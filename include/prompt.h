#ifndef PROMPT_H
#define PROMPT_H

#include <deque>
#include <string>
#include "genericcontorller.h"

class Engine;

class prompt : public genericContorller
{
    public:
        prompt(Engine*);
        ~prompt();
        
        int hKeyZ();

        int hRender(); 

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
        std::deque<std::wstring> m_message;
        std::deque<std::wstring> m_whom;
};

#endif // PROMPT_H
