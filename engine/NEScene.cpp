#include "NEScene.h"
#include "NECamara.h"
#include <d2d1.h>
#include <d2d1helper.h>
#include <dcommon.h>
#include "NESpirit.h"
#include "NEImage.h"
using namespace NeapuEngine;

Scene::Scene(String strName)
    : m_strName(strName)
{
    m_pCamara = new Camara();
    m_pCamara->setPosition(-4, -3);
}

bool NeapuEngine::Scene::addGameObject(GameObject* pGameObject)
{
    if (m_GameObjectList.find(pGameObject->name()) != m_GameObjectList.end()) {
        return false;
    }
    m_GameObjectList[pGameObject->name()] = pGameObject;
    return true;
}

void Scene::redner(ID2D1HwndRenderTarget* pRenderTarget, std::map<int, Image*>& imageList)
{
    pRenderTarget->BeginDraw();
    Vector2 camaraPos = m_pCamara->m_vPosition;
    for(auto item: m_GameObjectList){
        Spirit* sp = dynamic_cast<Spirit*>(item.second);
        if(sp){
            Vector2 pos = sp->position();
            Vector2 size = sp->size();
            Vector2 displayPos = pos - camaraPos;
            D2D1_RECT_F desRc = D2D1::RectF(
                displayPos.x * 100, 
                displayPos.y * 100, 
                displayPos.x * 100 + size.x * 100, 
                displayPos.y * 100 + size.y * 100
            );
            int nImgId = sp->imageId();
            Rect imgRc = sp->imageRect();
            Image* img = imageList[nImgId];
            if (!img) {
                MessageBox(nullptr, "image id error", "error", 0);
                exit(-1);
            }
            D2D1_RECT_F srcRc = D2D1::RectF(
                imgRc.x,
                imgRc.y,
                imgRc.x + imgRc.width,
                imgRc.y + imgRc.height
            );
            pRenderTarget->DrawBitmap(
                img->bitmap(),
                desRc,
                1.f,
                D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR,
                srcRc
            );
        }
    }
    pRenderTarget->EndDraw();
}