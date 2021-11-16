#include "NERenderer.h"
#include <d2d1.h>
#include <wincodec.h>
#include "NEImage.h"
#include "NESpirit.h"
using namespace NeapuEngine;
#define NE_ASSERT(b, msg) if(FAILED(b)){MessageBox(nullptr, msg, "error", 0);exit(-1);}

void Renderer::init(HWND hWnd) 
{
    HRESULT hr = S_OK;
    hr = CoInitialize(nullptr);
    NE_ASSERT(hr, "CoInitialize failed!");
    hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &m_pFactory);
    NE_ASSERT(hr, "Create factory failed!");
    RECT rc;
    GetClientRect(hWnd, &rc);
    D2D1_SIZE_U size = D2D1::SizeU(rc.right, rc.bottom);
    hr = m_pFactory->CreateHwndRenderTarget(
        D2D1::RenderTargetProperties(),
        D2D1::HwndRenderTargetProperties(hWnd, size),
        &m_pRenderTarget
    );
    NE_ASSERT(hr, "Create Render Target failed!");
    hr = CoCreateInstance(
        CLSID_WICImagingFactory,
        NULL,
        CLSCTX_INPROC_SERVER,
        IID_PPV_ARGS(&m_pIWICFactory)
    );
    NE_ASSERT(hr, "Create IWICFactory failed!");
    m_hWnd = hWnd;
}

void Renderer::render(Scene* pScene) 
{
    Camara* pCamara = pScene->getCamara();
    RECT rc;
    GetClientRect(m_hWnd, &rc);
    //每米像素数=窗口大小(像素)/摄像机大小(米)
    float fPixelPreUnitX = rc.right / pCamara->getSize().x;
    float fPixelPreUnitY = rc.bottom / pCamara->getSize().y;
    Vector2 vCamaraPos = pCamara->getPosition();
    pScene->onRender([&, this](GameObject* pGameObject, void* ptr){
        Spirit *pSpirit = dynamic_cast<Spirit*>(pGameObject);
        if (pSpirit) {
            Vector2 vDisplayPos = pSpirit->position() - vCamaraPos;
            //游戏坐标转换成窗口坐标
            D2D1_RECT_F desRc = D2D1::RectF(
                vDisplayPos.x * fPixelPreUnitX,
                rc.right - vDisplayPos.y * fPixelPreUnitY,//笛卡尔坐标系的Y轴和窗口坐标系的Y轴是相反的
                vDisplayPos.x * fPixelPreUnitX + pSpirit->size().x * fPixelPreUnitX,
                (rc.right - vDisplayPos.y * fPixelPreUnitY) + pSpirit->size().y * fPixelPreUnitY
            );
            int nImgId = pSpirit->imageId();
            Image* img = this->getImage(pSpirit->imageId());
            if (!img)return;
        }
    }, nullptr);
}

void Renderer::loadImage(std::map<int, String> imageList) 
{
    for(auto item:imageList){
        Image* img = new Image();
        if(img->loadImage(item.second, m_pIWICFactory, m_pRenderTarget)){
            m_ImageList[item.first] = img;
        }else{
            delete img;
        }
    }
}

Image* NeapuEngine::Renderer::getImage(int nId)
{
    if (m_ImageList.find(nId) == m_ImageList.end()) {
        return nullptr;
    }
    return m_ImageList.at(nId);
}
