#ifndef __NECAMARA_H__
#define __NECAMARA_H__

#include "NEVector.h"
namespace NeapuEngine{
class Camara{
public:
    Camara(Vector2 vPos, Vector2 vSize) : m_vPosition(vPos), m_vSize(vSize) {}
    void setPosition(Vector2 v) {m_vPosition=v;}
    void setSize(Vector2 v) {m_vSize=v;}

    Vector2 getPosition() {return m_vPosition;}
    Vector2 getSize() {return m_vSize;}
protected:
    Vector2 m_vPosition;
    Vector2 m_vSize;
};
}
#endif // __NECAMARA_H__