#include <fstream>
#include <string>
#include <cerrno>
#include <vector>

#ifndef UTILS_H_INCLUDED
#define UTILS_H_INCLUDED

char* stringToAllocChar(std::string);
void recycleMem(std::vector< std::vector<void*> >);


std::string get_file_contents(const char*);
std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems);
std::vector<std::string> split(const std::string &s, char delim);

#endif // UTILS_H_INCLUDED
