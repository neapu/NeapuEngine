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
}

void Renderer::render(Scene* pScene) 
{
    pScene->onRender([this](GameObject* pGameObject, void* ptr){
        Spirit *pSpirt = dynamic_cast<Spirit*>(pGameObject);
        
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