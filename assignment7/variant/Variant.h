
//#include <string>
//#include <typeinfo>
//#include <stdexcept>

//class Variant {
//
//    void* value;
//
//    const char * m_typename;
//
//public:
//
//    Variant() = default;
//
//    template <typename T>
//    Variant(T value) {
//        this->m_typename = typeid(T).name();
//        this->value = &value;
//    }
//
//    template<typename T>
//    bool hasType() {
//        auto result2 = typeid(T).name();
//        auto result = this->m_typename == typeid(T).name();
//        return result;
//    }
//
//    template<typename T>
//    T get() {
//        if (hasType<T>()) {
//             return *new (this->value) T;
////            return reinterpret_cast<T>(this->value);
//        } else {
//            throw std::logic_error("Incorrect type used.");
//        }
//    }
//
////    std::string toString() {
////        return this->get<std::string>();
////    }
//
////    void fromString(std::string s) {
////        this->value = value;
////    }
//
//    template<typename T>
//    static Variant fromString(std::string s) {
//        T value = T(s);
//        return Variant(value);
//    }
//
//    const char * getTypeId() {
//        return typeid(this->value).name();
//    }
//
//    friend bool operator==(Variant & v1, Variant & v2) {
//        return v1.getTypeId() == v2.getTypeId();
//    }
//
////    friend bool operator==(Variant & v1, std::string & s) {
////        return v1.getTypeId() == v2.getTypeId();
////    }
//
//
//};



#pragma once

#include <exception>
#include <memory>
#include <typeinfo>
#include <type_traits>

class Variant;

template<class Type> Type any_cast(Variant&);
template<class Type> Type any_cast(const Variant&);
template<class Type> Type* any_cast(Variant*);
template<class Type> const Type* any_cast(const Variant*);

struct bad_any_cast : public std::bad_cast {};

class Variant {
public:

    template<class Type> friend
    Type any_cast(Variant&);

    template<class Type>
    friend Type any_cast(const Variant&);

    template<class Type>
    friend Type* any_cast(Variant*);

    template<class Type>
    friend const Type* any_cast(const Variant*);

    Variant()
            : ptr(nullptr)
    {}

    Variant(Variant&& x)
            : ptr(std::move(x.ptr))
    {}

    Variant(const Variant& x) {
        if (x.ptr)
            ptr = x.ptr->clone();
    }

    template<class Type> Variant(const Type& x)
            : ptr(new concrete<typename std::decay<const Type>::type>(x))
    {}

    template<typename T>
    bool hasType() {
        return typeid(T) == this->type();
    }

    template<typename T>
    T get() {
        if (hasType<T>()) {
            return any_cast<T>(*this);
        } else {
            throw std::logic_error("Incorrect type used.");
        }
    }

    Variant& operator=(Variant&& rhs) {
        ptr = std::move(rhs.ptr);
        return (*this);
    }

    Variant& operator=(const Variant& rhs) {
        ptr = std::move(Variant(rhs).ptr);
        return (*this);
    }

    template<class T> Variant& operator=(T&& x) {
        ptr.reset(new concrete<typename std::decay<T>::type>(typename std::decay<T>::type(x)));
        return (*this);
    }

    template<class T> Variant& operator=(const T& x) {
        ptr.reset(new concrete<typename std::decay<T>::type>(typename std::decay<T>::type(x)));
        return (*this);
    }

    void clear() {
        ptr.reset(nullptr);
    }

    bool empty() const {
        return ptr == nullptr;
    }

    const std::type_info& type() const {
        return (!empty())
               ? ptr->type()
               : typeid(void);
    }

private:

    struct placeholder {

        virtual std::unique_ptr<placeholder> clone() const = 0;
        virtual const std::type_info& type() const = 0;
        virtual ~placeholder() {}

    };

    template<class T>
    struct concrete : public placeholder {

        concrete(T&& x)
                : value(std::move(x))
        {}

        concrete(const T& x)
                : value(x)
        {}

        virtual std::unique_ptr<placeholder> clone() const override {
            return std::unique_ptr<placeholder>(new concrete<T>(value));
        }

        virtual const std::type_info& type() const override {
            return typeid(T);
        }

        T value;

    };

    std::unique_ptr<placeholder> ptr;

};

template<class Type>
Type any_cast(Variant& val) {
    if (val.ptr->type() != typeid(Type))
        throw bad_any_cast();
    return static_cast<Variant::concrete<Type>*>(val.ptr.get())->value;
}

template<class Type>
Type any_cast(const Variant& val) {
    return any_cast<Type>(Variant(val));
}

template<class Type>
Type* any_cast(Variant* ptr) {
    return dynamic_cast<Type*>(ptr->ptr.get());
}

template<class Type>
const Type* any_cast(const Variant* ptr) {
    return dynamic_cast<const Type*>(ptr->ptr.get());
}