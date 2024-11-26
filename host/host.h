#include "wx/wx.h"
#include <wx/mstream.h>
#include <wx/snglinst.h>
#include <string>
#include <vector>
#include <map>
#include <chrono>
#include <thread>
#include <hidapi.h>

enum kb_mode
{
    KB_NONE = 0,
    KB_LAYER,
    KB_TIME
};

//command id for hid
enum commands
{
    ID_QUERY_MODE = 0x30,   //send
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
            hid_close(kb.second.hd);
        }
        m_keyboards.clear();
    }

    bool is_supported(uint16_t vendor_id, uint16_t product_id)
    {
        for (const auto &kb : supported_keyboards)
        {
            if (kb.vendor_id == vendor_id &&
                kb.product_id == product_id)
            {
                return true;
            }
        }
        return false;
    }

    void query_mode(Keyboard* kb)
    {
        uint8_t query[32] = {ID_QUERY_MODE};//command to query mode
        uint8_t resps[32] = {0};

        hid_write(kb->hd, query, sizeof(query));
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        hid_read(kb->hd, resps, sizeof(resps));

        if (resps[0] == ID_REPORT_MODE)
        {
            kb->mode = (kb_mode)(resps[1]);
        }
    }

    void keyboard_loop(Keyboard* kb)
    {
        if (!kb) return;
        while (true)
        {
            //update mode
            //query_mode(kb);

            //if (kb->mode == KB_NONE) return;
            //
            //switch (kb->mode)
            //{
                //case KB_TIME:
                    //{
                        auto now = std::chrono::system_clock::now();
                        std::time_t now_c = std::chrono::system_clock::to_time_t(now);
                        std::tm *now_tm = std::localtime(&now_c);

                        uint8_t buffer[32] = {0};
                        buffer[0] = ID_UPDATE_TIME;
                        buffer[1] = static_cast<uint8_t>(now_tm->tm_hour / 10) + '0';
                        buffer[2] = static_cast<uint8_t>(now_tm->tm_hour % 10) + '0';
                        buffer[3] = static_cast<uint8_t>(now_tm->tm_min / 10) + '0';
                        buffer[4] = static_cast<uint8_t>(now_tm->tm_min % 10) + '0';
                        buffer[5] = static_cast<uint8_t>(now_tm->tm_sec / 10) + '0';
                        buffer[6] = static_cast<uint8_t>(now_tm->tm_sec % 10) + '0';

                        int result = hid_write(kb->hd, buffer, 6);
                    //}
                    //break;
            //}

            //
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
        }
    }

protected:
    void OnOK(wxCommandEvent& event);
    void OnCloseWindow(wxCloseEvent& event);
    void OnDevEnum(wxTimerEvent &event);

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

