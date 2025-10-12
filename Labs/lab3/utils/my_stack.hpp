#pragma once

#include <stack>

template<typename T>
class Stack : public std::stack<T>
{
public:
    void remove_element(const T& value) {
        auto element = std::find(this->c.begin(), this->c.end(), value);
        if (element != this->c.end()) {
            this->c.erase(element);
        }
    }

    auto begin() const {
        return this->c.begin();
    }

    auto end() const {
        return this->c.end();
    }
};
