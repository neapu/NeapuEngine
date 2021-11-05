#ifndef __NEWINDOW_H__
#define __NEWINDOW_H__
#include "NEGame.h"
#include <Windows.h>
extern "C" LRESULT CALLBACK __WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

namespace NeapuEngine{
class Renderer;
class Window{
public:
    Window(int argc, char** argv);
    int init();
    int run();
    static Window* instance() {return m_pInstance;}
private:
    LRESULT widgetProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
    friend LRESULT CALLBACK ::__WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
    void onRender(HWND hWnd);
    void tick();

    void onWindowInit(HWND hWnd);
private:
    int m_argc;
    char** m_argv;
    static Window* m_pInstance;
    HWND m_hwnd;
    //标记哪些按键被按下
    //对应虚拟键码为1则为按下
    //虚拟键码：https://docs.microsoft.com/en-us/windows/win32/inputdev/virtual-key-codes
    unsigned char m_keyMap[256];
    
    Game* m_pGameInstance;
    Renderer* m_pRenderer;
};
}
#endif // __NEWINDOW_H__