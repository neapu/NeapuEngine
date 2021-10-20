#ifndef __NEVECTOR_H__
#define __NEVECTOR_H__
#include "export.h"
namespace NeapuEngine {
struct NEAPU_ENGINE_EXPORT Vector2{
    Vector2(float _x = 0, float _y = 0) : x(_x), y(_y) {}
    float x;
    float y;
    Vector2 operator+(const Vector2& v2);
    Vector2 operator-(const Vector2& v2);
};
}
#endif // __NEVECTOR_H__