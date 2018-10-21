#include "build.h"

const char *LM_buildarch (void) {
    const char *arch;

#if defined( __x86_64__) || defined(_M_X64)
    arch = "amd64";
#warning This Arch not supported yet!!!!
#elif defined(__i386__) || defined(_X86_) || defined(_M_IX86)
    arch = "i386";
#elif defined __aarch64__
    arch = "aarch64";
#elif defined __arm__ || defined _M_ARM
    arch = "arm";
#endif

    return arch;
}

const char *LM_buildos (void)
{
        const char *os;
        
#if defined(_WIN32) && defined(_MSC_VER)
        os = "Win32";
//#error Os not supported yet!!!!
#elif defined(_WIN32) && defined(__MINGW32__)
        os = "Win32-MinGW";
//#error Os not supported yet!!!!
#elif defined(__ANDROID__)
        os = "Android";
#error Os not supported yet!!!!
#elif defined(__SAILFISH__)
        os = "SailfishOS";
#error Os not supported yet!!!!
#elif defined(__linux__)
        os = "Linux";
#elif defined(__APPLE__)
        os = "Apple";
#error Os not supported yet!!!!
#elif defined(__FreeBSD__)
        os = "FreeBSD";
#error Os not supported yet!!!!
#elif defined(__NetBSD__)
        os = "NetBSD";
#error Os not supported yet!!!!
#elif defined(__OpenBSD__)
        os = "OpenBSD";
#error Os not supported yet!!!!
#else
#error You os none in list!!!
#endif
        return os;
}

const char *LM_buildhlsdk (void) {
    const char *headers;

#if defined( XASH3D )
    headers = "xash3d-hlsdk";
#elif defined( GOLDSRC_PRIVATE )
    headers = "hlsdk";
#else
#error Missing define
#endif
    return headers;
}

const char *LM_buildversion (void)
{
    const char *version;
    
#if defined (LUAMOD_VERSION)
    version = LUAMOD_VERSION;
#else
#error NO LUAMOD_VERSION
#endif
    return version;
}
