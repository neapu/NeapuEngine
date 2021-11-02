#ifndef __NERECT_H__
#define __NERECT_H__
#include "export.h"
namespace NeapuEngine{
struct NEAPU_ENGINE_EXPORT Rect{
    Rect(int _x = 0, int _y = 0, int _width = 0, int _height = 0) 
        : x(_x), y(_y), width(_width), height(_height)
    {}
    int x;
    int y;
    int width;
    int height;
};
}
#endif // __NERECT_H__