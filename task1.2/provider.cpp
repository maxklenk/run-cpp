
#include "provider.h"

#include <sstream>

// define PROVIDER_NAME using compiler options
#define PROVIDER_NAME "Max Klenk and Tobias Wollowski"

namespace provider
{


std::string providerInfo(const bool date)
{
    auto stream = std::stringstream { };

    // output provider name using the PROVIDER_NAME defined for compilation
    stream << PROVIDER_NAME << " ";

    // if date is true, output the date of compilation as well using predefined c++ macros
    if(date)
    {
        stream << __DATE__ << " " << __TIME__ << std::endl;
    }

    return stream.str();
}


}