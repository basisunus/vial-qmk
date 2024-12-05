#include "wx/artprov.h"
#include "wx/taskbar.h"
#include "wx/spinctrl.h"
#include <wx/stdpaths.h>
#include <wx/wfstream.h>
#include <wx/fileconf.h>
#include "host.h"
#include "images.h"

// ----------------------------------------------------------------------------
// global variables
// ----------------------------------------------------------------------------

static HostDlg* gs_dialog = NULL;

// ============================================================================
// implementation
// ============================================================================

// ----------------------------------------------------------------------------
// HostApp
// ----------------------------------------------------------------------------

wxIMPLEMENT_APP(HostApp);

bool HostApp::OnInit()
{
    m_checker = new wxSingleInstanceChecker("HostApp");
    if (m_checker->IsAnotherRunning())
    {
        wxLogError("Another instance of the application is already running.");
        delete m_checker;
        return false;
    }
    if (!wxApp::OnInit())
        return false;

	//add png handler
	wxImage::AddHandler(new wxPNGHandler);

    if (!wxTaskBarIcon::IsAvailable())
    {
        wxMessageBox("There appears to be no system tray support in your current environment. This sample may not behave as expected.",
            "Warning", wxOK | wxICON_EXCLAMATION);
    }

    // Create the main window
    gs_dialog = new HostDlg("Settings");

    return true;
}

int HostApp::OnExit()
{
    if (m_checker)
        delete m_checker;

    return 0;
}

// ----------------------------------------------------------------------------
// HostDlg implementation
// ----------------------------------------------------------------------------

wxBEGIN_EVENT_TABLE(HostDlg, wxDialog)
EVT_BUTTON(wxID_OK, HostDlg::OnOK)
EVT_CLOSE(HostDlg::OnCloseWindow)
wxEND_EVENT_TABLE()

HostDlg::HostDlg(const wxString& title)
: wxDialog(NULL, wxID_ANY, title),
m_dev_int(5000),
m_time_int(100),
m_run_hid(true)
{
    //read from config file
    read_settings();

    wxSizer* const sizerTop = new wxBoxSizer(wxVERTICAL);

    wxSizerFlags flags;
    flags.Border(wxALL, 10);

    sizerTop->AddStretchSpacer()->SetMinSize(200, 50);

    wxStaticText* devSt = new wxStaticText(this, 0, "Device Polling:");
    wxSpinCtrl*   devSpin = new wxSpinCtrl(this, wxID_ANY, wxString::Format("%d", m_dev_int),
        wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS | wxSP_WRAP, 1, 65535, m_dev_int);

    wxStaticText* timeSt = new wxStaticText(this, 0, "Time Polling:");
    wxSpinCtrl*   timeSpint = new wxSpinCtrl(this, wxID_ANY, wxString::Format("%d", m_time_int),
        wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS | wxSP_WRAP, 1, 65535, m_time_int);

    devSpin->Bind(wxEVT_SPINCTRL, &HostDlg::OnDevSpin, this);
    devSpin->Bind(wxEVT_TEXT, &HostDlg::OnDevSpinText, this);
    timeSpint->Bind(wxEVT_SPINCTRL, &HostDlg::OnTimeSpin, this);
    timeSpint->Bind(wxEVT_TEXT, &HostDlg::OnTimeSpinText, this);

    wxSizer* const sizerSpns = new wxBoxSizer(wxHORIZONTAL);
    sizerSpns->Add(devSt, flags);
    sizerSpns->Add(devSpin, flags);
    sizerSpns->Add(timeSt, flags);
    sizerSpns->Add(timeSpint, flags);

    wxSizer* const sizerBtns = new wxBoxSizer(wxHORIZONTAL);
    m_start_stop_btn = new wxButton(this, wxID_ANY, m_run_hid ? "&Stop" : "&Start");
    m_start_stop_btn->Bind(wxEVT_BUTTON, &HostDlg::OnStartStopBtn, this);
    sizerBtns->Add(m_start_stop_btn, flags);
    sizerBtns->Add(new wxButton(this, wxID_OK, "&OK"), flags);

    sizerTop->Add(sizerSpns, flags.Align(wxALIGN_CENTER_HORIZONTAL));
    sizerTop->Add(sizerBtns, flags.Align(wxALIGN_CENTER_HORIZONTAL));
    SetSizerAndFit(sizerTop);
    Centre();

    m_taskBarIcon = new HostTrayIcon(this);

    // we should be able to show up to 128 characters on Windows
    wxIcon icon;
    icon.CopyFromBitmap(wxGetBitmapFromMemory(squares));
    if (!m_taskBarIcon->SetIcon(icon, "Ortholinear Keyboardisplay"))
    {
        wxMessageBox("Could not set icon.", "Error", wxOK | wxICON_ERROR);
    }

    // init hidapi
    if (hid_init())
    {
        wxMessageBox("HID failed to initialize.", "Error", wxOK | wxICON_ERROR);
    }

    //timer for device enumeration
    m_dev_enum = new wxTimer(this);
    Bind(wxEVT_TIMER, &HostDlg::OnDevEnum, this);
    m_dev_enum->Start(m_dev_int);    //check every 0.5 seconds
}

