#ifndef __NESCENE_H__
#define __NESCENE_H__
#include "NEString.h"
#include <map>
#include "export.h"
namespace NeapuEngine {
class GameObject;
class Camara;
class NEAPU_ENGINE_EXPORT Scene{
public:
    Scene(String strName);
    String name() {return m_strName;}
protected:
    std::map<String, GameObject*> m_GameObjectList;
    Camara* m_pCamara;
    String m_strName;
};
}
#endif // __NESCENE_H__