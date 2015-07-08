#ifndef MING_IO_PRINT_HPP
#define MING_IO_PRINT_HPP

#include <string>
#include <cstring>
#include <iostream>

#include "has_iterator.hpp"

namespace ming {
namespace IO {

/**
 * @name: print
 * @desc: Print arbitrary object to stdout, including integral, C-string, object(with overloaded operator <<), C++ container.
 * @para: The object to print.
 * @exam: ming::print(1024); 
 *        ming::print("hello");
 *        ming::print(std::string("hello"));
 *        ming::print(Dog("Scooby Doo"));
 *        ming::print(std::vector<int>{ 1, 0, 2, 4 });
 */

/**
 * @name: println
 * @desc: Print arbitrary object to stdout, with a line break. 
 */

void print() {
}

/**
 * Print a std::string.
 */
void print(const std::string& str) {
    std::cout << str;
}

/**
 * Print std::pair.
 */
template <class K, class V>
void print(const std::pair<K, V>& p) {
    std::cout << p.first << ":" << p.second;
}

/**
 * Print a object.
 */
template <class T>
void print(const T& x, std::enable_if_t<!ming::has_iterator<T>::value>* = nullptr) {
    std::cout << x;
}

/**
 * Print a container with iterator.
 */
template <class T>
void print(const T& x, std::enable_if_t<ming::has_iterator<T>::value>* = nullptr) {
    for (auto& i : x)
        print(i), print(" ");
}

template <class T>
void println(const T& item) {
    print(item);
    std::cout << std::endl;
}

void println() {
    std::cout << std::endl;
}

} /* end of namespace ming::IO */

using IO::print;
using IO::println;
} /* end of namespace ming */
#endif