HostDlg::~HostDlg() {
    save_settings();

    delete m_taskBarIcon;

    //hidapi
    hid_exit();

    //timer
    m_dev_enum->Stop();
    delete m_dev_enum;

    close_all();
}

void HostDlg::OnOK(wxCommandEvent& WXUNUSED(event)) {
    Show(false);
}

void HostDlg::OnCloseWindow(wxCloseEvent& WXUNUSED(event)) {
    Show(false);
}

void HostDlg::OnDevEnum(wxTimerEvent& event)
{
    if (!m_run_hid)
        return;

    std::map<std::string, bool> current_devices;
    struct hid_device_info *devs, *cur_dev;

    devs = hid_enumerate(0x0, 0x0);
    cur_dev = devs;
    while (cur_dev)
    {
        if (is_supported(cur_dev->vendor_id, cur_dev->product_id,
            cur_dev->usage_page, cur_dev->usage))
        {
            std::string key = get_key(cur_dev->vendor_id, cur_dev->product_id);
            current_devices[key] = true;

            if (m_keyboards.find(key) == m_keyboards.end())
            {
                //open new device
                hid_device* handle = hid_open_path(cur_dev->path);
                if (handle)
                {
                    Keyboard kb =
                    {
                        cur_dev->vendor_id,
                        cur_dev->product_id,
                        handle,
                        KB_LAYER
                    };
                    m_keyboards[key] = kb;
                    //start loop
                    std::thread(&HostDlg::keyboard_loop, this, &(m_keyboards[key])).detach();
                }
            }
        }
        cur_dev = cur_dev->next;
    }
    hid_free_enumeration(devs);

    //close devices that are no longer connected
    for (auto it = m_keyboards.begin(); it != m_keyboards.end();)
    {
        if (current_devices.find(it->first) == current_devices.end())
        {
            hid_close(it->second.hd);
            it->second.mode = KB_NONE;
            std::this_thread::sleep_for(std::chrono::seconds(1));
            it = m_keyboards.erase(it);
        }
        else
            ++it;
    }
}

void HostDlg::OnStartStopBtn(wxCommandEvent& event)
{
    ToggleRunHID();
    if (m_run_hid)
        m_start_stop_btn->SetLabel("&Stop");
    else
        m_start_stop_btn->SetLabel("&Start");
}

void HostDlg::OnDevSpin(wxSpinEvent& event) {
    m_dev_int = event.GetValue();
    m_dev_enum->Start(m_dev_int);
}

void HostDlg::OnDevSpinText(wxCommandEvent& event)
{
    wxString str = event.GetString();
    m_dev_int    = std::atoi(str.ToStdString().c_str());
    m_dev_enum->Start(m_dev_int);
}

void HostDlg::OnTimeSpin(wxSpinEvent& event)
{
    m_time_int = event.GetValue();
}

void HostDlg::OnTimeSpinText(wxCommandEvent& event)
{
    wxString str = event.GetString();
    m_time_int   = std::atoi(str.ToStdString().c_str());
}

void HostDlg::query_mode(Keyboard* kb) {
    // lock
    std::unique_lock<std::mutex> lock(m_mutex);

    uint8_t query[32] = {0}; // command to query mode
    uint8_t resps[32] = {0};

    std::wstring str;
    int          err;
    query[0] = 0xFF;
    query[1] = ID_QUERY_MODE;
    err = hid_write(kb->hd, query, sizeof(query));
    if (err == -1) str = hid_error(kb->hd);

    // Clear any old data from the buffer
    while (hid_read(kb->hd, resps, sizeof(resps)) > 0)
    {
        if (resps[0] == 0xFF && resps[1] == ID_REPORT_MODE) {
            uint8_t mode = resps[2];
            switch (mode)
            {
                case KB_STOPW:
                    if (kb->mode != KB_STOPW)
                        m_sw_start = std::chrono::steady_clock::now();
                    break;
            }
            kb->mode = (kb_mode)(mode);
            break;
        }
        // No-op: just clearing the buffer
    }
}

