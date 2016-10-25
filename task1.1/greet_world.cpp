#include <iostream>

/**
 prints hello world on std out, if additional parameters added,
 instead of greeting world only parameter names are listed, separated by coma or and.

 @returns 0
 */
int main(int argc, char *argv[]) {
    std::cout << "Hello ";

    if (argc == 1) {
        std::cout << "World";
    }
    else if (argc == 2) {
        std::cout << argv[1];
    }
    else if (argc == 3) {
        std::cout << argv[1] << " and " << argv[2];
    }
    else if (argc > 3) {
        for (int i = 1; i < argc; i++) {
            if (i != 1) {
                if (argc - 1 == i) {
                    std::cout << ", and ";
                }
                else {
                    std::cout << ", ";
                }
            }
            std::cout << argv[i];
        }
    }

    std::cout << std::endl;

    return 0;
}
