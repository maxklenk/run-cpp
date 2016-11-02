#include <iostream>

/**
 prints hello world on std out, if additional parameters added,
 instead of greeting world only parameter names are listed, separated by coma or and.

 @returns 0
 */
int main(int argc, char *argv[]) {
    std::cout << "Hello ";

    if (argc == 1) {
        std::cout << "World" << std::endl;
        return 0;
    }

    if (argc == 2) {
        std::cout << argv[1] << std::endl;
        return 0;
    }

    if (argc == 3) {
        std::cout << argv[1] << " and " << argv[2] << std::endl;
        return 0;
    }

    std::cout << argv[1];
    for (auto i = 2; i < argc; i++) {
        if (i == argc - 1) {
            std::cout << ", and ";
        } else {
            std::cout << ", ";
        }
        std::cout << argv[i];
    }
    std::cout << std::endl;
    return 0;
}
