#ifndef __NESCENE_H__
#define __NESCENE_H__

#include "NEGameObject.h"
#include "NECamara.h"
namespace NeapuEngine {
class Scene: public GameObject{
public:
    Scene(String strName, GameObject* pParent = nullptr);
protected:
    Camara m_Camara;
};
}
#endif // __NESCENE_H__