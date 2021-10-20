#ifndef __NEIMAGE_H__
#define __NEIMAGE_H__
#include "NEString.h"
#include "export.h"
struct ID2D1HwndRenderTarget;
struct IWICImagingFactory;
struct ID2D1Bitmap;
namespace NeapuEngine {
class NEAPU_ENGINE_EXPORT Image{
public:
    Image();
    Image(const Image& img) = delete;
    Image(Image&& img);
    ~Image();
    bool loadImage(String strPath, IWICImagingFactory* pWICIFactory, ID2D1HwndRenderTarget* pRenderTarget);
    ID2D1Bitmap* bitmap() { return m_pBitmap; }
private:
    ID2D1Bitmap* m_pBitmap;
};
}
#endif // __NEIMAGE_H__