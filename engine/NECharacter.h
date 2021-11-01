#ifndef __NECHARACTER_H__
#define __NECHARACTER_H__

#include "NESpirit.h"
namespace NeapuEngine{
enum class MoveMode{
    Free,
    SingleDirection,
};
class Character: public Spirit{
public:
    Character(String strName, GameObject* pParent);
    void setMoveMode(MoveMode m) {m_MoveMode = m;};
protected:
    virtual void fixedTick() override;
private:
    MoveMode m_MoveMode;
    float m_fHorizontalSpeed;
    float m_fVerticalSpeed;
    unsigned long m_nKeyLeft;
    unsigned long m_nKeyRight;
    unsigned long m_nKeyUp;
    unsigned long m_nKeyDown;
};
}
#endif // __NECHARACTER_H__