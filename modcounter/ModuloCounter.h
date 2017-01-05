#pragma once

#include <iostream>

class ModuloCounter {

public:
    explicit ModuloCounter(int newMin, int newMax, int newValue = 0) : min{newMin}, max{newMax} {
        this->setValue(newValue);
    }

    explicit ModuloCounter(int newMin, int newMax, const ModuloCounter &other) : min{newMin}, max{newMax} {
        this->setValue(other.value);
    }

    ModuloCounter(const ModuloCounter &other) : min{other.min}, max{other.max} {
        this->setValue(other.value);
    }

    const operator int() {
        return value;
    }

    void setValue(int i);

    void setValue(ModuloCounter m);

    ModuloCounter operator++();

    ModuloCounter operator++(int);

    ModuloCounter operator+=(int i);

    friend ModuloCounter operator+(ModuloCounter lhs, const int &rhs);

    ModuloCounter operator--();

    ModuloCounter operator--(int);

    ModuloCounter operator-=(int i);

    friend ModuloCounter operator-(ModuloCounter lhs, const int &rhs);

    ModuloCounter operator=(int i);

    ModuloCounter operator+=(const ModuloCounter &rhs);

    friend ModuloCounter operator+(ModuloCounter lhs, const ModuloCounter &rhs);

    ModuloCounter operator-=(const ModuloCounter &rhs);

    friend ModuloCounter operator-(ModuloCounter lhs, const ModuloCounter &rhs);

    ModuloCounter operator*=(const ModuloCounter &rhs);

    friend ModuloCounter operator*(ModuloCounter lhs, const ModuloCounter &rhs);

    ModuloCounter operator/=(const ModuloCounter &rhs);

    friend ModuloCounter operator/(ModuloCounter lhs, const ModuloCounter &rhs);

    friend std::ostream &operator<<(std::ostream &os, const ModuloCounter &game);

private:
    int value;
    int min;
    int max;
};
