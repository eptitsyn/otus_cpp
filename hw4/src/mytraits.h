#pragma once
#include <type_traits>
#include <functional>
#include <utility>

template<typename T, typename _ = void>
struct is_container : std::false_type {};

template<typename... Ts>
struct is_container_helper {};

template<typename T>
struct is_container<
        T,
        std::conditional_t<
            false,
            is_container_helper<
                typename T::value_type,
                typename T::size_type,
                typename T::allocator_type,
                typename T::iterator,
                typename T::const_iterator,
                decltype(std::declval<T>().size()),
                decltype(std::declval<T>().begin()),
                decltype(std::declval<T>().end()),
                decltype(std::declval<T>().cbegin()),
                decltype(std::declval<T>().cend())
                >,
            void
            >
        > : public std::true_type {};

    //! Tests if T is a specialization of Template
    template <typename T, template <typename...> class Template>
    struct is_specialization_of : std::false_type {};
    template <template <typename...> class Template, typename... Args>
    struct is_specialization_of<Template<Args...>, Template> : std::true_type {};

    //T is specialization of Template with same Args...
    template <typename T, template <typename...> class Template>
    struct is_specialization_ofsame : std::false_type {};
    template <template <typename...> class Template, typename A, typename... Args>
    struct is_specialization_ofsame<Template<A, Args...>, Template> : 
        std::conditional_t<std::conjunction_v<std::is_same<A, Args>...>, std::true_type, std::false_type> {};