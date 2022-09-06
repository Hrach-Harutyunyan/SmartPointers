#include <iostream>
#include "shared_ptr.hpp"

int main() {
    int* a = new int(10);
    Shared_ptr<int> s{a};

    int *b = new int(20);
    Shared_ptr<int> p{b};


    std::cout << "Before reset: " << std::endl;
    std::cout << "s: " << s << std::endl;
    std::cout << "p: " << p << std::endl;

    s.reset();

    std::cout << "After reset: " << std::endl;
    std::cout << "s: " << s << std::endl;
    std::cout << "p: " << p << std::endl;
    
    s.swap(p);

    std::cout << "After swap: " << std::endl;
    std::cout << "s: " << s << std::endl;
    std::cout << "p: " << p << std::endl;


    return 0;
}