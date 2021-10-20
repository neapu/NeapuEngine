#ifndef __NEGAMEOBJECT_H__
#define __NEGAMEOBJECT_H__
#include "export.h"
#include "NEVector.h"
#include "NEString.h"
namespace NeapuEngine {
class NEAPU_ENGINE_EXPORT GameObject{
public:
    GameObject(String name) : m_strName(name) {};
    virtual ~GameObject() {}

    Vector2 position() {return m_vPosition;}
    Vector2 size() {return m_vSize;}
    String name() { return m_strName; }
private:
    String m_strName;
    Vector2 m_vPosition;//左上角位置
    Vector2 m_vSize;//宽高
};
}
#endif // __NEGAMEOBJECT_H__