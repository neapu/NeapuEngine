#include "NEScene.h"
#include "NECamara.h"
#include <d2d1.h>
#include <d2d1helper.h>
#include <dcommon.h>
#include "NEImage.h"
#include "NEGameObject.h"
using namespace NeapuEngine;

Scene::Scene(String strName)
    : m_strName(strName)
    , m_pRootGameObject(new GameObject("root"))
{
    m_pCamara = new Camara();
    m_pCamara->setPosition(-4, -3);
}


void Scene::redner(ID2D1HwndRenderTarget* pRenderTarget, std::map<int, Image*>& imageList)
{
    pRenderTarget->BeginDraw();
    pRenderTarget->Clear(D2D1::ColorF(0, 0, 0, 1));
    m_pRootGameObject->render(pRenderTarget, m_pCamara, imageList);
    pRenderTarget->EndDraw();
}

void Scene::tick() 
{
    m_pRootGameObject->tick();
}

void Scene::fixedTick() 
{
    m_pRootGameObject->fixedTick();
}
