
#pragma once

#include <string>

// define PROVIDER_API for cross-platform use
// Generic helper definitions for shared library support
#if defined _WIN32 || defined __CYGWIN__
    #define PROVIDER_HELPER_DLL_IMPORT __declspec(dllimport)
    #define PROVIDER_HELPER_DLL_EXPORT __declspec(dllexport)
    //#define PROVIDER_HELPER_DLL_LOCAL
#else
    #if __GNUC__ >= 4
        #define PROVIDER_HELPER_DLL_IMPORT __attribute__ ((visibility ("default")))
        #define PROVIDER_HELPER_DLL_EXPORT __attribute__ ((visibility ("default")))
        //#define PROVIDER_HELPER_DLL_LOCAL  __attribute__ ((visibility ("hidden")))
    #else
        #define PROVIDER_HELPER_DLL_IMPORT
        #define PROVIDER_HELPER_DLL_EXPORT
        //#define PROVIDER_HELPER_DLL_LOCAL
    #endif
#endif

// Now we use the generic helper definitions above to define PROVIDER_API and PROVIDER_LOCAL.
// PROVIDER_API is used for the public API symbols. It either DLL imports or DLL exports (or does nothing for static build)
// PROVIDER_LOCAL is used for non-api symbols.

#ifdef PROVIDER_DLL // defined if PROVIDER is compiled as a DLL
    #ifdef PROVIDER_DLL_EXPORTS // defined if we are building the PROVIDER DLL (instead of using it)
        #define PROVIDER_API PROVIDER_HELPER_DLL_EXPORT
    #else
        #define PROVIDER_API PROVIDER_HELPER_DLL_IMPORT
    #endif // PROVIDER_DLL_EXPORTS
    //#define PROVIDER_LOCAL PROVIDER_HELPER_DLL_LOCAL
#else // PROVIDER_DLL is not defined: this means PROVIDER is a static lib.
    #define PROVIDER_API
    //#define PROVIDER_LOCAL
#endif // PROVIDER_DLL

namespace provider
{


PROVIDER_API std::string providerInfo(bool date = false);


} // namespace provider
