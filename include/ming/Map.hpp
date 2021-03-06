#ifndef MING_CONTAINER_MAP_HPP
#define MING_CONTAINER_MAP_HPP

#include <map>
#include <utility>

#include "Iterable.hpp"
#include "is_pair.hpp"
#include "Vector.hpp"
#include "ParallelMap.hpp"

namespace ming {
namespace container {

template <class Pair>
class Map;

template <class K, class V>
class Map<std::pair<K, V>>: public std::map<K, V>, 
      public Iterable<Map<std::pair<K, V>>> {
    public:
    using first_type = K;
    using second_type = V;
    using value_type = std::pair<K, V>;
    using base = std::map<K, V>;
    using iterable = Iterable<Map<value_type>>;
    /* inherit construtor */
    using std::map<K, V>::map;
    
    /**
     * Use for create another container with type T, U.
     */
    template <class T, class U>
    struct container {
        using type = Map<std::pair<T, U>>;
    };

    /**
     * Sepcialization for map method.
     */
    template <class Fn>
    constexpr auto map(Fn f) {
        using result_type = decltype(f(iterable::head()));
        using container_type = std::conditional_t<
                                    ming::is_pair<result_type>::value, 
                                    Map<result_type>, 
                                    Vector<result_type> 
                                >;
        return iterable::fold(container_type(), [f](auto&& init, auto&& elem) {
                init += f(std::forward<decltype(elem)>(elem));
                return init;
        });
    }

    /**
     * Parallelly
     */
    constexpr ParallelMap<value_type> par() {
        return ParallelMap<value_type>(base::begin(), base::end());
    }
};

} /* end of namespace ming::container */

using container::Map;
} /* end of namespace ming */
#endif
