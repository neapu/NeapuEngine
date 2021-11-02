#include "NEImage.h"
#include <d2d1.h>
#include <minwindef.h>
#include <wincodec.h>
#include <winnt.h>
using namespace NeapuEngine;

Image::Image() 
    : m_pBitmap(nullptr)
{
    
}

Image::Image(Image&& img) 
{
    m_pBitmap = img.m_pBitmap;
    img.m_pBitmap = nullptr;
}

Image::~Image() 
{
    if(m_pBitmap)m_pBitmap->Release();
}

bool Image::loadImage(String strPath, IWICImagingFactory* pWICIFactory, ID2D1HwndRenderTarget* pRenderTarget) 
{
    IWICBitmapDecoder* pDecoder = nullptr;
    IWICBitmapFrameDecode* pFrame = nullptr;
    IWICFormatConverter* pConverter = nullptr;
    LRESULT hr = S_OK;
    hr = pWICIFactory->CreateDecoderFromFilename(
        strPath.toWString().c_str(), 
        nullptr,
        GENERIC_READ,
        WICDecodeMetadataCacheOnLoad,
        &pDecoder
    );
    if(FAILED(hr))return false;
    hr = pDecoder->GetFrame(0, &pFrame);
    if(FAILED(hr))return false;
    hr = pWICIFactory->CreateFormatConverter(&pConverter);
    if(FAILED(hr))return false;
    hr = pConverter->Initialize(
        pFrame,
        GUID_WICPixelFormat32bppPBGRA,
        WICBitmapDitherTypeNone,
        0,
        0.f,
        WICBitmapPaletteTypeCustom
    );
    if(FAILED(hr))return false;
    hr = pRenderTarget->CreateBitmapFromWicBitmap(
        pConverter,
        nullptr,
        &m_pBitmap
    );
    if(FAILED(hr))return false;
    pDecoder->Release();
    pFrame->Release();
    pConverter->Release();
    return true;
}