#ifndef PROMPT_H
#define PROMPT_H

#include <string>

class prompt
{
    public:
        prompt();
        ~prompt();

        void discardMessage();
        void loadMessaage(const char*, const char*);
        void loadMessaage(std::string, std::string);

        bool hasMessage(){ return !(m_message.size() == 0); }

        const std::string getMessage() const { return m_message; }
        void setMessage(std::string val) { m_message = val; }
        const std::string getWhom() const { return m_whom; }
        void setWhom(std::string val) { m_whom = val; }
    protected:
    private:
        std::string m_message;
        std::string m_whom;
};

#endif // PROMPT_H
