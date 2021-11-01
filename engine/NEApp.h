#ifndef __NEAPP_H__
#define __NEAPP_H__
#include <Windows.h>
#include <map>
#include <set>
#include "NEString.h"
#include "export.h"
#include "NEImage.h"
#include <functional>
#pragma warning(disable: 4251)//禁用stl实例类导出警告

struct ID2D1Factory;
struct ID2D1HwndRenderTarget;
struct IWICImagingFactory;
using timerCallback = std::function<bool()>;
extern "C" LRESULT CALLBACK __WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
namespace NeapuEngine {
class Scene;
class NEAPU_ENGINE_EXPORT App{
public:
    App(int argc, char** argv);
    int init();
    int run();
    static App* instance() {return m_pInstance;}

    bool isKeyDown(unsigned long keyCode);
public:
    bool addScene(Scene* scene);
    int addImage(String strPath);
    int addTimer(long timeout, timerCallback cb);
    void removeTimer(int id);

protected:
    void onInit(HWND hWnd);
    void onRender(HWND hWnd);
    void onResize(HWND hWnd);

    void tick();
    void fixedTick();
private:
    LRESULT widgetProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
    friend LRESULT CALLBACK ::__WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
    void updateTimers();
private:
    int m_argc;
    char** m_argv;
    static App* m_pInstance;
    HWND m_hwnd;
    std::map<String, Scene*> m_SceneList;
    String m_strCurrentSceneName;
    Scene* m_pCurrentScene;
    ID2D1Factory* m_pFactory;
    ID2D1HwndRenderTarget* m_pRenderTarget;
    IWICImagingFactory* m_pIWICFactory;
    std::map<int, Image*> m_ImageList;
    //标记哪些按键被按下
    //对应虚拟键码为1则为按下
    //虚拟键码：https://docs.microsoft.com/en-us/windows/win32/inputdev/virtual-key-codes
    unsigned char m_keyMap[256];
    //简单定时器
    
    int m_nTimerIdCount;
    struct TimerInfo{
        int id;
        long timeout;
        long last;
        timerCallback cb;
    };
    std::map<int, TimerInfo> m_Timers;
};
// LRESULT __WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
}
#endif // __NEAPP_H__