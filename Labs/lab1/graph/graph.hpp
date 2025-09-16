#pragma once

#include <filesystem>
#include <iosfwd>

#include "types/graph.hpp"

class Graph {
public:
    explicit Graph(Vertices vertices = {}, Edges edges = {});

    [[nodiscard]] const auto& vertices() const { return m_vertices; }
    [[nodiscard]] const auto& edges() const { return m_edges; }

    friend std::istream& operator>>(std::istream& is, Graph& graph);
    friend std::ostream& operator<<(std::ostream& os, const Graph& graph);

    static Graph readFromFile(const std::filesystem::path& path);
    void writeToFile(const std::filesystem::path& path) const;

private:
    Vertices m_vertices;
    Edges m_edges;

    void checkVertex_(const Vertex& v) const;
};
