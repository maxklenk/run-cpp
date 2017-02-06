
#include <string>
#include <typeinfo>
#include <stdexcept>

class Variant {

    void* value;

    const char * m_typename;

public:

    Variant() = default;

    template <typename T>
    Variant(T value) {
        this->m_typename = typeid(T).name();
        this->value = &value;
    }

    template<typename T>
    bool hasType() {
        auto result2 = typeid(T).name();
        auto result = this->m_typename == typeid(T).name();
        return result;
    }

    template<typename T>
    T get() {
        if (hasType<T>()) {
             return *new (this->value) T;
//            return reinterpret_cast<T>(this->value);
        } else {
            throw std::logic_error("Incorrect type used.");
        }
    }

//    std::string toString() {
//        return this->get<std::string>();
//    }

//    void fromString(std::string s) {
//        this->value = value;
//    }

    template<typename T>
    static Variant fromString(std::string s) {
        T value = T(s);
        return Variant(value);
    }

    const char * getTypeId() {
        return typeid(this->value).name();
    }

    friend bool operator==(Variant & v1, Variant & v2) {
        return v1.getTypeId() == v2.getTypeId();
    }

//    friend bool operator==(Variant & v1, std::string & s) {
//        return v1.getTypeId() == v2.getTypeId();
//    }


};