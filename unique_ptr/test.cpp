#include <iostream>
#include "unique_ptr.hpp"

int main() {
    
    int *a = new int{2222};
    unique_ptr <int> ptr(a);
    std::cout << "a = " << (a == nullptr) << std::endl;
    std::cout << "ptr = " << *ptr << std::endl;

    return 0;
    
}