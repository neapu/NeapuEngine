#include "NEApp.h"
#include <Windows.h>
#include <winuser.h>
#include "NEScene.h"
using namespace NeapuEngine;

App* g_pInstance = nullptr;
extern "C" LRESULT CALLBACK __WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) 
{
    return g_pInstance->widgetProc(msg, wParam, lParam);
}


App::App(int argc, char** argv) 
    : m_argc(argc)
    , m_argv(argv)
    , m_pCurrentScene(nullptr)
{
    g_pInstance = this;
}

int App::run() 
{
    char szWindowClass[128] = "NEWidget";
    HINSTANCE hIns = GetModuleHandle(0);
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
    if(!hWnd){
        MessageBox(nullptr, "窗口创建失败", "error", 0);
        exit(-1);
    }
    m_hwnd = hWnd;

    ShowWindow(hWnd, SW_SHOW);
    UpdateWindow(hWnd);

    MSG msg = {0};
    while (msg.message != WM_QUIT) {
        if(PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)){
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }
    return msg.message;
}

bool App::addScene(Scene* scene) 
{
    String strSceneName = scene->name();
    if(m_SceneList.find(strSceneName)==m_SceneList.end()){
        m_SceneList[strSceneName] = scene;
        return true;
    }
    return false;
}



LRESULT App::widgetProc(UINT msg, WPARAM wParam, LPARAM lParam) 
{
    switch (msg) {
    case WM_DESTROY:
        PostQuitMessage(0);
    }
    return DefWindowProc(m_hwnd, msg, wParam, lParam);
}

