
#include <algorithm>

using namespace std;

// Numeric Vector to Vector
template<typename ResultType, typename CollectionType, typename TransformFunction>
enable_if_t<is_arithmetic<ResultType>::value, vector<ResultType>>
collect(const CollectionType &collection, TransformFunction function)
{
    vector<ResultType> output(collection.size());
    transform(collection.begin(), collection.end(), output.begin(), function);
    return output;
};

// Vectors: has method 'pop_back'
template<typename ResultType, typename CollectionType, typename TransformFunction>
enable_if_t<std::is_member_function_pointer<decltype(&ResultType::pop_back)>::value, ResultType>
collect(const CollectionType &collection, TransformFunction function)
{
    ResultType output(collection.size());
    transform(collection.begin(), collection.end(), output.begin(), function);
    return output;
};


// Maps: has method 'key_comp'
template<typename ResultType, typename CollectionType, typename TransformFunction>
enable_if_t<std::is_member_function_pointer<decltype(&ResultType::key_comp)>::value, ResultType>
collect(const CollectionType &collection, TransformFunction function)
{
    ResultType output;
    for (auto entry : collection)
    {
        output.emplace(function(entry));
    }
    return output;
};

// Unordered_Maps/Unordered_Sets: has method 'hash_function'
template<typename ResultType, typename CollectionType, typename TransformFunction>
enable_if_t<std::is_member_function_pointer<decltype(&ResultType::hash_function)>::value, ResultType>
collect(const CollectionType &collection, TransformFunction function)
{
    ResultType output;
    for (auto entry : collection)
    {
        output.emplace(function(entry));
    }
    return output;
};

// vector.insert() exist
// std::inserter()...

// vector<float> _1
//template<typename Result, typename Source, typename Function>
//auto collect(const Source &source, Function f)
//{
//    Result result;
//    std::transform(source.begin(), source.end(), std::inserter(result, result.end()), f);
//    return result;
//};

// vector ohne <float> _2
// geht auch: template<template<typename...> class Result, typename Source, typename Function>
//template<template<typename, typename> class Result, typename Source, typename Function>
//auto collect(const Source &source, Function f)
//{
//    using ResultValueType=std::result_of_t<Function(typename Source::value_type)>;
//    Result<ResultValueType> result;
//    std::transform(source.begin(), source.end(), std::inserter(result, result.end()), f);
//    return result;
//};

// _3 ohne vector
//template<template<typename, typename> class Container, typename SourceValueType, typename Function>
//auto collect(const Container &source, Function f)
//{
//    using ResultValueType=std::result_of_t<Function(SourceValueType)>;
//    Container<ResultValueType> result;
//    std::transform(source.begin(), source.end(), std::inserter(result, result.end()), f);
//    return result;
//};

