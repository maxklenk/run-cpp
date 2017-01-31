
//template<typename T, template<typename CT>>
//T collect(std::initializer_list
//        list,
//        func convert
//)
//{
//    Collection result = Collection();
//    for (auto item: list)
//    {
//        result.add(convert(item));
//    }
//    return result;
//}

template<typename T, typename V, typename Func, template<typename, typename> class C = std::vector>
C<T, std::allocator<T>> collect(const C<V,std::allocator<V>> collection, Func &&convert)
{
    auto result = C<T,std::allocator<T>>();
    for (V &value : collection)
    {
        result.push_back(convert(value)); // push_back only for vector
    }
    return result;
};