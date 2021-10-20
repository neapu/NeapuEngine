#ifndef __NEAPP_H__
#define __NEAPP_H__
#include <Windows.h>
#include <map>
#include "NEString.h"
#include "export.h"
#include "NEImage.h"

struct ID2D1Factory;
struct ID2D1HwndRenderTarget;
struct IWICImagingFactory;

extern "C" LRESULT CALLBACK __WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
namespace NeapuEngine {
class Scene;
class NEAPU_ENGINE_EXPORT App{
public:
    App(int argc, char** argv);
    int init(HINSTANCE hIns);
    int run();

public:
    bool addScene(Scene* scene);
    int addImage(String strPath);

protected:
    void onInit();
    void onRender();
    void onResize();

    void tick();
private:
    LRESULT widgetProc(UINT msg, WPARAM wParam, LPARAM lParam);
    friend LRESULT CALLBACK ::__WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
private:
    int m_argc;
    char** m_argv;
    HWND m_hwnd;
    std::map<String, Scene*> m_SceneList;
    String m_strCurrentSceneName;
    Scene* m_pCurrentScene;
    ID2D1Factory* m_pFactory;
    ID2D1HwndRenderTarget* m_pRenderTarget;
    IWICImagingFactory* m_pIWICFactory;
    std::map<int, Image*> m_ImageList;
};
// LRESULT __WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
}
#endif // __NEAPP_H__