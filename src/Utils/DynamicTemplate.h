#pragma once

#include <type_traits>

// Use SFINAE to detect if method exists
#define HAS_METHOD(method_name) \
    template<typename T, typename... Args> \
    struct has_##method_name { \
    public: \
        template<typename U> \
        static auto check(int) -> decltype(std::declval<U>().method_name(std::declval<Args>()...), std::true_type()); \
        template<typename> \
        static std::false_type check(...); \
    public: \
        static constexpr bool value = std::is_same_v<decltype(check<T>(0)), std::true_type>; \
    };

#define DECLARE_METHOD(method_name) \
    template<typename U, typename... Args> \
    auto method_##method_name(U* obj, Args&&... args) \
    { \
        if constexpr (has_##method_name<T, Args...>::value) { \
            /*DEBUG("Find ", #method_name);*/ \
            return obj->##method_name(std::forward<Args>(args)...); \
        } else { \
            ERROR(#method_name, " does not exist."); \
            return false; \
        } \
    }

#define DEFINE_METHOD(method_name) \
    HAS_METHOD(method_name) \
    DECLARE_METHOD(method_name)

#define CALL_METHOD(obj, method_name, ...) \
    method_##method_name(obj, __VA_ARGS__)
