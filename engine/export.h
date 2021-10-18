#ifndef __EXPORT_H__
#define __EXPORT_H__
#ifdef _WIN32
    #ifdef NEAPU_ENGINE_EXPORTS
        #define NEAPU_ENGINE_EXPORT __declspec(dllexport)
    #else
        #define NEAPU_ENGINE_EXPORT __declspec(dllimport)
    #endif
#endif
#endif // __EXPORT_H__