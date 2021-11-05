#include "NEScene.h"
using namespace NeapuEngine;

Scene::Scene(String strName, GameObject* pParent) 
    : GameObject(strName, pParent)
    , m_Camara({0, 0}, {8, 6})
{
    
}
