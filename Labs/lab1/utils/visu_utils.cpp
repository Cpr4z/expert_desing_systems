#include "visu_utils.hpp"

// std
#include <format>
#include <fstream>
#include <iostream>

namespace fs = std::filesystem;

namespace {
using namespace std::string_view_literals;
constexpr std::string_view dot_ext = ".dot";
constexpr std::string_view png_ext = ".png";
constexpr std::string_view cmd_pattern {R"(dot -Tpng "{}" -o "{}")"sv};

inline std::string esc(const std::string& s) {
    std::string r;
    r.reserve(s.size());
    for (char c : s) {
        if (c == '"' ) r += "\\\"";
        else if (c == '\\') r += "\\\\";
        else r += c;
    }
    return r;
}

inline std::string extractName(const fs::path& path) {
    return path.stem();
}

fs::path replace_only_ext(const fs::path& filepath, const std::string_view ext)
{
    fs::path out = filepath;
    out.replace_extension(ext);
    return out;
}

std::string vertexLabel(std::size_t idx) {
    return "v" + std::to_string(idx);
}

template <class Vertices, class Edges>
std::string to_dot(const Vertices& V, const Edges& E, const std::string& title)
{
    std::string dot;
    dot += "digraph G {\n";
    dot += "  graph [dpi=140, labelloc=t, label=\"" + esc(title) + "\"];\n";
    dot += "  node  [shape=circle, fontname=\"Helvetica\"];\n";
    dot += "  edge  [fontname=\"Helvetica\"];\n";

    for (const auto& v : V) {
        const auto lbl = vertexLabel(v);
        dot += "  v" + std::to_string(v) +
               " [label=\"" + esc(lbl) + "\"];\n";
    }

    for (const auto& e : E) {
        const auto& u = e.first;
        const auto& w = e.second;

        dot += "  v" + std::to_string(u) +
                " -> v" + std::to_string(w) + ";\n";
    }

    dot += "}\n";
    return dot;
}
}

namespace Utils {
void visualizeGraph(const Graph& graph, const std::filesystem::path& filepath) {
    const auto& V = graph.vertices();
    const auto& E = graph.edges();

    const fs::path dot_path = replace_only_ext(filepath, dot_ext);

    {
        std::ofstream dot(dot_path, std::ios::trunc);
        dot << to_dot(V, E, extractName(filepath));
    }

    const fs::path png_path = replace_only_ext(filepath, png_ext);
    const std::string command = std::vformat(cmd_pattern, std::make_format_args(dot_path.string(), png_path.string()));
    const int res = std::system(command.data());
    if (res != 0) {
        throw std::runtime_error("Error while executing converting cmd");
    }
    fs::remove(dot_path);
}
}
