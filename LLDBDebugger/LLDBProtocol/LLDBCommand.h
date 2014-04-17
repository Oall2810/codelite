#ifndef LLDBCOMMAND_H
#define LLDBCOMMAND_H

#include <wx/string.h>
#include "json_node.h"
#include "LLDBEnums.h"
#include "LLDBBreakpoint.h"
#include "LLDBSettings.h"

class LLDBCommand
{
protected:
    int                        m_commandType;
    wxString                   m_commandArguments;
    wxString                   m_workingDirectory;
    wxString                   m_executable;
    wxString                   m_redirectTTY;
    LLDBBreakpoint::Vec_t      m_breakpoints;
    int                        m_interruptReason;
    int                        m_lldbId;
    JSONElement::wxStringMap_t m_env;
    LLDBSettings               m_settings;
    int                        m_frameId;
    int                        m_threadId;
    wxString                   m_expression;
public:
    // Serialization API
    JSONElement ToJSON() const;
    void FromJSON(const JSONElement &json);

    LLDBCommand() : m_commandType(kCommandInvalid), m_interruptReason(kInterruptReasonNone), m_lldbId(0) {}
    LLDBCommand(const wxString &jsonString);
    virtual ~LLDBCommand();

    void SetExpression(const wxString& expression) {
        this->m_expression = expression;
    }
    const wxString& GetExpression() const {
        return m_expression;
    }
    void FillEnvFromMemory();
    /**
     * @brief return an environment array
     * The environment array is allocated on the heap and should be deleted
     * by the caller
     */
    char **GetEnvArray() const;

    void SetThreadId(int threadId) {
        this->m_threadId = threadId;
    }
    int GetThreadId() const {
        return m_threadId;
    }
    void Clear() {
        m_threadId = wxNOT_FOUND;
        m_frameId = wxNOT_FOUND;
        m_env.clear();
        m_commandType = kCommandInvalid;
        m_commandArguments.clear();
        m_workingDirectory.clear();
        m_executable.clear();
        m_redirectTTY.clear();
        m_breakpoints.clear();
        m_interruptReason = kInterruptReasonNone;
        m_lldbId = wxNOT_FOUND;
    }

    void SetFrameId(int frameId) {
        this->m_frameId = frameId;
    }
    int GetFrameId() const {
        return m_frameId;
    }
    void SetEnv(const JSONElement::wxStringMap_t& env) {
        this->m_env = env;
    }
    const JSONElement::wxStringMap_t& GetEnv() const {
        return m_env;
    }
    void SetSettings(const LLDBSettings& settings) {
        this->m_settings = settings;
    }
    const LLDBSettings& GetSettings() const {
        return m_settings;
    }
    void SetLldbId(int lldbId) {
        this->m_lldbId = lldbId;
    }
    int GetLldbId() const {
        return m_lldbId;
    }
    void SetInterruptReason(int interruptReason) {
        this->m_interruptReason = interruptReason;
    }
    int GetInterruptReason() const {
        return m_interruptReason;
    }
    void SetRedirectTTY(const wxString& redirectTTY) {
        this->m_redirectTTY = redirectTTY;
    }
    const wxString& GetRedirectTTY() const {
        return m_redirectTTY;
    }
    void SetExecutable(const wxString& executable) {
        this->m_executable = executable;
    }
    const wxString& GetExecutable() const {
        return m_executable;
    }
    void SetCommandArguments(const wxString& commandArguments) {
        this->m_commandArguments = commandArguments;
    }
    void SetCommandType(int commandType) {
        this->m_commandType = commandType;
    }
    const wxString& GetCommandArguments() const {
        return m_commandArguments;
    }
    int GetCommandType() const {
        return m_commandType;
    }
    void SetWorkingDirectory(const wxString& workingDirectory) {
        this->m_workingDirectory = workingDirectory;
    }
    const wxString& GetWorkingDirectory() const {
        return m_workingDirectory;
    }
    void SetBreakpoints(const LLDBBreakpoint::Vec_t& breakpoints) {
        this->m_breakpoints = breakpoints;
    }
    const LLDBBreakpoint::Vec_t& GetBreakpoints() const {
        return m_breakpoints;
    }
};

#endif // LLDBCOMMAND_H