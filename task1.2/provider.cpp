
#include "provider.h"

#include <sstream>

// ToDo: define PROVIDER_NAME using compiler options


namespace provider
{


std::string providerInfo(const bool date)
{
    auto stream = std::stringstream { };

    // ToDo: output provider name using the PROVIDER_NAME defined for compilation

    // ToDo: if date is true, output the date of compilation as well using predefined c++ macros
    
    return stream.str();
}


}