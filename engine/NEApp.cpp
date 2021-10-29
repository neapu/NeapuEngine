#include "NEApp.h"
#include <Windows.h>
#include <algorithm>
#include <objbase.h>
#include <synchapi.h>
#include <winuser.h>
#include "NEScene.h"
#include <d2d1.h>
#include <wincodec.h>

using namespace NeapuEngine;
#define NE_ASSERT(b, msg) if(FAILED(b)){MessageBox(nullptr, msg, "error", 0);exit(-1);}

// App* g_pInstance = nullptr;
App* App::m_pInstance = nullptr;
extern "C" LRESULT CALLBACK __WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) 
{
    return App::instance()->widgetProc(hWnd, msg, wParam, lParam);
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
    // g_pInstance = this;
    m_pInstance = this;
    memset(m_keyMap, 0, 256);
}

bool App::isKeyDown(unsigned long keyCode) 
{
    return m_keyMap[keyCode]==1;
}

int NeapuEngine::App::init()
{
    char szWindowClass[128] = "NEWidget";
    //注册窗口类
    WNDCLASSEXA wcex;
    HINSTANCE hIns = GetModuleHandle(0);
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
    ATOM hr = RegisterClassEx(&wcex);

    const char* title = "NeapuGame";
    //创建窗口
    HWND hWnd = CreateWindowA(szWindowClass, title, WS_OVERLAPPEDWINDOW^ WS_THICKFRAME,//禁止改变窗口大小
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
    int n = SetTimer(nullptr, 1, 1000, [](HWND hwnd, UINT, UINT_PTR, DWORD){
        int i=0;
    });
    ShowWindow(m_hwnd, SW_SHOW);
    UpdateWindow(m_hwnd);

    MSG msg = {0};
    while (msg.message != WM_QUIT) {
        if(PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)){
            if(msg.message == WM_TIMER){
                Sleep(1);
            }
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else {
            onRender(m_hwnd);
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

void App::onInit(HWND hWnd)
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

void App::onRender(HWND hWnd)
{
    if(m_pCurrentScene){
        m_pCurrentScene->redner(m_pRenderTarget, m_ImageList);
    }
}

void App::onResize(HWND hWnd)
{
    
}

void App::tick() 
{
    if(m_pCurrentScene){
        m_pCurrentScene->tick();
    }
}

void App::fixedTick() 
{
    if(m_pCurrentScene){
        m_pCurrentScene->fixedTick();
    }
}



LRESULT App::widgetProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg) {
    case WM_CREATE:onInit(hWnd);  break;
    case WM_PAINT:onRender(hWnd);  break;
    case WM_SIZE:onResize(hWnd);  break;
    case WM_TIMER:
        if(wParam==1){
            fixedTick();
        }
        break;
    case WM_KEYDOWN:{
        m_keyMap[wParam]=1;
    }break;
    case WM_KEYUP:{
        m_keyMap[wParam]=0;
    }break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, msg, wParam, lParam);
    }
    return 0;
}

