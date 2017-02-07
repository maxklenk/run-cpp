
#include <algorithm>

using namespace std;

// Numeric Vector to Vector
template<typename ResultType, typename CollectionType, typename TransformFunction>
enable_if_t<is_arithmetic<ResultType>::value, vector<ResultType>>
collect(const CollectionType &collection, TransformFunction function) {
    vector<ResultType> output(collection.size());
    transform(collection.begin(), collection.end(), output.begin(), function);
    return output;
};

// Vectors: has method 'pop_back'
template<typename ResultType, typename CollectionType, typename TransformFunction>
enable_if_t<std::is_member_function_pointer<decltype(&ResultType::pop_back)>::value, ResultType>
collect(const CollectionType &collection, TransformFunction function) {
    ResultType output(collection.size());
    transform(collection.begin(), collection.end(), output.begin(), function);
    return output;
};


// Maps: has method 'key_comp'
template<typename ResultType, typename CollectionType, typename TransformFunction>
enable_if_t<std::is_member_function_pointer<decltype(&ResultType::key_comp)>::value, ResultType>
collect(const CollectionType &collection, TransformFunction function) {
    ResultType output;
    for (auto entry : collection) {
        output.emplace(function(entry));
    }
    return output;
};

// Unordered_Maps/Unordered_Sets: has method 'hash_function'
template<typename ResultType, typename CollectionType, typename TransformFunction>
enable_if_t<std::is_member_function_pointer<decltype(&ResultType::hash_function)>::value, ResultType>
collect(const CollectionType &collection, TransformFunction function) {
    ResultType output;
    for (auto entry : collection) {
        output.emplace(function(entry));
    }
    return output;
};

