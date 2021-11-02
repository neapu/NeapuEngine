#ifndef __NECAMARA_H__
#define __NECAMARA_H__
#include "NEVector.h"
namespace NeapuEngine {
class Camara{
public:
    void setPosition(float x, float y) {
        m_vPosition.x = x;
        m_vPosition.y = y;
    }
    Vector2 m_vPosition;
    Vector2 m_vSize;
};
}
#endif // __NECAMARA_H__