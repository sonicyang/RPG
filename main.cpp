#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <cerrno>

#include "point.h"
#include "engine.h"
#include <unistd.h>
#include <locale.h>

//For the sake of NcursesW
#define _XOPEN_SOURCE_EXTENDED

using namespace std;

int main(int argc, char *argv[])
{
    Engine gCtl("data/setting.manifest");
    gCtl.excute();
    return 0;
}
