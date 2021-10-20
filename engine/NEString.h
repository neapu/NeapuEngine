#ifndef __NSSTRING_H__
#define __NSSTRING_H__

#include <string>
#include <vector>
#include "export.h"
namespace NeapuEngine {
class NEAPU_ENGINE_EXPORT ByteArray{
public:
    static size_t npos;
    ByteArray();
    ByteArray(const ByteArray& data);
    ByteArray(ByteArray&& data);
    ByteArray(const char* data, size_t len);
    ByteArray(const char* str) : ByteArray(str, strlen(str)) {}
    virtual ~ByteArray();

    ByteArray& append(const ByteArray& data);
    ByteArray& append(const char* data, size_t len);

    char* ptr() {return m_data;}
    const char* data() const {return m_data;}
    std::wstring toWString();

    void clear();

    void operator=(const ByteArray& ba) {
        clear();
        append(ba);
    }
    inline bool operator<(const ByteArray& str) const { return strcmp(this->data(), str.data()) < 0; }
protected:
    void extend(size_t len);
protected:
    char* m_data;
    size_t m_len;
    size_t m_max;
};
typedef ByteArray String;
}
#endif // __NSSTRING_H__