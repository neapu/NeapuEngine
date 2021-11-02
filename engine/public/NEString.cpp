#include "NEString.h"
#include <corecrt_malloc.h>
#include <string.h>
#include <string>
#ifdef _WIN32
#include <clocale>
#include <Windows.h>
#endif
using namespace NeapuEngine;
#define BASE_LEN 1024
ByteArray::ByteArray() 
    : m_max(BASE_LEN)
    , m_data(nullptr)
    , m_len(0)
{
    m_data = static_cast<char*>(malloc(BASE_LEN));
}

ByteArray::ByteArray(const ByteArray& data) : ByteArray()
{
    append(data);
}

ByteArray::ByteArray(ByteArray&& data) 
{
    m_data = data.m_data;
    data.m_data = nullptr;
    m_len = data.m_len;
    data.m_len = 0;
    m_max = data.m_max;
    data.m_max = 0;
}

ByteArray::ByteArray(const char* data, size_t len) : ByteArray()
{
    append(data, len);
}

ByteArray::~ByteArray() 
{
    if(m_data)free(m_data);
}

ByteArray& ByteArray::append(const ByteArray& data) 
{
    this->append(data.m_data, data.m_len);
    return *this;
}

ByteArray& ByteArray::append(const char* data, size_t len) 
{
    if(len==0)return (*this);
    if(len+m_len>=m_max)
    {
        extend(len+m_len);
    }
    memcpy(m_data+m_len, data, len);
    m_len += len;
    return (*this);
}

std::wstring ByteArray::toWString() 
{
    setlocale(LC_ALL, "chs");
    int len = MultiByteToWideChar(CP_ACP, 0, m_data, m_len, nullptr, 0);
    int mallocLen = sizeof(wchar_t*)*(len+1);
    wchar_t* temp = (wchar_t*)malloc(mallocLen);
    len = MultiByteToWideChar(CP_ACP, 0, m_data, m_len, temp, len);
    std::wstring strRst(temp, len);
    free(temp);
    return strRst;
}

void ByteArray::clear() 
{
    if(m_data && m_len!=0)
        memset(m_data, 0, m_len);
    m_len=0;
}

void ByteArray::extend(size_t len) 
{
    size_t newlen = len+BASE_LEN-(len%BASE_LEN);
    m_data = static_cast<char*>(realloc(m_data, newlen));
    if(!m_data)
    {
        perror("realloc error");
        _exit(-1);
    }
    memset(m_data+m_max, 0, newlen-m_max);
    m_max = newlen;
}

