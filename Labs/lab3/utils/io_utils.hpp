#pragma once

#include <algorithm>
#include <experimental/iterator>
#include <ostream>
#include <vector>

template <typename It>
void join(It begin, It end, std::ostream& os, const char* delimiter = " ") {
    std::copy(begin, end, std::experimental::make_ostream_joiner(os, delimiter));
}

template <typename Container>
void join(const Container& container,
          std::ostream& os,
          const char* delimiter = " ") {
    join(std::begin(container), std::end(container), os, delimiter);
}

template<typename ContainerIt>
std::vector<typename std::iterator_traits<ContainerIt>::value_type> convertToVector(ContainerIt&& begin,
                                                                                    ContainerIt&& end) {
    return std::vector(begin, end);
}

template<typename ContainerIt>
std::set<typename std::iterator_traits<ContainerIt>::value_type> convertToSet(ContainerIt&& begin,
                                                                              ContainerIt&& end) {
    return std::set(begin, end);
}
