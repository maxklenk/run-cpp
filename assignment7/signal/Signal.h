
#include <vector>
#include <functional>

template<typename... Args>
class Signal {
public:

    // for functions and lambdas
    template<typename Func>
    void connect(Func &&func) {
        this->functions.push_back(func);
    }

    // for member functions applied to objects
    template<typename T, typename R>
    void connect(T &obj, R T::* mf) {
        auto func = [=](Args... args) {
            auto f = std::bind(mf, obj, args...);
            f();
        };

        this->functions.push_back(func);
    }

    void emit(Args &&... args) {
        for (auto it = functions.begin(); it != functions.end(); ++it) {
            (*it)(args...);
        }
    }

protected:
    std::vector<std::function<void(Args...)>> functions;
};