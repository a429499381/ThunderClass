#pragma once

#include <iostream>


template<class T>
void
_print(T arg) {
    std::cout << arg << " ";
}

template <class... Args>
void
log(Args... args) {
    int arr[] = { (_print(args), 0)... };
    std::cout << std::endl;
    (void)arr;
}
