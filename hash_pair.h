//
// Created by Randy on 9/23/2019.
//

#ifndef CPR_EXAMPLE_HASH_PAIR_H
#define CPR_EXAMPLE_HASH_PAIR_H

#include <iostream>
#include <unordered_map>
#include <utility>

template <class T>
inline void hash_combine(std::size_t& seed, const T& v) {
    std::hash<T> hasher;
    seed ^= hasher(v) + 0x9e3779b9 + (seed<<6) + (seed>>2);
}

struct hash_pair {
    template <class T1, class T2>
    std::size_t operator() (const std::pair<T1, T2> &pair) const
    {
        std::size_t seed = 0;
        ::hash_combine(seed, pair.first);
        ::hash_combine(seed, pair.second);
        return seed;
    }
};


#endif //CPR_EXAMPLE_HASH_PAIR_H
