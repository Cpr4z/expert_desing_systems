// std
#include <iostream>

#include "graph/breadth_first_search.hpp"
#include "graph/depth_first_search.hpp"
#include "graph/graph.hpp"
#include "graph/search_result.hpp"
#include "utils/io_utils.hpp"
#include "utils/visu_utils.hpp"

namespace fs = std::filesystem;

namespace {
    using namespace std::string_view_literals;
    constexpr std::string_view tests_rel_path = "../tests"sv;
    constexpr std::string_view tests_ext = ".txt"sv;
}

/**
 * Поиск в глубину и в ширину в пространстве состояний.
 */
int main() {
    const auto runTest = [](const fs::path& test_file){
        std::cout << "Start test " + test_file.filename().string() << std::endl;
        const auto graph = Graph::readFromFile(test_file);
        for (auto v : graph.vertices()) {
            for (auto u : graph.vertices()) {
                if (v == u) {
                    continue;
                }

                auto dfs = depthFirstSearch(graph, v, u);
                auto bfs = breadthFirstSearch(graph, v, u);
                if (!dfs.path.empty() || !bfs.path.empty()) {
                    std::cout << "Найден путь от вершины " << v << " до " << u << ":\n";
                    std::cout << "\tПоиском в глубину: ";
                    Utils::join(dfs.path, std::cout, " -> ");
                    std::cout << "\n";
                    std::cout << "\tПоиском в ширину:  ";
                    Utils::join(bfs.path, std::cout, " -> ");
                    std::cout << '\n';
                }
                else {
                    std::cout << "Путь от вершины " << v << " до " << u << " не найден" << ":\n";
                }
            }
        }
        std::cout << "##########################################" << std::endl;
        Utils::visualizeGraph(graph, test_file);
    };

    for (const auto& dir_entry : fs::directory_iterator(fs::path(tests_rel_path))) {
        if (const auto& test_path = dir_entry.path(); test_path.extension() == tests_ext) {
            runTest(test_path);
        }
    }


}
