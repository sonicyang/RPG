#include "prompt.h"

prompt::prompt()
{
    //ctor
}

prompt::~prompt()
{
    //dtor
}

void prompt::discardMessage(){
    m_message = L"";
    m_whom = L"";
}
void prompt::loadMessaage(const wchar_t* m, const wchar_t* w){
    m_message = m;
    m_whom = w;
}
void prompt::loadMessaage(std::wstring m, std::wstring w){
    m_message = m;
    m_whom = w;
}
