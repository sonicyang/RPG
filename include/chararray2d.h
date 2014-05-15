#include "point.h"
#include <string>

#ifndef ARRAY2D_H
#define ARRAY2D_H

template<class T>
class Array2D
{
    public:
        Array2D();
        Array2D(Point);
        Array2D(Point,std::string);
        ~Array2D();
        Array2D(const Array2D& other);
        Array2D& operator=(const Array2D& other);
        int operator=(const std::string&);
        T* operator[](unsigned int subscript);

        Point size();
    protected:
    private:
        T** m_data;
        Point m_size;
};

#endif // 2DCHARARRAY_H
