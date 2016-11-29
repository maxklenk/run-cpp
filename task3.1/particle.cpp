
#include <stack>
#include <iostream>
#include "particle.h"
#include <cstdint>


namespace
{
    // allocate SIZE for all Particles
    static const size_t SIZE = 1572864;

    static const void *particles = malloc(SIZE); // TODO use #define

    static std::stack<Particle *> free_addresses;
    static bool initialized = false;
}


void *Particle::operator new(std::size_t size) noexcept
{

    if (!initialized)
    {
        initialized = true;

        Particle *currentAddress = (Particle *) &particles;
        free_addresses = std::stack<Particle *>();

        static const int amount_particles = floor(SIZE / sizeof(Particle));
        std::cout << "amount particles: " << amount_particles << std::endl;
        for (int i = 0; i < amount_particles; i++)
        {
            free_addresses.push(currentAddress);
            currentAddress = currentAddress + 1;
        }
    }

    if (free_addresses.size() == 0)
    {
        //std::cout << "full...";
        return nullptr;
    }

    Particle *particle = reinterpret_cast<Particle *>(free_addresses.top());
    particle = ::new Particle();
    free_addresses.pop(); // pop on success only
    return particle;
}

void Particle::operator delete(void *ptr)
{
    Particle *p = (Particle *) ptr;
    ::operator delete(ptr);
    free_addresses.push(p);
}
