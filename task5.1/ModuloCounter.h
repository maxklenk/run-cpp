#pragma once

#include <iostream>

class ModuloCounter {

public:
    explicit ModuloCounter(int newMin, int newMax, int newValue = 0) : min{newMin}, max{newMax} {
        this->setValue(newValue);
    };

    void increment(int i = 1);

    void decrement(int i = 1);

    const int getValue();

    void setValue(int i);

    const int getMin();

    void setMin(int i);

    const int getMax();

    void setMax(int i);

    void setValue(ModuloCounter m);

    friend std::ostream &operator<<(std::ostream &os, const ModuloCounter &game);

private:
    int value;
    int min;
    int max;
};
