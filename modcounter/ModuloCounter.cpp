#include <iostream>

#import "ModuloCounter.h"

void ModuloCounter::setValue(int i) {
    while (i >= this->max) {
        i = i - (this->max - this->min);
    }
    while (i < this->min) {
        i = i + (this->max - this->min);
    }
    this->value = i;
}

void ModuloCounter::setValue(ModuloCounter m) {
    this->setValue(m.value);
}

ModuloCounter ModuloCounter::operator++() {
    this->setValue(this->value + 1);
    return *this;
}

ModuloCounter ModuloCounter::operator++(int) {
    ModuloCounter tmp(*this);
    operator++();
    return tmp;
}

ModuloCounter ModuloCounter::operator+=(int i) {
    this->setValue(this->value + i);
    return *this;
}

ModuloCounter operator+(ModuloCounter lhs, const int &rhs) {
    lhs += rhs;
    return lhs;
}

ModuloCounter ModuloCounter::operator--() {
    this->setValue(this->value - 1);
    return *this;
}

ModuloCounter ModuloCounter::operator--(int) {
    ModuloCounter tmp(*this);
    operator--();
    return tmp;
}

ModuloCounter ModuloCounter::operator-=(int i) {
    this->setValue(this->value - i);
    return *this;
}

ModuloCounter operator-(ModuloCounter lhs, const int &rhs) {
    lhs -= rhs;
    return lhs;
}

ModuloCounter ModuloCounter::operator=(int i) {
    this->setValue(i);
    return *this;
}

ModuloCounter ModuloCounter::operator+=(const ModuloCounter &rhs) {
    this->setValue(this->value + rhs.value);
    return *this;
}

ModuloCounter operator+(ModuloCounter lhs, const ModuloCounter &rhs) {
    lhs += rhs;
    return lhs;
}

ModuloCounter ModuloCounter::operator-=(const ModuloCounter &rhs) {
    this->setValue(this->value - rhs.value);
    return *this;
}

ModuloCounter operator-(ModuloCounter lhs, const ModuloCounter &rhs) {
    lhs -= rhs;
    return lhs;
}

ModuloCounter ModuloCounter::operator*=(const ModuloCounter &rhs) {
    this->setValue(this->value * rhs.value);
    return *this;
}

ModuloCounter operator*(ModuloCounter lhs, const ModuloCounter &rhs) {
    lhs *= rhs;
    return lhs;
}

ModuloCounter ModuloCounter::operator/=(const ModuloCounter &rhs) {
    this->setValue(this->value / rhs.value);
    return *this;
}

ModuloCounter operator/(ModuloCounter lhs, const ModuloCounter &rhs) {
    lhs /= rhs;
    return lhs;
}

std::ostream &operator<<(std::ostream &os, const ModuloCounter &counter) {
    os << counter.value << " in [" << counter.min << ", " << counter.max << ")" << std::endl;
    return os;
}