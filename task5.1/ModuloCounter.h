
class ModuloCounter {

public:
    explicit ModuloCounter(int newMin, int newMax, int newValue = 0) : min {newMin}, max {newMax} {
        this->setValue(newValue);
    };
    void increment(int i = 1);
    void decrement(int i = 1);
    // TODO: how to define getter/setter?
    const int getValue();
//    const int getMin();
//    const int getMax();
    void setValue(int i);
    void setValue(ModuloCounter m);

private:
    int value;
    int min;
    int max;
    friend std::ostream &operator<<(std::ostream &os, const ModuloCounter &game);
};

std::ostream &operator<<(std::ostream &os, const ModuloCounter &counter)
{
    os << counter.value << " in [" << counter.min << ", " << counter.max << ")" << std::endl;
    return os;
}

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