#pragma once

#include "types/common.hpp"

namespace Utils {
template <typename T>
Vector<T> converted(List<T> list) {
    return {list.begin(), list.end()};
}

template <typename T>
Vector<T> reverseConverted(List<T> list) {
    return {list.rbegin(), list.rend()};
}

template<typename T>
Vector<T> openedConverted(Stack<T> stack) {
    Vector<T> result;
    result.reserve(stack.size());
    while (!stack.empty()) {
        result.emplace_back(std::move(stack.top()));
        stack.pop();
    }
    return {result.rbegin(), result.rend()};
}
}
