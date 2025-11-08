#include "types/atom.hpp"

#include <ostream>

#include "utils/io_join.hpp"

std::ostream& operator<<(std::ostream& os, const Atom& atom) {
    os << atom.name << '(';
    join(atom.terminals, os);
    return os << ')';
}