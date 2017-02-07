
#include <cassert>
#include <string>
#include <iostream>

#include "Variant.h"


using namespace std::string_literals;


void basicTest()
{
    auto v0 = Variant();
    assert(!v0.hasType<int>());
    assert(!v0.hasType<float>());
    assert(!v0.hasType<std::string>());

    auto v1 = Variant(4);
    auto b1 = v1.hasType<int>();
    auto i1 = v1.get<int>();
    assert(b1);
    assert(i1 == 4);

    auto v2 = Variant(3.14f);
    auto b2 = v2.hasType<float>();
    auto f2 = v2.get<float>();
    assert(b2);
    assert(f2 == 3.14f);

    auto v3 = Variant(std::string { "barfoo" });
    auto b3 = v3.hasType<std::string>();
    auto s3 = v3.get<std::string>();
    assert(b3);
    assert(s3 == "barfoo");

    assert(!v1.hasType<float>());
    assert(!v1.hasType<std::string>());
    assert(!v2.hasType<int>());
    assert(!v2.hasType<std::string>());
    assert(!v3.hasType<int>());
    assert(!v3.hasType<float>());

    std::cout << "Basic test: success" << std::endl;
}


void comparisonTest()
{
//    auto v1 = Variant(1);
//    auto v2 = Variant(1);
//    auto v3 = Variant(2);
//    auto v4 = Variant(1.0f);
//    auto v5 = Variant(std::string{ "1" });
//
//    assert(v1 == v2);
//    assert(!(v1 == v3));
//    assert(!(v1 == v4));
//    assert(!(v1 == v5));
//
//    std::cout << "Comparison test: success" << std::endl;
}


void conversionTest()
{
//    auto v1 = Variant(1);
//    auto f1 = v1.get<unsigned long>();
//    assert(f1 == 1ul);
//
//    auto c1 = v1.get<char>();
//    assert(c1 == 1);
//
//    auto s1 = v1.get<std::string>();
//    assert(s1 == "1");
//
//    auto v2 = Variant(3.14);
//    auto f2 = v2.get<float>();
//    assert(f2 == 3.14f);
//
//    std::cout << "Conversion test: success" << std::endl;
}


void stringTest()
{
//    auto v1 = Variant(4);
//    assert(v1.toString() == "4");
//
//    auto v2 = Variant(3.14f);
//    assert(v2.toString() == "3.14");
//
//    auto v3 = Variant("foobar"s);
//    assert(v3.toString() == "foobar");
//
//    v1.fromString("1");
//    assert(v1.get<int>() == 1);
//
//    v2.fromString("5");
//    assert(v2.get<float>() == 5.0f);
//
//    v3.fromString("3.14");
//    assert(v3.get<std::string>() == "3.14");
//
//    auto v4 = Variant::fromString<double>("42.123");
//    assert(v4.hasType<double>());
//    assert(v4.get<double>() == 42.123);
//
//    std::cout << "String test: success" << std::endl;
}


void reassignmentTest()
{
//    auto v1 = Variant(4);
//    assert(v1.get<int>() == 4);
//
//    v1 = 42;
//    assert(v1.get<int>() == 42);
//
//    v1 = 3.0;
//    assert(v1.hasType<double>());
//    assert(v1.get<double>() == 3.0);
//
//    v1 = "foobar"s;
//    assert(v1.hasType<std::string>());
//    assert(v1.get<std::string>() == "foobar");
//
//    std::cout << "Reassignment test: success" << std::endl;
}


void typeQueryTest()
{
//    // TODO: implement the pseudo code statments using the closest possible solution
//
//    auto v1 = Variant(123);
//    assert(false /* v1.type() == int */);
//
//    auto v2 = Variant("foobar"s);
//    assert(false /* v2.type() == std::string */);
//
//    /*
//    switch (v1.type())
//    {
//        case int:
//            assert(true);
//            break;
//        case std::string:
//            assert(false);
//            break;
//        case float:
//            assert(false);
//            break;
//    }
//    */
//
//    std::cout << "Type query test: success" << std::endl;
}


void copyMoveTest()
{
//    auto v1 = Variant("foobar"s);
//    auto v2 = Variant(v1);
//
//    assert(v1.hasType<std::string>());
//    assert(v1.get<std::string>() == "foobar");
//    assert(v2.hasType<std::string>());
//    assert(v2.get<std::string>() == "foobar");
//
//    auto v3 = std::move(v1);
//    assert(!v1.hasType<std::string>());
//    assert(v3.hasType<std::string>());
//    assert(v3.get<std::string>() == "foobar");
//
//    v2 = Variant(4);
//    assert(v2.hasType<int>());
//    assert(v2.get<int>() == 4);
//
//    v3 = std::move(v2);
//    assert(!v2.hasType<int>());
//    assert(v3.hasType<int>());
//    assert(v3.get<int>() == 4);
//
//    std::cout << "Copy/move test: success" << std::endl;
}


int main(int argc, char * argv[])
{
    basicTest();

    // Extended task: comment in at least four of the following six tests.
    comparisonTest();
    conversionTest();
    stringTest();
    reassignmentTest();
    typeQueryTest();
    copyMoveTest();
}
