#include "Point.h"
#include <string>
#include <cstring>

#include "chararray2d.h"

template<class T>
Array2D<T>::Array2D()
{
    m_size = Point(2,2);
    m_data = new T*[m_size.m_y];
    m_data[0] = new T[m_size.m_x * m_size.m_y];
    for(unsigned int i = 1; i < m_size.m_y; i++)
        m_data[i] = m_data[0] + i * m_size.m_x;
}

template<class T>
Array2D<T>::Array2D(Point s)
{
    m_size = s;
    m_data = new T*[m_size.m_y];
    m_data[0] = new T[m_size.m_x * m_size.m_y];
    for(unsigned int i = 1; i < m_size.m_y; i++)
        m_data[i] = m_data[0] + i * m_size.m_x;
}

template<class T>
Array2D<T>::Array2D(Point s, std::string loading)
{
    m_size = s;
    m_data = new T*[m_size.m_y];
    m_data[0] = new T[m_size.m_x * m_size.m_y];
    for(unsigned int i = 1; i < m_size.m_y; i++)
        m_data[i] = m_data[0] + i * m_size.m_x;
    memcpy(m_data[0],loading.c_str(),sizeof(T) * (m_size.m_x) * (m_size.m_y));
}

template<class T>
Array2D<T>::~Array2D()
{
    delete [] m_data[0];
    delete [] m_data;
}

template<class T>
Array2D<T>::Array2D(const Array2D& other)
{
    m_size = other.m_size;
    m_data = new T*[m_size.m_y];
    m_data[0] = new T[m_size.m_x * m_size.m_y];
    for(unsigned int i = 1; i < m_size.m_y; i++)
        m_data[i] = m_data[0] + i * m_size.m_x;
    memcpy(m_data[0], other.m_data[0], sizeof(T) * (m_size.m_x) * (m_size.m_y));
}

template<class T>
Array2D<T>& Array2D<T>::operator=(const Array2D& rhs)
{
    if (this == &rhs) return *this; // handle self assignment

    delete [] m_data[0];
    delete [] m_data;

    m_size = rhs.m_size;
    m_data = new T*[m_size.m_y];
    m_data[0] = new T[m_size.m_x * m_size.m_y];
    for(unsigned int i = 1; i < m_size.m_y; i++)
        m_data[i] = m_data[0] + i * m_size.m_x;
    memcpy(m_data[0],rhs.m_data[0], sizeof(T) * (m_size.m_x) * (m_size.m_y));

    return *this;
}

template<class T>
int Array2D<T>::operator=(const std::string& rhs)
{
    if(rhs.size() != (m_size.m_x * m_size.m_y))
        return -1;
    memcpy(m_data[0], rhs.c_str(), sizeof(T) * (m_size.m_x) * (m_size.m_y));
    return 0;
}

template<class T>
T* Array2D<T>::operator[](unsigned int subscript)
{
    if(subscript >= m_size.m_y)
        return 0;
    else
        return m_data[subscript];
}

template<class T>
Point Array2D<T>::size()
{
    return m_size;
}

template class Array2D<char>;
template class Array2D<int>;
