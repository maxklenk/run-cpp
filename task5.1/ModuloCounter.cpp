#include <iostream>

#import "ModuloCounter.h"

void ModuloCounter::increment(int i) {
    this->setValue(this->value + i);
}

void ModuloCounter::decrement(int i) {
    this->setValue(this->value - i);
}

const int ModuloCounter::getValue() {
    return this->value;
}

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
    this->setValue(m.getValue());
}

const int ModuloCounter::getMin() {
    return this->min;
}

void ModuloCounter::setMin(int i) {
    this->min = i;
}

const int ModuloCounter::getMax() {
    return this->max;
}

void ModuloCounter::setMax(int i) {
    this->max = i;
}

std::ostream &operator<<(std::ostream &os, const ModuloCounter &counter) {
    os << counter.value << " in [" << counter.min << ", " << counter.max << ")" << std::endl;
    return os;
}