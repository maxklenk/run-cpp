
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

struct BaseObject
{
public:
    BaseObject() {}
    BaseObject(float value, bool count) : m_value(value) {}
    ~BaseObject() {}

    operator float() const {
        return m_value;
    }

    float m_value;
};

struct Object : BaseObject
{
public:
    Object(float value, bool count);
    ~Object();

    Object(BaseObject b) : Object(b.m_value, true) {}

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

    BaseObject operator()()
    {
        return BaseObject(rand(), false);
    }
};

struct Coordinate
{
    int y;
    int x;

    Coordinate(int y, int x) {
        this->y = y;
        this->x = x;
    }
};

struct Coordinates
{
    std::vector<Coordinate> items;

    Coordinates() {}

    Coordinates(Coordinate coord) {
        this->items.emplace_back(coord);
    }

    void emplace_back(Coordinate coord) {
        this->items.emplace_back(coord);
    }
};

struct Columns
{
    int elements;
    int size;

    Columns(int size, int elements) {
        this->size = size;
        this->elements = elements;
    }
};

struct Rows
{
    int elements;
    int size;

    Rows(int size, int elements) {
        this->size = size;
        this->elements = elements;
    }

    friend Coordinates operator==(const Rows r, const Columns c) {
        Coordinates result;
        for (int i = 0; i < r.size && i < r.elements && i < c.size && i < c.elements; ++i) {
            Coordinate newCoord { i, i };
            result.emplace_back(newCoord);
        }

        return result;
    }

    friend Coordinates operator==(const Rows r, const int row) {
        Coordinates result;
        if (row <= r.size) {
            for (int i = 0; i < r.elements; ++i) {
                Coordinate newCoord { row, i };
                result.emplace_back(newCoord);
            }
        }

        return result;
    }

    friend Coordinates operator>(const Rows r, const Columns c) {
        Coordinates result;
        for (int i = 0; i < r.size && i < c.elements; ++i) {
            for (int j = 0; j < r.elements && j < c.size; ++j) {
                if (i > j) {
                    Coordinate newCoord{i, j};
                    result.emplace_back(newCoord);
                }
            }
        }

        return result;
    }

    friend Coordinates operator<(const Rows r, const Columns c) {
        Coordinates result;
        for (int i = 0; i < r.size && i < c.elements; ++i) {
            for (int j = 0; j < r.elements && j < c.size; ++j) {
                if (i < j) {
                    Coordinate newCoord{i, j};
                    result.emplace_back(newCoord);
                }
            }
        }

        return result;
    }
};




struct Column {
    int i;
    Column(int i) {
        this->i = i;
    }
};


struct Row {
    int i;
    Row(const int i) {
        this->i = i;
    }

    friend Coordinates operator,(const Row r, const Column c) {
        Coordinate coord{ r.i, c.i};
        return { coord };
    };

    friend Coordinates operator,(const Column c, const Row r) {
        Coordinate coord{ r.i, c.i};
        return { coord };
    };
};

Row operator "" _y(unsigned long long int i) {
    return Row { (int) i };
}
Column operator "" _x(unsigned long long int i) {
    return Column { (int) i };
}


struct Matrix
{
    Columns x;
    Rows y;

    Matrix() : x{4,4}, y{4,4}
    {
        for (size_t i = 0; i < size;)
        {
            m_f[i++] = 0;
        }
    }
    
    Matrix(std::initializer_list<float> initializer): x{4,4}, y{4,4}
    {
        assert(initializer.size() == size);
        
        size_t i = 0;
        for (auto value : initializer)
        {
            m_f[i++] = value;
        }
    }

    Matrix operator[](Coordinates c) {
        this->c = c;
        return *this;
    }

    void print() {
        for (int i = 0; i < this->size; )
        {
            std::cout << "DEBUG " << i << ": " << this->m_f[i] << " " << std::endl;
            i++;
        }
    }

    Matrix operator=(float i) {
        for (auto value : this->c.items)
        {
            this->m_f[(value.y * 4 + value.x)] = i;
        }

        this->print();

        return *this;
    }

    friend bool operator==(const Matrix &m1, const Matrix &m2)
    {
        bool result = true;

        for (int i = 0; i < m1.size; )
        {
            std::cout << "DEBUG " << m1.m_f[i] << " " << m2.m_f[i] << std::endl;
            result &= m1.m_f[i] == m2.m_f[i];
            i++;
        }

        return result;
    }


    
    Coordinates c;
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

    assert(objects.size() == Generator::objectInstanceCount);
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
//    assert(m == m1);

    m[m.y == m.x] = 1.0f;
//    m[(0,0), (1,1), (2,2), (3,3)] = 1.0f;
//    m.print();

    Matrix m2 = { 1, 0, 0, 0,   0, 1, 0, 0,   0, 0, 1, 0,   0, 0, 0, 1 };
//    assert(m == m2);

    m[m.y > m.x] = 3.0f;
//    m[(1,0), (2,0), (2,1), (3,0), (3,1), (3,2)] = 3.0f;

    Matrix m3 = { 1, 0, 0, 0,   3, 1, 0, 0,   3, 3, 1, 0,   3, 3, 3, 1 };
//    assert(m == m3);

    m[m.y < m.x] = 4.0f;
//    m[(0,1), (0,2), (0,3), (1,2), (1,3), (2,3)] = 4.0f;

    Matrix m4 = { 1, 4, 4, 4,   3, 1, 4, 4,   3, 3, 1, 4,   3, 3, 3, 1 };
//    assert(m == m4);

    m[3_y, 2_x] = 12.0f;
//    m[(3, 2)] = 12.0f;

    Matrix m5 = { 1, 4, 4, 4,   3, 1, 4, 4,   3, 3, 1, 4,   3, 3, 12, 1 };
//    assert(m == m5);

    m[3_x, 2_y] = 42.0f;
//    m[(2, 3)] = 42.0f;

    Matrix m6 = { 1, 4, 4, 4,   3, 1, 4, 4,   3, 3, 1, 42,   3, 3, 12, 1 };
//    assert(m == m6);

    m[m.y == 0] = 2.0f;
//    m[{(0,0), (0,1), (0,2), (0,3)}] = 2.0f;

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
