#include "NESpirit.h"
#include "NECamara.h"
#include <d2d1.h>
#include "NEImage.h"
using namespace NeapuEngine;

Spirit::Spirit(String name, int nImgId, const Rect& rcImageRect, int nLayer, GameObject* pParam)
	: GameObject(name, nLayer, pParam)
	, m_nImageId(nImgId)
	, m_rcImageRect(rcImageRect)
{
	m_vSize.x = rcImageRect.width/100.f;
	m_vSize.y = rcImageRect.height/100.f;
}

void NeapuEngine::Spirit::render(ID2D1HwndRenderTarget* pRenderTarget, const Camara* camara, std::map<int, Image*>& imageList)
{
    Vector2 camaraPos = camara->m_vPosition;
    Vector2 displayPos = m_vPosition - camaraPos;
    D2D1_RECT_F desRc = D2D1::RectF(
        displayPos.x * 100,
        displayPos.y * 100,
        displayPos.x * 100 + m_vSize.x * 100,
        displayPos.y * 100 + m_vSize.y * 100
    );
    Image* img = imageList[m_nImageId];
    if (!img) {
        MessageBox(nullptr, "image id error", "error", 0);
        exit(-1);
    }
    D2D1_RECT_F srcRc = D2D1::RectF(
        m_rcImageRect.x,
        m_rcImageRect.y,
        m_rcImageRect.x + m_rcImageRect.width,
        m_rcImageRect.y + m_rcImageRect.height
    );
    pRenderTarget->DrawBitmap(
        img->bitmap(),
        desRc,
        1.f,
        D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR,
        srcRc
    );
    GameObject::render(pRenderTarget, camara, imageList);
}
