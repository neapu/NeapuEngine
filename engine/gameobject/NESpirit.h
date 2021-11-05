#ifndef __NESPIRIT_H__
#define __NESPIRIT_H__
#include "NEGameObject.h"
#include "NERect.h"
#include "export.h"

namespace NeapuEngine{
class NEAPU_ENGINE_EXPORT Spirit: public GameObject{
public:
    Spirit(String strName, GameObject* pParent = nullptr);
    virtual ~Spirit();
    void setImage(int nId, const Rect& rcImageRect);
    int imageId() { return m_nImageId; }
    Rect imageRect() { return m_rcImageRect; }
    void setPixelsPerMeter(float f);
private:
    int m_nImageId;
    Rect m_rcImageRect;
    float m_fPixelsPerMeter;
};
}
#endif // __NESPIRIT_H__