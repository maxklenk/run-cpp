
#include <vector>
#include <initializer_list>
#include <map>
#include <array>
#include <unordered_map>
#include <unordered_set>
#include <list>
#include <set>

#include "collect.h"


int main(int argc, char * argv[])
{
    const auto intVector  = std::vector<int>{ 0, 1, 2, 3, 4 };
    const auto intInitList  = { 0, 1, 2, 3, 4 };
    const auto intBoolMap = std::map<int, bool>{ {1, false }, { 4, true }, { 2, true }, { 3, false } };
    const auto doubleSet = std::set<double>{ 0.0, 3.2, 4.1, 5.7 };
    
    // You can reduce the number of template arguments if your solution is able to deduce them
//    std::vector<float> vfc_1              = collect<std::vector>            (intInitList, [](int v) { return static_cast<float>(v); });
//
//    std::vector<float> vfc_2              = collect<std::vector>            (intInitList, [](int v) { return static_cast<float>(v); });
//
//    auto vfc_3              = collect            (intInitList, [](int v) { return static_cast<float>(v); });


    std::vector<float> vfc              = collect<std::vector<float>>            (intInitList, [](int v) { return static_cast<float>(v); });
    std::vector<float> vfe              = collect<float>                         (intVector,   [](int v) { return static_cast<float>(v); });
    std::list<float> lfc                = collect<std::list<float>>              (intVector,   [](int v) { return static_cast<float>(v); });
    std::set<int> sic                   = collect<std::set<int>>                 (doubleSet,   [](double v) { return static_cast<int>(v); });
    std::unordered_set<int> usic        = collect<std::unordered_set<int>>       (doubleSet,   [](double v) { return static_cast<int>(v); });
    std::vector<int> vic                = collect<std::vector<int>>              (doubleSet,   [](double v) { return static_cast<int>(v); });
    std::vector<bool> vbc               = collect<std::vector<bool>>             (intBoolMap,  [](const std::pair<int, bool> & p) { return p.second; });
    std::map<int, float> mif            = collect<std::map<int, float>>          (intVector,   [](int i) { return std::pair<int, float>(i, static_cast<float>(i)); });
    std::unordered_map<int, float> umif = collect<std::unordered_map<int, float>>(intVector,   [](int i) { return std::pair<int, float>(i, static_cast<float>(i)); });
}
