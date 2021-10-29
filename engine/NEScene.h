#ifndef __NESCENE_H__
#define __NESCENE_H__
#include "NEString.h"
#include <map>
#include "export.h"
struct ID2D1HwndRenderTarget;
namespace NeapuEngine {
class GameObject;
class Camara;
class Image;
class NEAPU_ENGINE_EXPORT Scene{
public:
    Scene(String strName);
    String name() {return m_strName;}
    GameObject* rootGameObject() { return m_pRootGameObject; }
    void redner(ID2D1HwndRenderTarget* pRenderTarget, std::map<int, Image*>& imageList);
    void tick();
    void fixedTick();
protected:
    GameObject* m_pRootGameObject;
    Camara* m_pCamara;
    String m_strName;
};
}
#endif // __NESCENE_H__