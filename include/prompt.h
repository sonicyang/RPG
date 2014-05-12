#ifndef PROMPT_H
#define PROMPT_H


class prompt
{
    public:
        prompt();
        ~prompt();

        std::string getMessage() { return m_message; }
        void setMessage(std::string val) { m_message = val; }
        std::string getWhom() { return m_whom; }
        void setWhom(std::string val) { m_whom = val; }
    protected:
    private:
        std::string m_message;
        std::string m_whom;
};

#endif // PROMPT_H
