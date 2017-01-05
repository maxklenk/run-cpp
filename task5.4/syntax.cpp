
#include <iostream>
#include <string>
#include <cassert>
#include <vector>
#include <sstream>

// Start of solution
// You may edit / add anything from here to satisfy the interfaces and behaviors expected by the execution code below


struct Currency
{
    unsigned long long int cents;

    Currency operator-=(const Currency c) {
        this->cents -= c.cents;
        return *this;
    }

    Currency operator+=(const Currency c) {
        this->cents += c.cents;
        return *this;
    }

    Currency operator&&(const Currency c) {
        this->cents += c.cents;
        return *this;
    }

    Currency operator,(const Currency c) {
        this->cents += c.cents;
        return *this;
    }

    friend bool operator==(const Currency& c, const int i) {
        return c.cents == i;
    }
};

Currency operator "" _cent(unsigned long long int i) {
    return Currency { i };
}
Currency operator "" _cents(unsigned long long int i) {
    return Currency { i };
}
Currency operator "" _euro(unsigned long long int i) {
    return Currency { 100 * i };
}

namespace Bills
{
    const auto Five = Currency { 500 };
    const auto Ten = Currency { 1000 };
    const auto Twenty = Currency { 2000 };
    const auto Fifty = Currency { 5000 };
}

struct Account
{
    Currency balance = 0_euro;

    explicit Account(const Currency & balance)
    : balance(balance)
    {
    }

    Currency operator>>(const Currency &c) {
        this->balance -= c;
        return c;
    }

    Currency operator<<(const Currency &c) {
        this->balance += c;
        return c;
    }

    friend Account operator>>(const Currency &c, Account &a) {
        a.balance.cents += c.cents;
        return a;
    }

    friend Account operator<<(const Currency &c, Account &a) {
        a.balance.cents -= c.cents;
        return a;
    }

    friend std::ostream &operator<<(std::ostream &os, const Account &a) {
        os << "Account with balance " << a.balance.cents / 100 << " euro, " << a.balance.cents % 100 << " cents";
        return os;
    }
};

struct Object
{
public:
    Object(float value, bool count);
    ~Object();
    
    operator float() const {
        return m_value;
    }
    
    float m_value;
};

struct Converter
{
    float m_value;
    
    operator float() const { return float(m_value); }
    operator Object() const { return Object{ m_value, true }; }
};

struct Generator
{
    static size_t objectInstanceCount;

    Object operator()()
    {
        return Object(rand(), true);
    }
};


struct Matrix
{
    Matrix()
    {

        for (size_t i = 0; i < sizeof(m_f) / sizeof(m_f[0]); ++i)
        {
            m_f[i++] = 0.0f;
        }
    }
    
    Matrix(std::initializer_list<float> initializer)
    {
        assert(initializer.size() == sizeof(m_f) / sizeof(m_f[0]));
        
        size_t i = 0;
        for (auto value : initializer)
        {
            m_f[i++] = value;
        }
    }

    float& operator[](int i) {
        return this->m_f[i];
    }

    friend bool operator==(const Matrix &m1, const Matrix &m2)
    {

        bool result = sizeof(m1) == sizeof(m2);

        for (size_t i = 0; i < sizeof(m1.m_f) / sizeof(m1.m_f[0]); ++i)
        {
            result &= m1.m_f[i] == m2.m_f[i];
            ++i;
        }

        return result;
    }
    
protected:
    static const int size = 16;
    float m_f[size];
};

// End of solution
// Do not edit the source code below!

// Generator::objectInstanceCount must be incremented on object creation and shall never be manipulated otherwise
Object::Object(float value, bool count) : m_value(value) { if (count) Generator::objectInstanceCount++; }
Object::~Object() {}
size_t Generator::objectInstanceCount = 0;

void generator()
{
    Generator gen;
    std::vector<float> floats;
    std::vector<Object> objects;
    for (auto i = 0; i < 500; ++i)
    {
        if (i % 7 == 0)
        {
            floats.emplace_back(gen());
        }
        else if (i % 5 == 0)
        {
            objects.emplace_back(gen());
        }
        else
        {
            std::cout << gen() << std::endl;
        }
    }

    // TODO
//    std::cout << objects.size() << " " << Generator::objectInstanceCount << std::endl;
//    assert(objects.size() == Generator::objectInstanceCount);
}

void accounting()
{
    Account a { 200_euro and 34_cents };
    Account b { 300_euro and 1_cent };

    b >> (100_euro, 32_cents) >> a;

    assert(a.balance == 30066);
    assert(b.balance == 19969);

    b << Bills::Fifty << a;

    assert(a.balance == 25066);
    assert(b.balance == 24969);

    std::cout << "a = " << a << std::endl;
    std::cout << "b = " << b << std::endl;

    std::stringstream stream_a;
    stream_a << a;
    std::stringstream stream_b;
    stream_b << b;
    assert(stream_a.str() == "Account with balance 250 euro, 66 cents");
    assert(stream_b.str() == "Account with balance 249 euro, 69 cents");
}

void matrix()
{
    // TODO
    Matrix m;

    Matrix m1 = { 0, 0, 0, 0,   0, 0, 0, 0,   0, 0, 0, 0,   0, 0, 0, 0 };
    assert(m == m1);

//    m[m.y == m.x] = 1.0f;
//    m[(0,0), (1,1), (2,2), (3,3)] = 1.0f;

    Matrix m2 = { 1, 0, 0, 0,   0, 1, 0, 0,   0, 0, 1, 0,   0, 0, 0, 1 };
//    assert(m == m2);

//    m[m.y > m.x] = 3.0f;
//    m[(1,0), (2,0), (2,1), (3,0), (3,1), (3,2)] = 3.0f;

    Matrix m3 = { 1, 0, 0, 0,   3, 1, 0, 0,   3, 3, 1, 0,   3, 3, 3, 1 };
//    assert(m == m3);

//    m[m.y < m.x] = 4.0f;
//    m[(0,1), (0,2), (0,3), (1,2), (1,3), (2,3)] = 4.0f;

    Matrix m4 = { 1, 4, 4, 4,   3, 1, 4, 4,   3, 3, 1, 4,   3, 3, 3, 1 };
//    assert(m == m4);

//    m[3_y, 2_x] = 12.0f;
//    m[(3, 2)] = 12.0f;

    Matrix m5 = { 1, 4, 4, 4,   3, 1, 4, 4,   3, 3, 1, 4,   3, 3, 12, 1 };
//    assert(m == m5);

//    m[3_x, 2_y] = 42.0f;
//    m[(3, 2)] = 42.0f;

    Matrix m6 = { 1, 4, 4, 4,   3, 1, 4, 4,   3, 3, 1, 42,   3, 3, 12, 1 };
//    assert(m == m6);

//    m[m.y == 0] = 2.0f;
//    m[(0,0), (0,1), (0,2), (0,3)] = 2.0f;

    Matrix m7 = { 2, 2, 2, 2,   3, 1, 4, 4,   3, 3, 1, 42,   3, 3, 12, 1 };
//    assert(m == m7);
}

int main(int argc, char * argv[])
{
    generator();
    accounting();
    matrix();
    
    return 0;
}
