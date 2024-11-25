#include "wx/artprov.h"
#include "wx/taskbar.h"
#include "host.h"
#include "images.h"
#include <hidapi.h>

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
    m_checker = new wxSingleInstanceChecker("MyApp");
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
    gs_dialog = new HostDlg("Host");

    //gs_dialog->Show(true);

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
EVT_BUTTON(wxID_ABOUT, HostDlg::OnAbout)
EVT_BUTTON(wxID_OK, HostDlg::OnOK)
EVT_BUTTON(wxID_EXIT, HostDlg::OnExit)
EVT_CLOSE(HostDlg::OnCloseWindow)
wxEND_EVENT_TABLE()

HostDlg::HostDlg(const wxString& title)
: wxDialog(NULL, wxID_ANY, title)
{
    wxSizer* const sizerTop = new wxBoxSizer(wxVERTICAL);

    wxSizerFlags flags;
    flags.Border(wxALL, 10);

    sizerTop->Add(new wxStaticText(this, wxID_ANY, "Press 'Hide me' to hide this window, Exit to quit."), flags);

    sizerTop->Add(new wxStaticText(this, wxID_ANY, "Double-click on the taskbar icon to show me again."), flags);

    sizerTop->AddStretchSpacer()->SetMinSize(200, 50);

    wxSizer* const sizerBtns = new wxBoxSizer(wxHORIZONTAL);
    sizerBtns->Add(new wxButton(this, wxID_ABOUT, "&About"), flags);
    sizerBtns->Add(new wxButton(this, wxID_OK, "&Hide"), flags);
    sizerBtns->Add(new wxButton(this, wxID_EXIT, "E&xit"), flags);

    sizerTop->Add(sizerBtns, flags.Align(wxALIGN_CENTER_HORIZONTAL));
    SetSizerAndFit(sizerTop);
    Centre();

    m_taskBarIcon = new HostTrayIcon();

    // we should be able to show up to 128 characters on Windows
    wxIcon icon;
    icon.CopyFromBitmap(wxGetBitmapFromMemory(squares));
    if (!m_taskBarIcon->SetIcon(icon, "Host"))
    {
        wxLogError("Could not set icon.");
    }
}

HostDlg::~HostDlg() {
    delete m_taskBarIcon;
}

void HostDlg::OnAbout(wxCommandEvent& WXUNUSED(event))
{
}

void HostDlg::OnOK(wxCommandEvent& WXUNUSED(event)) {
    Show(false);
}

void HostDlg::OnExit(wxCommandEvent& WXUNUSED(event)) {
    Close(true);
}

void HostDlg::OnCloseWindow(wxCloseEvent& WXUNUSED(event)) {
    Destroy();
}

// ----------------------------------------------------------------------------
// HostTrayIcon implementation
// ----------------------------------------------------------------------------

enum { PU_RESTORE = 10001, PU_NEW_ICON, PU_EXIT, PU_CHECKMARK, PU_SUB1, PU_SUB2, PU_SUBMAIN };

wxBEGIN_EVENT_TABLE(HostTrayIcon, wxTaskBarIcon)
EVT_MENU(PU_RESTORE, HostTrayIcon::OnMenuRestore)
EVT_MENU(PU_EXIT, HostTrayIcon::OnMenuExit)
EVT_MENU(PU_NEW_ICON, HostTrayIcon::OnMenuSetNewIcon)
EVT_MENU(PU_CHECKMARK, HostTrayIcon::OnMenuCheckmark)
EVT_UPDATE_UI(PU_CHECKMARK, HostTrayIcon::OnMenuUICheckmark)
EVT_TASKBAR_LEFT_DCLICK(HostTrayIcon::OnLeftButtonDClick)
EVT_MENU(PU_SUB1, HostTrayIcon::OnMenuSub)
EVT_MENU(PU_SUB2, HostTrayIcon::OnMenuSub)
wxEND_EVENT_TABLE()

void HostTrayIcon::OnMenuRestore(wxCommandEvent&) {
    gs_dialog->Show(true);
}

void HostTrayIcon::OnMenuExit(wxCommandEvent&) {
    gs_dialog->Close(true);
}

static bool check = true;

void HostTrayIcon::OnMenuCheckmark(wxCommandEvent&) {
    check = !check;
}

void HostTrayIcon::OnMenuUICheckmark(wxUpdateUIEvent& event) {
    event.Check(check);
}

void HostTrayIcon::OnMenuSetNewIcon(wxCommandEvent&) {
    // wxIcon icon(smile_xpm);

    // if (!SetIcon(wxBitmapBundle::FromBitmaps(
    //                  wxBitmap(smile_xpm),
    //                  wxBitmap(smile2_xpm)
    //              ),
    //              "wxTaskBarIcon Sample - a different icon"))
    //     wxMessageBox("Could not set new icon.");
}

void HostTrayIcon::OnMenuSub(wxCommandEvent&) {
    wxMessageBox("You clicked on a submenu!");
}

// Overridables
wxMenu* HostTrayIcon::CreatePopupMenu() {
    wxMenu* menu = new wxMenu;
    menu->Append(PU_RESTORE, "&Restore main window");
    menu->AppendSeparator();
    menu->Append(PU_NEW_ICON, "&Set New Icon");
    menu->AppendSeparator();
    menu->AppendCheckItem(PU_CHECKMARK, "Test &check mark");
    menu->AppendSeparator();
    wxMenu* submenu = new wxMenu;
    submenu->Append(PU_SUB1, "One submenu");
    submenu->AppendSeparator();
    submenu->Append(PU_SUB2, "Another submenu");
    menu->Append(PU_SUBMAIN, "Submenu", submenu);
    /* OSX has built-in quit menu for the dock menu, but not for the status item */
#ifdef __WXOSX__
    if (OSXIsStatusItem())
#endif
    {
        menu->AppendSeparator();
        menu->Append(PU_EXIT, "E&xit");
    }
    return menu;
}

void HostTrayIcon::OnLeftButtonDClick(wxTaskBarIconEvent&) {
    gs_dialog->Show(true);
}
