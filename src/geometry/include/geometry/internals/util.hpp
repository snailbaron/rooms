#pragma once

#include <type_traits>

namespace geometry::internals {

template <class, class... T>
struct have_common_type_detector {
    using type = std::false_type;
};

template <class... T>
struct have_common_type_detector<std::void_t<std::common_type_t<T...>>, T...> {
    using type = std::true_type;
};

template <class... T>
using have_common_type =
    typename have_common_type_detector<void, T...>::type;

template <class... T>
inline constexpr bool have_common_type_v = have_common_type<T...>::value;

template <class... T>
using enable_if_have_common_type =
    typename std::enable_if<have_common_type_v<T...>>;

template <class... T>
using enable_if_have_common_type_t =
    typename enable_if_have_common_type<T...>::type;

template <class From, class To>
using enable_if_convertible =
    typename std::enable_if<std::is_convertible_v<From, To>>;

template <class From, class To>
using enable_if_convertible_t = typename enable_if_convertible<From, To>::type;

} // namespace geometry::internals
