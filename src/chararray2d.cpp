#include "Point.h"
#include <string>
#include <cstring>

#include "chararray2d.h"

CharArray2D::CharArray2D()
{
    m_size = Point(2,2);
    m_data = new char*[m_size.m_y];
    m_data[0] = new char[m_size.m_x * m_size.m_y];
    for(unsigned int i = 1; i < m_size.m_y; i++)
        m_data[i] = m_data[0] + i * m_size.m_x;
}

CharArray2D::CharArray2D(Point s)
{
    m_size = s;
    m_data = new char*[m_size.m_y];
    m_data[0] = new char[m_size.m_x * m_size.m_y];
    for(unsigned int i = 1; i < m_size.m_y; i++)
        m_data[i] = m_data[0] + i * m_size.m_x;
}

CharArray2D::CharArray2D(Point s, std::string loading)
{
    m_size = s;
    m_data = new char*[m_size.m_y];
    m_data[0] = new char[m_size.m_x * m_size.m_y];
    for(unsigned int i = 1; i < m_size.m_y; i++)
        m_data[i] = m_data[0] + i * m_size.m_x;
    memcpy(m_data[0],loading.c_str(),sizeof(char) * (m_size.m_x) * (m_size.m_y));
}

CharArray2D::~CharArray2D()
{
    delete [] m_data[0];
    delete [] m_data;
}

CharArray2D::CharArray2D(const CharArray2D& other)
{
    m_size = other.m_size;
    m_data = new char*[m_size.m_y];
    m_data[0] = new char[m_size.m_x * m_size.m_y];
    for(unsigned int i = 1; i < m_size.m_y; i++)
        m_data[i] = m_data[0] + i * m_size.m_x;
    memcpy(m_data[0], other.m_data[0], sizeof(char) * (m_size.m_x) * (m_size.m_y));
}

CharArray2D& CharArray2D::operator=(const CharArray2D& rhs)
{
    if (this == &rhs) return *this; // handle self assignment

    delete [] m_data[0];
    delete [] m_data;

    m_size = rhs.m_size;
    m_data = new char*[m_size.m_y];
    m_data[0] = new char[m_size.m_x * m_size.m_y];
    for(unsigned int i = 1; i < m_size.m_y; i++)
        m_data[i] = m_data[0] + i * m_size.m_x;
    memcpy(m_data[0],rhs.m_data[0], sizeof(char) * (m_size.m_x) * (m_size.m_y));

    return *this;
}

int CharArray2D::operator=(const std::string& rhs)
{
    if(rhs.size() != (m_size.m_x * m_size.m_y))
        return -1;
    memcpy(m_data[0], rhs.c_str(), sizeof(char) * (m_size.m_x) * (m_size.m_y));
    return 0;
}

char* CharArray2D::operator[](int subscript)
{
    if(subscript >= m_size.m_y || subscript < 0)
        return 0;
    else
        return m_data[subscript];
}

Point CharArray2D::size()
{
    return m_size;
}
