#ifndef __SPARK_MLSTL_HASH_MLHASH_HPP_INCLUDED__
#define __SPARK_MLSTL_HASH_MLHASH_HPP_INCLUDED__

#include <vector>
#include <string>
#include <spark/SparkTypes.hpp>

namespace spark {
    namespace mlstl {
        namespace hash {
            /**
            * Calculates hash for the provided byte stream using Fowler-Noll-Vo algorithmus
            */
            class MLHash
            {
            public:
                static std::string hashFNV1a(std::vector<spark::uc8_t>& data)
                {
                    const int64_t FNV_OFFSET_BASIS = 14695981039346656037U;
                    const int64_t FNV_64_PRIME = 1099511628211U;

                    int64_t hash = FNV_OFFSET_BASIS;

                    for (auto byte : data)
                    {
                        hash ^= byte;            // XOR the byte with the current hash
                        hash *= FNV_64_PRIME;    // Multiply by the FNV prime
                    }
                    std::ostringstream oss;
                    oss << hash;
                    return oss.str();
                }
            };
        }
    }
}
#endif
