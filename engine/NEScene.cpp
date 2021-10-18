#include "NEScene.h"
#include "NECamara.h"
using namespace NeapuEngine;

Scene::Scene(String strName)
    : m_strName(strName)
{
    m_pCamara = new Camara();
}