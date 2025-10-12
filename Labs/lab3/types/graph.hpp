#pragma once

#include <cstddef>
#include <iostream>

#include "types/common.hpp"

enum class Label {
    OPEN = 0,
    CLOSE = 1,
    FORBIDDEN = -1,
    VIEWED = 2
};

struct Vertex {
    Vertex() = default;
    explicit Vertex(size_t id_) : id(id_) {}
    std::size_t id = 0;
    Label label = Label::OPEN;

    auto operator<=>(const Vertex& vertex) const
    {
        return vertex.id <=> this->id;
    }

    bool operator==(const Vertex& vertex) const
    {
        return vertex.id == this->id;
    }

    friend std::ostream& operator<<(std::ostream& os, Vertex vertex) {
        os << vertex.id;
        return os;
    }
};

using Vertices = Set<Vertex>;

struct Rule {
    Vertex from;
    Vertices to;
    std::size_t id;
    Label label = Label::OPEN;

    auto operator<=>(const Rule& rule) const
    {
        return rule.id <=> this->id;
    }

    bool operator==(const Rule& rule) const
    {
        return rule.id == this->id;
    }

    friend std::ostream& operator<<(std::ostream& os, const Rule& rule) {
        os << rule.id;
        return os;
    }
};

using Rules = Vector<Rule>;
using RulePtr = Rule*;