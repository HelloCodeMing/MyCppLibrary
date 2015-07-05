#ifndef MING_CONTAINER_SET_HPP
#define MING_CONTAINER_SET_HPP

#include <set>

#include "Iterable.hpp"
#include "range.hpp"

namespace ming {
namespace container {

template <class T>
class Set: public std::set<T>, public Iterable<Set<T>> {
    public:
    using std::set<T>::set;
    using base = std::set<T>;
    using iterable = Iterable<Set<T>>;

    /**
     * Used for obtain another container with type U.
     */
    template <class U>
    struct container {
        using type = Set<U>;
    };

    /**
     * Add element.
     */
    
    void add(const T& elem) {
        base::insert(elem);
    }
};
} /* end of namespace ming::container */

using container::Set;
} /* end of namespace ming */
#endif