/*
* Copyright (c) 2009, Helios (helios.vmg@gmail.com)
* All rights reserved.
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions are met:
*     * Redistributions of source code must retain the above copyright notice,
*       this list of conditions and the following disclaimer.
*     * Redistributions in binary form must reproduce the above copyright
*       notice, this list of conditions and the following disclaimer in the
*       documentation and/or other materials provided with the distribution.
*
* THIS SOFTWARE IS PROVIDED BY HELIOS "AS IS" AND ANY EXPRESS OR IMPLIED
* WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
* MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO
* EVENT SHALL HELIOS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
* EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
* PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
* OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
* WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
* OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
* OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#ifndef HELIOS_UTF8_H
#define HELIOS_UTF8_H


#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
using namespace std;


#define BOM8A 0xEF
#define BOM8B 0xBB
#define BOM8C 0xBF

typedef unsigned char uchar;

/*
string: a UTF-8-encoded C string (nul terminated)
Return value: a wchar_t C string.

The function handles memory allocation on its own.

Limitations: Only handles the range [U+0000;U+FFFF], higher code points are
changed to '?'.

Assumptions: sizeof(wchar_t)>=2
*/
wchar_t *UTF8_to_WChar(const char*);

//Do not call me.
long getUTF8size(const wchar_t*);

/*
string: a wchar_t C string (nul terminated)
Return value: a UTF-8-encoded C string.

The function handles memory allocation on its own.

Limitations: Only handles the range [U+0000;U+FFFF], higher code points are
changed to '?'.

Assumptions: sizeof(wchar_t)>=2
*/
char *WChar_to_UTF8(const wchar_t*);

//my helper function
void loadContent(const string& a, wstring& b);

#endif
