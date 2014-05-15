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
    m_message = "";
    m_whom = "";
}
void prompt::loadMessaage(const char* m, const char* w){
    m_message = m;
    m_whom = w;
}
void prompt::loadMessaage(std::string m, std::string w){
    m_message = m;
    m_whom = w;
}
