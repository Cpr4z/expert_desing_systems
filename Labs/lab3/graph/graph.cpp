#include "graph.hpp"

#include <cstddef>
#include <filesystem>
#include <fstream>
#include <istream>
#include <ostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <utility>

#include "types/common.hpp"
#include "types/graph.hpp"
#include "utils/io_utils.hpp"

HyperGraph::HyperGraph(Vertices vertices, Rules rules)
        : vertices_{std::move(vertices)}, rules_{std::move(rules)} {
    USet<size_t> ids;

    for (const auto& [from, tos, id, label] : rules_) {
        checkVertex_(from);
        for (auto&& to : tos) {
            checkVertex_(to);
        }
        if (ids.contains(id)) {
            throw std::invalid_argument(
                    "[HyperGraph::HyperGraph] Production rule with id \"" +
                    std::to_string(id) + "\" already exists");
        }
        ids.insert(id);
    }
}

void HyperGraph::checkVertex_(const Vertex& v) const {
    if (!vertices_.contains(v)) {
        throw std::invalid_argument("[HyperGraph::checkVertex_] \"" +
                                    std::to_string(v.id) + "\" is not in V");
    }
}

std::istream& operator>>(std::istream& is, HyperGraph& graph) {
    size_t n = 0;
    is >> n;

    Vertices vertices;

    for (size_t i = 0; i < n; ++i) {
        Vertex v;
        is >> v.id;
        vertices.insert(v);
    }

    is >> n;

    Rules rules;
    for (size_t i = 0; i < n; ++i) {
        std::size_t id = 0;
        is >> id;

        std::string symbol;
        is >> symbol;  // ","

        Vertex from;
        is >> from.id;

        is >> symbol;  // "->"

        std::string line;
        std::getline(is, line);
        std::stringstream ss{line};

        Vertex to;
        Vertices tos;
        while (ss >> to.id) {
            tos.insert(to);
        }

        rules.push_back(Rule{from, std::move(tos), id});
    }

    graph = HyperGraph(std::move(vertices), std::move(rules));

    return is;
}

std::ostream& operator<<(std::ostream& os, const HyperGraph& graph) {
    os << graph.vertices_.size() << '\n';
    join(graph.vertices_, os);
    os << '\n';

    os << graph.rules_.size() << '\n';
    for (auto&& [from, to, id, label] : graph.rules_) {
        os << id << ", " << from.id << " -> ";
        join(to, os);
        os << '\n';
    }
    return os;
}

HyperGraph HyperGraph::readFromFile(const std::filesystem::path& path) {
    HyperGraph graph;
    std::ifstream stream{path};
    if (!stream) {
        throw std::invalid_argument("[HyperGraph::readFromFile] " + path.string() +
                                    ": no such file");
    }
    stream >> graph;
    return graph;
}

void HyperGraph::writeToFile(const std::filesystem::path& path) const {
    std::ofstream stream{path};
    if (!stream) {
        throw std::invalid_argument("[HyperGraph::writeToFile] " + path.string() +
                                    ": can't open file");
    }
    stream << *this;
}
