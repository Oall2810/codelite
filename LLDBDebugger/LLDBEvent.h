#ifndef LLDBEVENT_H
#define LLDBEVENT_H

#include <wx/event.h>
#include "LLDBBacktrace.h"

class LLDBEvent : public wxCommandEvent
{
    LLDBBacktrace m_backtrace;
    wxString      m_filename;
    int           m_linenumber;

public:
    LLDBEvent(wxEventType eventType, int winid = 0);
    virtual ~LLDBEvent();
    LLDBEvent(const LLDBEvent& src);
    LLDBEvent& operator=(const LLDBEvent& src);
    virtual wxEvent* Clone() const {
        return new LLDBEvent(*this);
    }
    void SetBacktrace(const LLDBBacktrace& backtrace) {
        this->m_backtrace = backtrace;
    }
    const LLDBBacktrace& GetBacktrace() const {
        return m_backtrace;
    }
    void SetFilename(const wxString& filename) {
        this->m_filename = filename;
    }
    void SetLinenumber(int linenumber) {
        this->m_linenumber = linenumber;
    }
    const wxString& GetFilename() const {
        return m_filename;
    }
    int GetLinenumber() const {
        return m_linenumber;
    }
};

wxDECLARE_EVENT(wxEVT_LLDB_STOPPED,   LLDBEvent);
wxDECLARE_EVENT(wxEVT_LLDB_BACKTRACE, LLDBEvent);
wxDECLARE_EVENT(wxEVT_LLDB_EXITED,    LLDBEvent);
wxDECLARE_EVENT(wxEVT_LLDB_STARTED,   LLDBEvent);

typedef void (wxEvtHandler::*LLDBEventFunction)(LLDBEvent&);
#define LLDBEventHandler(func) \
    wxEVENT_HANDLER_CAST(LLDBEventFunction, func)

#endif // LLDBEVENT_H
