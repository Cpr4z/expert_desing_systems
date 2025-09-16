#pragma once

// std
#include <list>
#include <queue>
#include <set>
#include <stack>
#include <unordered_map>
#include <utility>
#include <vector>

template <typename T>
using List = std::list<T>;

template <typename T>
using Set = std::set<T>;

template <typename Key, typename T>
using UMap = std::unordered_map<Key, T>;

template <typename T, typename U>
using Pair = std::pair<T, U>;

template <typename T>
using Vector = std::vector<T>;

template <typename T>
using Stack = std::stack<T>;

template<typename T>
using Queue = std::queue<T>;
