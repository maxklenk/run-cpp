
#pragma once


#include <iostream>


// Do not edit this class, it is designed to work for both solutions
class ISBN
{
public:
    enum class Type : bool {
        ISBN10,
        ISBN13
    };
    constexpr ISBN(unsigned int group, unsigned int registrant, unsigned int publication, unsigned int checksum)
    : ISBN(Type::ISBN10, 0, group, registrant, publication, checksum)
    {
    }
    
    constexpr ISBN(unsigned int prefix, unsigned int group, unsigned int registrant, unsigned int publication, unsigned int checksum)
    : ISBN(Type::ISBN13, prefix, group, registrant, publication, checksum)
    {
    }
    
    void print() const
    {
        switch (type)
        {
        case Type::ISBN10:
            std::cout << "ISBN10: " << group << "-" << registrant << "-" << publication << "-" << checksum << std::endl;
            break;
        case Type::ISBN13:
            std::cout << "ISBN13: " << prefix << "-" << group << "-" << registrant << "-" << publication << "-" << checksum << std::endl;
            break;
        };
    };
    

protected:
    unsigned int prefix;
    unsigned int group;
    unsigned int registrant;
    unsigned int publication;
    unsigned int checksum;
    Type type;


protected:
    constexpr ISBN(Type type, unsigned int prefix, unsigned int group, unsigned int registrant, unsigned int publication, unsigned int checksum)
    : prefix(prefix), group(group), registrant(registrant), publication(publication), checksum(checksum), type(type)
    {
    }
};
