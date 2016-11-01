
#pragma once

#include <string>


// define PROVIDER_API for cross-platform use
#ifdef PROVIDER_API_EXPORTS
  #if defined (_WIN32) 
      #define  PROVIDER_API __declspec(dllexport)
  #else
      #define PROVIDER_API __attribute__ ((visibility ("default")))
  #endif
#else
  #if defined (_WIN32)
      #define  PROVIDER_API __declspec(dllimport)
  #else
      #define PROVIDER_API __attribute__ ((visibility ("hidden")))
  #endif
#endif


namespace provider
{


PROVIDER_API std::string providerInfo(bool date = false);


} // namespace provider
