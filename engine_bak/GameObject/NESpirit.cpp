#include "NESpirit.h"
using namespace NeapuEngine;

Spirit::Spirit(String strName, GameObject* pParent)
	: GameObject(strName, pParent)
	, m_nImageId(-1)
    , m_fPixelsPerMeter(100.f)
{
}

void Spirit::setImage(int nId, const Rect& rcImageRect) 
{
    m_nImageId=nId;
    m_rcImageRect=rcImageRect;
    m_vSize.x = m_rcImageRect.width/m_fPixelsPerMeter;
	m_vSize.y = m_rcImageRect.height/m_fPixelsPerMeter;
}


void Spirit::setPixelsPerMeter(float f) 
{
    m_fPixelsPerMeter=f;
    m_vSize.x = m_rcImageRect.width/m_fPixelsPerMeter;
	m_vSize.y = m_rcImageRect.height/m_fPixelsPerMeter;
}