void HostDlg::keyboard_loop(Keyboard* kb) {
    if (!kb) return;
    while (true) {
        if (kb->mode == KB_NONE) return;

        if (!m_run_hid)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(m_time_int));
            continue;
        }

        // update mode
        query_mode(kb);

        switch (kb->mode) {
            case KB_TIME: {
                auto        now    = std::chrono::system_clock::now();
                std::time_t now_c  = std::chrono::system_clock::to_time_t(now);
                std::tm*    now_tm = std::localtime(&now_c);

                uint8_t buffer[32] = {0};
                buffer[0]          = 0xFF;
                buffer[1]          = ID_UPDATE_TIME;
                buffer[2]          = static_cast<uint8_t>(now_tm->tm_hour / 10) + '0';
                buffer[3]          = static_cast<uint8_t>(now_tm->tm_hour % 10) + '0';
                buffer[4]          = static_cast<uint8_t>(now_tm->tm_min / 10) + '0';
                buffer[5]          = static_cast<uint8_t>(now_tm->tm_min % 10) + '0';

                hid_write(kb->hd, buffer, sizeof(buffer));
            } break;
            case KB_TSEC: {
                auto        now    = std::chrono::system_clock::now();
                std::time_t now_c  = std::chrono::system_clock::to_time_t(now);
                std::tm*    now_tm = std::localtime(&now_c);

                uint8_t buffer[32] = {0};
                buffer[0]          = 0xFF;
                buffer[1]          = ID_UPDATE_TIME;
                buffer[2]          = static_cast<uint8_t>(now_tm->tm_min / 10) + '0';
                buffer[3]          = static_cast<uint8_t>(now_tm->tm_min % 10) + '0';
                buffer[4]          = static_cast<uint8_t>(now_tm->tm_sec / 10) + '0';
                buffer[5]          = static_cast<uint8_t>(now_tm->tm_sec % 10) + '0';

                hid_write(kb->hd, buffer, sizeof(buffer));
            } break;
            case KB_STOPW: {
                auto sw_cur = std::chrono::steady_clock::now();
                auto sw_duration = std::chrono::duration_cast<std::chrono::seconds>(sw_cur - m_sw_start).count();
                int  minutes     = sw_duration / 60;
                int  seconds     = sw_duration % 60;

                uint8_t buffer[32] = {0};
                buffer[0]          = 0xFF;
                buffer[1]          = ID_UPDATE_TIME;
                buffer[2]          = static_cast<uint8_t>(minutes / 10) + '0';
                buffer[3]          = static_cast<uint8_t>(minutes % 10) + '0';
                buffer[4]          = static_cast<uint8_t>(seconds / 10) + '0';
                buffer[5]          = static_cast<uint8_t>(seconds % 10) + '0';

                hid_write(kb->hd, buffer, sizeof(buffer));
            } break;
        }

        //
        std::this_thread::sleep_for(std::chrono::milliseconds(m_time_int));
    }
}

void HostDlg::read_settings()
{
	wxString expath = wxStandardPaths::Get().GetExecutablePath();
	expath = wxPathOnly(expath);
	wxString dft = expath + "\\" + "config.ini";
	wxFileInputStream is(dft);
	if (!is.IsOk())
		return;
	wxFileConfig fconfig(is);

    int ival;
    fconfig.Read("dev int", &ival, 5000);
    m_dev_int = ival;

    fconfig.Read("time int", &ival, 100);
    m_time_int = ival;

    bool bval;
    fconfig.Read("run hid", &bval, true);
    m_run_hid = bval;
}

void HostDlg::save_settings()
{
	wxString app_name = "Host " +
		wxString::Format("%d.%.1f", 1, float(0));
	wxString vendor_name = "Host";
	wxString local_name = "config.ini";
	wxFileConfig fconfig(app_name, vendor_name, local_name, "",
		wxCONFIG_USE_LOCAL_FILE);

    int ival;
    ival = m_dev_int;
    fconfig.Write("dev int", ival);

    ival = m_time_int;
    fconfig.Write("time int", ival);

    fconfig.Write("run hid", m_run_hid);

	wxString expath = wxStandardPaths::Get().GetExecutablePath();
	expath = wxPathOnly(expath);
	wxString dft = expath + "\\" + "config.ini";
	wxString str = "\x5c\x5c\x3f\x5c" + dft;
	wxFileOutputStream os(str);
	fconfig.Save(os);
}

// ----------------------------------------------------------------------------
// HostTrayIcon implementation
// ----------------------------------------------------------------------------

enum
{
    PU_START_STOP = 10001,
    PU_SETTINGS,
    PU_EXIT
};

wxBEGIN_EVENT_TABLE(HostTrayIcon, wxTaskBarIcon)
EVT_MENU(PU_START_STOP, HostTrayIcon::OnStartStop)
EVT_MENU(PU_SETTINGS, HostTrayIcon::OnMenuSettings)
EVT_MENU(PU_EXIT, HostTrayIcon::OnMenuExit)
EVT_TASKBAR_LEFT_DCLICK(HostTrayIcon::OnLeftButtonDClick)
wxEND_EVENT_TABLE()

void HostTrayIcon::OnStartStop(wxCommandEvent& event)
{
    if (m_host_dlg)
        m_host_dlg->ToggleRunHID();
}

void HostTrayIcon::OnMenuSettings(wxCommandEvent&) {
    gs_dialog->Show(true);
}

void HostTrayIcon::OnMenuExit(wxCommandEvent&) {
    gs_dialog->Destroy();
}

// Overridables
wxMenu* HostTrayIcon::CreatePopupMenu() {
    wxMenu* menu = new wxMenu;
    if (m_host_dlg)
    {
        if (m_host_dlg->GetRunHID())
            menu->Append(PU_START_STOP, "&Stop");
        else
            menu->Append(PU_START_STOP, "&Start");
    }
    menu->Append(PU_SETTINGS, "&Settings");
    menu->AppendSeparator();
    menu->Append(PU_EXIT, "E&xit");
    return menu;
}

void HostTrayIcon::OnLeftButtonDClick(wxTaskBarIconEvent&) {
    gs_dialog->Show(true);
}
