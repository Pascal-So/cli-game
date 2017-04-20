#include <vector>

#ifndef UTILS_HPP
#define UTILS_HPP

template<typename T>
std::vector<T> pair_to_vector(std::pair<T, T> p);

template<typename T>
std::vector<T> filter(std::function<bool(T)> pred, const std::vector<T> & vec);

template<typename T>
void inplace_filter(std::function<bool(T)> pred, std::vector<T> & vec);

template<typename A, typename B>
std::vector<B> map(std::function<B(A)> func, const std::vector<A> & vec);

#include "utils.tpp"

#endif
