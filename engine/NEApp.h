#ifndef __NEAPP_H__
#define __NEAPP_H__
#include <Windows.h>
#include <map>
#include "NEString.h"
#include "export.h"
extern "C" LRESULT CALLBACK __WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
namespace NeapuEngine {
class Scene;
class NEAPU_ENGINE_EXPORT App{
public:
    App(int argc, char** argv);
    int run();

public:
    bool addScene(Scene* scene);
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
    
};
// LRESULT __WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
}
#endif // __NEAPP_H__