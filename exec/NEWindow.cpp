#include "NEWindow.h"
#include <stdio.h>
#include <d2d1.h>
#include <wincodec.h>
using namespace NeapuEngine;
#define NE_ASSERT(b, msg) if(FAILED(b)){MessageBox(nullptr, msg, "error", 0);exit(-1);}

extern "C" LRESULT CALLBACK __WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) 
{
    return Window::instance()->widgetProc(hWnd, msg, wParam, lParam);
}

Window* Window::m_pInstance=nullptr;

Window::Window(int argc, char** argv) 
    : m_argc(argc)
    , m_argv(argv)
    , m_hwnd(nullptr)
{
    m_pInstance=this;
}

LRESULT Window::widgetProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) 
{
    switch (msg) {
    case WM_CREATE:onWindowInit(hWnd);  break;
    case WM_PAINT:onRender(hWnd);  break;
    // case WM_SIZE:onResize(hWnd);  break;
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

void Window::onWindowInit(HWND hWnd) 
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

int Window::init() 
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

int Window::run() 
{
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
