#include "wx/wx.h"
#include <wx/mstream.h>
#include <wx/snglinst.h>
#include <string>
#include <vector>
#include <map>
#include <chrono>
#include <thread>
#include <mutex>
#include <hidapi.h>

enum kb_mode
{
    KB_NONE = 0,
    KB_LAYER,
    KB_TIME,
    KB_STOPW
};

//command id for hid
enum commands
{
    ID_QUERY_MODE = 0xF0,   //send
    ID_REPORT_MODE,         //receive
    ID_UPDATE_TIME          //send
};

struct Keyboard
{
    uint16_t vendor_id;
    uint16_t product_id;
    hid_device *hd;
    kb_mode mode;
};

#define USAGE_PAGE 0xFF60
#define USAGE 0x61

static std::vector<Keyboard> supported_keyboards = {
    {0x8065, 0x8048, 0, KB_NONE}, // pabile p48
    {0x594D, 0x0075, 0, KB_NONE}  // ymdk id75
};

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
    void OnMenuSettings(wxCommandEvent&);
    void OnMenuExit(wxCommandEvent&);
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

private:
    wxTimer *m_dev_enum;
    std::map<std::string, Keyboard> m_keyboards;//connected keyboards
    std::chrono::time_point<std::chrono::steady_clock> m_sw_start;//start time by a stopwatch
    std::mutex m_mutex;
    //polling intervals
    uint16_t m_dev_int;
    uint16_t m_time_int;

private:
    std::string get_key(uint16_t vendor_id, uint16_t product_id)
    {
     return std::to_string(vendor_id) + ":" + std::to_string(product_id);
    }

    void close_all()
    {
        for (auto& kb : m_keyboards)
        {
            kb.second.mode = KB_NONE;
            std::this_thread::sleep_for(std::chrono::seconds(1));
            hid_close(kb.second.hd);
        }
        m_keyboards.clear();
    }

    bool is_supported(uint16_t vendor_id, uint16_t product_id,
        uint16_t usage_page, uint16_t usage)
    {
        for (const auto &kb : supported_keyboards)
        {
            if (kb.vendor_id == vendor_id &&
                kb.product_id == product_id &&
                USAGE_PAGE == usage_page &&
                USAGE == usage)
            {
                return true;
            }
        }
        return false;
    }

    void query_mode(Keyboard *kb);

    void keyboard_loop(Keyboard *kb);

protected:
    void OnOK(wxCommandEvent& event);
    void OnCloseWindow(wxCloseEvent& event);
    void OnDevEnum(wxTimerEvent &event);

    void OnDevSpin(wxSpinEvent &event);
    void OnDevSpinText(wxCommandEvent &event);
    void OnTimeSpin(wxSpinEvent &event);
    void OnTimeSpinText(wxCommandEvent &event);

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

