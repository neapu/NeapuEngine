#ifndef __NECHARACTER_H__
#define __NECHARACTER_H__

#include "NESpirit.h"
#include "NEVector.h"
namespace NeapuEngine{
enum class MoveMode{
    Free,
    SingleDirection,
};
class Character: public Spirit{
public:
    Character(String strName, GameObject* pParent);
    void setMoveMode(MoveMode m) {m_MoveMode = m;};
    // void MoveTo(const Vector2 pos);
protected:
    MoveMode m_MoveMode;
    float m_fHorizontalSpeed;
    float m_fVerticalSpeed;
    
};
}
#endif // __NECHARACTER_H__