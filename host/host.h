#include "wx/wx.h"
#include <wx/mstream.h>
#include <wx/snglinst.h>

class HostTrayIcon : public wxTaskBarIcon
{
public:
#if defined(__WXOSX__) && wxOSX_USE_COCOA
    HostTrayIcon(wxTaskBarIconType iconType = wxTBI_DEFAULT_TYPE)
    :   wxTaskBarIcon(iconType)
#else
    HostTrayIcon()
#endif
    {}

    void OnLeftButtonDClick(wxTaskBarIconEvent&);
    void OnMenuRestore(wxCommandEvent&);
    void OnMenuExit(wxCommandEvent&);
    void OnMenuSetNewIcon(wxCommandEvent&);
    void OnMenuCheckmark(wxCommandEvent&);
    void OnMenuUICheckmark(wxUpdateUIEvent&);
    void OnMenuSub(wxCommandEvent&);
    virtual wxMenu *CreatePopupMenu() wxOVERRIDE;

    wxDECLARE_EVENT_TABLE();
};


// Define a new application
class HostApp : public wxApp
{
public:
    wxSingleInstanceChecker *m_checker;
    virtual bool OnInit() wxOVERRIDE;
    virtual int OnExit() wxOVERRIDE;
};

class HostDlg: public wxDialog
{
public:
    HostDlg(const wxString& title);
    virtual ~HostDlg();

protected:
    void OnAbout(wxCommandEvent& event);
    void OnOK(wxCommandEvent& event);
    void OnExit(wxCommandEvent& event);
    void OnCloseWindow(wxCloseEvent& event);

    HostTrayIcon   *m_taskBarIcon;
#if defined(__WXOSX__) && wxOSX_USE_COCOA
    HostTrayIcon   *m_dockIcon;
#endif

    wxDECLARE_EVENT_TABLE();
};

#define wxGetBitmapFromMemory(name) _wxGetBitmapFromMemory(name ## _png, sizeof(name ## _png))

inline wxBitmap _wxGetBitmapFromMemory(const unsigned char *data, int length)
{
	wxLogNull logNo;
	wxMemoryInputStream is(data, length);
    wxImage image(is, wxBITMAP_TYPE_PNG);
	return wxBitmap(image);
}

