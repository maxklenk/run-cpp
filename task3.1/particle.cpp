
#include <stack>
#include <iostream>
#include "particle.h"
#include <cstdint>


namespace
{
    // allocate SIZE for all Particles
    static const size_t SIZE = 1572864;

    static const void *particles = malloc(SIZE); // TODO use #define

    static std::stack<void *> free_addresses;

    static bool initialized_particles = false;

    static void init_particles(Particle &particles, size_t size, std::stack<void *> &free_addresses)
    {
        std::cout << "initialize...";
        static const int amount_particles = floor(SIZE / sizeof(Particle));
        Particle *currentAddress = &particles;
        free_addresses = std::stack<void *>();
        for (int i = 0; i < amount_particles; i++)
        {
            free_addresses.push(&currentAddress);
            std::cout << free_addresses.top();

            std::cout << &currentAddress << std::endl;
            currentAddress = (Particle *) (&currentAddress + sizeof(Particle));
            std::cout << &currentAddress << std::endl << std::endl;
        }
        std::cout << "created " << free_addresses.size() << " free addresses" << std::endl
                  << "  from " << &particles << std::endl << "  to   " << &currentAddress << std::endl;
        initialized_particles = true;
    }

}


void *Particle::operator new(std::size_t size) noexcept
{

    if (!initialized_particles)
        init_particles((Particle &) particles, SIZE, free_addresses);

    std::cout << "new...";

    if (free_addresses.size() == 0)
    {
        std::cout << "full...";
        return nullptr;
    }

    Particle *particleLocation = reinterpret_cast<Particle *>(free_addresses.top());
    std::cout << "create " << &particleLocation << std::endl;
    Particle *particle = ::new(particleLocation) Particle();
    std::cout << "create " << &particle << std::endl;

    free_addresses.pop(); // pop on success only
    return particle;
}

void Particle::operator delete(void *ptr)
{
    std::cout << "delete " << &ptr << std::endl;
    ::operator delete(ptr);
    free_addresses.push(&ptr);
    ptr = nullptr;
    return;
}
