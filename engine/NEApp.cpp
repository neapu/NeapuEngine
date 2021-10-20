#include "NEApp.h"
#include <Windows.h>
#include <algorithm>
#include <objbase.h>
#include <winuser.h>
#include "NEScene.h"
#include <d2d1.h>
#include <wincodec.h>

using namespace NeapuEngine;
#define NE_ASSERT(b, msg) if(FAILED(b)){exit(-1);MessageBox(nullptr, msg, "error", 0);}

App* g_pInstance = nullptr;
extern "C" LRESULT CALLBACK __WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) 
{
    return g_pInstance->widgetProc(msg, wParam, lParam);
}


App::App(int argc, char** argv) 
    : m_argc(argc)
    , m_argv(argv)
    , m_pCurrentScene(nullptr)
    , m_pFactory(nullptr)
    , m_pRenderTarget(nullptr)
    , m_hwnd(nullptr)
    , m_pIWICFactory(nullptr)
{
    g_pInstance = this;
}

int NeapuEngine::App::init(HINSTANCE hIns)
{
    char szWindowClass[128] = "NEWidget";
    //注册窗口类
    WNDCLASSEXA wcex;

    wcex.cbSize = sizeof(WNDCLASSEXA);

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = __WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hIns;
    wcex.hIcon = NULL;
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = NULL;
    RegisterClassEx(&wcex);

    const char* title = "NeapuGame";
    //创建窗口
    HWND hWnd = CreateWindowA(szWindowClass, title, WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, 800, 600, nullptr, nullptr, hIns, nullptr);
    if (!hWnd) {
        auto err = GetLastError();
        char strErr[128];
        sprintf_s(strErr, "window create failed.%u", err);
        MessageBox(nullptr, strErr, "error", 0);
        exit(-1);
    }
    m_hwnd = hWnd;
    return 0;
}

int App::run() 
{
    

    ShowWindow(m_hwnd, SW_SHOW);
    UpdateWindow(m_hwnd);

    MSG msg = {0};
    while (msg.message != WM_QUIT) {
        if(PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)){
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }else{
            onRender();
        }
        tick();
    }
    return msg.message;
}

bool App::addScene(Scene* scene) 
{
    String strSceneName = scene->name();
    if(m_SceneList.find(strSceneName)==m_SceneList.end()){
        m_SceneList[strSceneName] = scene;
        if(!m_pCurrentScene){
            m_pCurrentScene = scene;
            m_strCurrentSceneName = strSceneName;
        }
        
        return true;
    }
    return false;
}

int App::addImage(String strPath) 
{
    static int id = 0;
    Image *img = new Image();
    if(img->loadImage(strPath, m_pIWICFactory, m_pRenderTarget)){
        m_ImageList[id++]=img;
        return id-1;
    }
    return -1;
}

void App::onInit() 
{
    CoInitialize(nullptr);
    HRESULT hr = S_OK;
    hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &m_pFactory);
    NE_ASSERT(hr, "Create factory failed!");
    RECT rc;
    GetClientRect(m_hwnd, &rc);
    D2D1_SIZE_U size = D2D1::SizeU(rc.right, rc.bottom);
    hr = m_pFactory->CreateHwndRenderTarget(
        D2D1::RenderTargetProperties(),
        D2D1::HwndRenderTargetProperties(m_hwnd, size),
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

void App::onRender() 
{
    if(m_pCurrentScene){
        
    }
}

void App::onResize() 
{
    
}

void App::tick() 
{
    
}



LRESULT App::widgetProc(UINT msg, WPARAM wParam, LPARAM lParam) 
{
    switch (msg) {
    case WM_CREATE:onInit();break;
    case WM_PAINT:onRender();break;
    case WM_SIZE:onResize();break;
    case WM_DESTROY:
        PostQuitMessage(0);
    }
    return DefWindowProc(m_hwnd, msg, wParam, lParam);
}

