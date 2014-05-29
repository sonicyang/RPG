#include "prompt.h"

prompt::prompt()
{
    //ctor
}

prompt::prompt(const wchar_t* m, const wchar_t* w)
{
    loadMessaage(m, w);
}

prompt::~prompt()
{
    //dtor
}

void prompt::discardMessage(){
    if(m_message.size() > 0){
        m_message.pop_back();
        m_whom.pop_back();
    }
}
void prompt::loadMessaage(const wchar_t* m, const wchar_t* w){
    std::wstring s1(m);
    std::wstring s2(w);
    loadMessaage(s1, s2);
}
void prompt::loadMessaage(std::wstring m, std::wstring w){
    m_message.push_back(m);
    m_whom.push_back(w);
}
