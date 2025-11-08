#pragma once

#include <initializer_list>
#include <iosfwd>
#include <vector>

#include "atom.hpp"

// Дизъюнкт
class Clause {
public:
    Clause(std::initializer_list<Atom> atoms = {});
    Clause(const std::vector<Atom>& atoms);

    [[nodiscard]] const std::vector<Atom>& atoms() const;
    [[nodiscard]] std::vector<Atom>& atoms();

    void Distinct();
    void RemoveOpposites();
    void Sort();

    [[nodiscard]] friend bool operator==(const Clause&, const Clause&) = default;

    friend std::ostream& operator<<(std::ostream&, const Clause&);

private:
    std::vector<Atom> atoms_;
};
