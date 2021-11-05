#ifndef __NERENDERER_H__
#define __NERENDERER_H__
#include "NEScene.h"
#include "NEString.h"
#include <Windows.h>
struct ID2D1Factory;
struct ID2D1HwndRenderTarget;
struct IWICImagingFactory;
namespace NeapuEngine {
class Image;
class Renderer{
public:
    void init(HWND hWnd);
    void render(Scene* pScene);
    void loadImage(std::map<int, String> imageList);
private:
    ID2D1Factory* m_pFactory;
    ID2D1HwndRenderTarget* m_pRenderTarget;
    IWICImagingFactory* m_pIWICFactory;
    std::map<int, Image*> m_ImageList;
};
}
#endif // __NERENDERER_H__