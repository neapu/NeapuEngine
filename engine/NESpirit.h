#ifndef __NESPIRIT_H__
#define __NESPIRIT_H__
#include "NEGameObject.h"
#include "NERect.h"
#include "export.h"
struct ID2D1HwndRenderTarget;
namespace NeapuEngine{
    class Camara;
class NEAPU_ENGINE_EXPORT Spirit: public GameObject{
public:
    Spirit(String name, int nImgId, const Rect& rcImageRect, int nLayer = 0, GameObject* pParam = nullptr);
    int imageId() { return m_nImageId; }
    Rect imageRect() { return m_rcImageRect; }
    virtual void render(ID2D1HwndRenderTarget* pRenderTarget, const Camara* camara, std::map<int, Image*>& imageList) override;
private:
    int m_nImageId;
    Rect m_rcImageRect;
};
}
#endif // __NESPIRIT_H__