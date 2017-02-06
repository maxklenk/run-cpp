
#include <vector>
#include <functional>

template<typename... Args>
class Signal {
public:


    // for functions and lambdas
    template<typename Func>
    void connect(Func&& func) {
        this->functions.push_back(func);
    }

    // for member functions applied to objects
    template <typename T, typename R>
    void connect(T & obj, R T::* mf)
    {
//        auto func = [&obj, mf](Args... args) {
//            auto f = std::bind(mf, obj, args);
//        };
//
//        this->functions.push_back(func);

        // TODO: store member function
//        this->functions.push_back((obj).*mf);
//        auto func = std::bind(mf, obj);
//        this->functions.push_back(func);
//        return (obj.*mf)(std::forward<Args>(args)...);
    }

    void emit(Args&&... args) {
        for (auto it = functions.begin(); it != functions.end(); ++it)
        {
            (*it)(args...);
        }
    }

protected:
    std::vector<void (*)(Args...)> functions;
};