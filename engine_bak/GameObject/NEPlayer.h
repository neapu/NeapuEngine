#ifndef __NEPLAYER_H__
#define __NEPLAYER_H__
#include "NECharacter.h"

namespace NeapuEngine {
class Player:public Character{
public:
    Player(String strName, GameObject* pParent);
protected:
    virtual void fixedTick() override;
private:
    unsigned long m_nKeyLeft;
    unsigned long m_nKeyRight;
    unsigned long m_nKeyUp;
    unsigned long m_nKeyDown;
};
}
#endif // __NEPLAYER_H__