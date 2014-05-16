#ifndef PROMPT_H
#define PROMPT_H

#include <string>

class prompt
{
    public:
        prompt();
        ~prompt();

        void discardMessage();
        void loadMessaage(const wchar_t*, const wchar_t*);
        void loadMessaage(std::wstring, std::wstring);

        bool hasMessage(){ return !(m_message.size() == 0); }

        const std::wstring getMessage() const { return m_message; }
        void setMessage(std::wstring val) { m_message = val; }
        const std::wstring getWhom() const { return m_whom; }
        void setWhom(std::wstring val) { m_whom = val; }
    protected:
    private:
        std::wstring m_message;
        std::wstring m_whom;
};

#endif // PROMPT_H
