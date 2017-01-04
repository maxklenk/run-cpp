#pragma once

#include <iostream>

class ModuloCounter {

public:
    explicit ModuloCounter(int newMin, int newMax, int newValue = 0) : min{newMin}, max{newMax} {
        this->setValue(newValue);
    }

    ModuloCounter(const ModuloCounter &other) : min{other.min}, max{other.max} {
        this->setValue(other.value);
    }

    void increment(int i = 1);

    void decrement(int i = 1);

    const int getValue();

    void setValue(int i);

    void setValue(ModuloCounter m);

    const int getMin();

    const int getMax();

    const ModuloCounter operator*(ModuloCounter &other);

    friend std::ostream &operator<<(std::ostream &os, const ModuloCounter &game);

private:
    int value;
    int min;
    int max;
};
