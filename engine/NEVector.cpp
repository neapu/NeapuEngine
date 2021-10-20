#include "NEVector.h"
using namespace NeapuEngine;

Vector2 Vector2::operator+(const Vector2& v2){
    return Vector2(x+v2.x, y+v2.y);
}

Vector2 Vector2::operator-(const Vector2& v2){
    return Vector2(x-v2.x, y-v2.y);
}