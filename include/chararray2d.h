#include "point.h"
#include <string>

#ifndef CHARARRAY2D_H
#define CHARARRAY2D_H


class CharArray2D
{
    public:
        CharArray2D();
        CharArray2D(Point);
        CharArray2D(Point,std::string);
        ~CharArray2D();
        CharArray2D(const CharArray2D& other);
        CharArray2D& operator=(const CharArray2D& other);
        int operator=(const std::string&);
        char* operator[](int subscript);

        Point size();
    protected:
    private:
        char** m_data;
        Point m_size;
};

#endif // 2DCHARARRAY_H
