#include "wx/artprov.h"
#include "wx/taskbar.h"
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
: wxDialog(NULL, wxID_ANY, title)
{
    wxSizer* const sizerTop = new wxBoxSizer(wxVERTICAL);

    wxSizerFlags flags;
    flags.Border(wxALL, 10);

    sizerTop->AddStretchSpacer()->SetMinSize(200, 50);

    wxSizer* const sizerBtns = new wxBoxSizer(wxHORIZONTAL);
    sizerBtns->Add(new wxButton(this, wxID_OK, "&OK"), flags);

    sizerTop->Add(sizerBtns, flags.Align(wxALIGN_CENTER_HORIZONTAL));
    SetSizerAndFit(sizerTop);
    Centre();

    m_taskBarIcon = new HostTrayIcon();

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
    m_dev_enum->Start(5000);    //check every 5 seconds
}

HostDlg::~HostDlg() {
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
    std::map<std::string, bool> current_devices;
    struct hid_device_info *devs, *cur_dev;

    devs = hid_enumerate(0x0, 0x0);
    cur_dev = devs;
    while (cur_dev)
    {
        if (is_supported(cur_dev->vendor_id, cur_dev->product_id))
        {
            std::string key = get_key(cur_dev->vendor_id, cur_dev->product_id);
            current_devices[key] = true;

            if (m_keyboards.find(key) == m_keyboards.end())
            {
                //open new device
                hid_device* handle = hid_open(cur_dev->vendor_id, cur_dev->product_id, NULL);
                if (handle)
                {
                    Keyboard kb =
                    {
                        cur_dev->vendor_id,
                        cur_dev->product_id,
                        handle,
                        KB_NONE,
                        0
                    };
                    m_keyboards.insert(std::pair<std::string, Keyboard>(key, kb));
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
            it = m_keyboards.erase(it);
        }
        else
            ++it;
    }
}
    // ----------------------------------------------------------------------------
// HostTrayIcon implementation
// ----------------------------------------------------------------------------

enum { PU_SETTINGS = 10001, PU_EXIT };

wxBEGIN_EVENT_TABLE(HostTrayIcon, wxTaskBarIcon)
EVT_MENU(PU_SETTINGS, HostTrayIcon::OnMenuSettings)
EVT_MENU(PU_EXIT, HostTrayIcon::OnMenuExit)
EVT_TASKBAR_LEFT_DCLICK(HostTrayIcon::OnLeftButtonDClick)
wxEND_EVENT_TABLE()

void HostTrayIcon::OnMenuSettings(wxCommandEvent&) {
    gs_dialog->Show(true);
}

void HostTrayIcon::OnMenuExit(wxCommandEvent&) {
    gs_dialog->Destroy();
}

// Overridables
wxMenu* HostTrayIcon::CreatePopupMenu() {
    wxMenu* menu = new wxMenu;
    menu->Append(PU_SETTINGS, "&Settings");
    menu->AppendSeparator();
    menu->Append(PU_EXIT, "E&xit");
    return menu;
}

void HostTrayIcon::OnLeftButtonDClick(wxTaskBarIconEvent&) {
    gs_dialog->Show(true);
}
