#include "NECharacter.h"
using namespace NeapuEngine;



Character::Character(String strName, GameObject* pParent) 
    : Spirit(strName, pParent)
    , m_MoveMode(MoveMode::Free)
    , m_fHorizontalSpeed(1)
    , m_fVerticalSpeed(1)
    
{
    
}

