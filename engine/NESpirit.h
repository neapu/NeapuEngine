#ifndef __NESPIRIT_H__
#define __NESPIRIT_H__
#include "NEGameObject.h"
#include "NERect.h"
#include "export.h"
namespace NeapuEngine{

class NEAPU_ENGINE_EXPORT Spirit: public GameObject{
public:
    Spirit(String name, int nImgId, const Rect& rcImageRect) 
        : GameObject(name),  m_nImageId(nImgId), m_rcImageRect(rcImageRect) 
    {}
    int imageId() { return m_nImageId; }
    Rect imageRect() { return m_rcImageRect; }
private:
    int m_nImageId;
    Rect m_rcImageRect;
};
}
#endif // __NESPIRIT_H__