#ifndef PROMPT_H
#define PROMPT_H

#include <vector>
#include <string>

class prompt
{
    public:
        prompt();
        prompt(const wchar_t*, const wchar_t*);
        ~prompt();

        void discardMessage();
        void loadMessaage(const wchar_t*, const wchar_t*);
        void loadMessaage(std::wstring, std::wstring);

        bool hasMessage(){ return !(m_message.size() == 0); }

        const std::wstring getMessage() const { return m_message.back(); }
        void setMessage(std::wstring val) { m_message.push_back(val); }
        const std::wstring getWhom() const { return m_whom.back(); }
        void setWhom(std::wstring val) { m_whom.push_back(val); }
    protected:
    private:
        std::vector<std::wstring> m_message;
        std::vector<std::wstring> m_whom;
};

#endif // PROMPT_H
