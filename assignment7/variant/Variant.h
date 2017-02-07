
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

    template<class Type>
    Variant(const Type& x)
            : ptr(new concrete<typename std::decay<const Type>::type>(x))
    {}

    template<typename T>
    bool hasType() {
        return typeid(T) == this->type();
    }

    template<typename Type>
    Type get() {
        if (hasType<Type>()) {
            return any_cast<Type>(*this);
        } else {
            throw std::logic_error("Incorrect type used.");
        }
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


    // Friends
    template<class Type>
    friend Type any_cast(Variant& val) {
        if (val.ptr->type() != typeid(Type))
            throw bad_any_cast();
        return static_cast<Variant::concrete<Type>*>(val.ptr.get())->value;
    }

    template<class Type>
    friend Type any_cast(const Variant& val) {
        return any_cast<Type>(Variant(val));
    }

    template<class Type>
    friend Type* any_cast(Variant* ptr) {
        return dynamic_cast<Type*>(ptr->ptr.get());
    }

    template<class Type>
    friend const Type* any_cast(const Variant* ptr) {
        return dynamic_cast<const Type*>(ptr->ptr.get());
    }

};

