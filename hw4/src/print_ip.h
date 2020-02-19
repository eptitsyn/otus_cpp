/**
 * @file doxygen_c.h
 * @author Evgenii Ptitsyn
 * @brief File containing function for printing IP.
 */

/**
 * Print Ip function library
 */
#pragma once
#include "mytraits.h"
#include "myostream_joiner.h"

#include <iostream>
#include <stdexcept>
#include <vector>
#include <experimental/iterator>
#include <type_traits>
#include <list>
#include <tuple>

/**
 * PrintIp function
 * @param Takes container
 */
template<typename T,
    typename std::enable_if<!is_same<typename std::remove_reference<T>::type, std::string>::value && 
    is_container<typename std::remove_reference<T>::type>::value>::type* = nullptr 
        >
void print_ip(T&& value) {
    copy(begin(value), end(value), make_myostream_joiner(std::cout, "."));
    std::cout << std::endl;
}

/**
 * PrintIp function
 * @param Takes container
 */
template<typename T,
    typename std::enable_if<is_same<typename std::remove_reference<T>::type, std::string>::value>::type* = nullptr 
        >
void print_ip(T&& value) {
    std::cout << value << std::endl;
}

/**
 * PrintIp function
 * @param Takes integral types
 */
template<typename T,
    typename = 
        typename std::enable_if<std::is_integral<typename std::remove_reference<T>::type>::value>::type
        >
void print_ip(T&& value) {
    copy(
        std::make_reverse_iterator(static_cast<const uint8_t*>(static_cast<const void*>(&value)) + sizeof(T)),
        std::make_reverse_iterator(static_cast<const uint8_t*>(static_cast<const void*>(&value))),  
        make_myostream_joiner(std::cout, "."));
    std::cout << std::endl;
}

/**
 * PrintIp function
 * @param Takes tuple, but only of same type.
 */
template<typename T,
    typename std::enable_if<is_specialization_ofsame<typename std::remove_reference<T>::type, std::tuple>::value>::type* = nullptr 
        >
void print_ip(T&& value) {
    std::apply([](auto&& a, auto&&... args) {{std::cout << a;}{((std::cout << '.' << args ), ...);};}, value);
    std::cout << std::endl;

}