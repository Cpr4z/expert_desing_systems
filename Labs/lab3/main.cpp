#include <iostream>

#include "graph/depth_first_search.hpp"
#include "graph/graph.hpp"
#include "types/graph.hpp"
#include "utils/io_utils.hpp"

int main() {
    const auto graph = HyperGraph::readFromFile("../tests/graph2.txt");
    std::cout << "========== Граф И/ИЛИ ==========\n" << graph;

    std::cout << "Введите стартовую вершину:" << std::endl;

    std::string vert_number;
    std::cin >> vert_number;
    const Vertex from(std::atoi(vert_number.c_str()));

    std::cout << "Введите целевые вершины:" << std::endl;

    Vertices to;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    while (std::getline(std::cin, vert_number))
    {
        if (vert_number.empty()) {
            break;
        }
        to.emplace(std::atoi(vert_number.c_str()));
    }

//    const Vertex from = 17;
//    const Vertices to{1, 2, 6, 7, 9, 14, 21, 22};

    std::cout << "========== Цель ================\n" << from << '\n';
    std::cout << "========== Данные ==============\n"
              << (join(to, std::cout), '\n');

    std::cout << "========== Трассировка =========\n";
    DepthFirstSearch dfs(graph, from, to);
    const auto res = dfs.search();

    std::cout << "========== Результат ===========\n"
              << "Путь ";
    if (res.found) {
        std::cout << "НАЙДЕН\n";
        std::cout << "Закрытые вершины: "
                  << (join(res.closed_vertices, std::cout), '\n');
        std::cout << "Закрытые правила: "
                  << (join(res.closed_rules, std::cout), '\n');
    } else {
        std::cout << "НЕ НАЙДЕН\n";
        std::cout << "Закрытые вершины: "
                  << (join(res.closed_vertices, std::cout), '\n');
        std::cout << "Закрытые правила: "
                  << (join(res.closed_rules, std::cout), '\n');
    }
}
