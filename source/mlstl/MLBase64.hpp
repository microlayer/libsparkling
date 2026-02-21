#ifndef __SPARK_MLSTL_BASE64_MLBASE64_HPP_INCLUDED__
#define __SPARK_MLSTL_BASE64_MLBASE64_HPP_INCLUDED__

#include <vector>
#include "spark/SparkTypes.hpp"
#include <string>
#include <unordered_map>

namespace spark::mlstl::base64 {
    /**
    * -------------------------------
    * |  1.byte |  2.byte |  3.byte |
    * |         |         |         |
    * |010000|01|0000|0000|00|000000|
    * |      |       |       |      |
    * | 1    | 2     |3      |4     |
    * -------------------------------
    *
    * 252=0xFC=11111100
    * 240=0xF0=11110000
    * 192=0xC0=11000000
    * 063=0x3F=00111111
    * 015=0x0F=00001111
    * 003=0x03=00000011
    */
    class MLBase64
    {
    public:
        static std::string encode(uc8_t* bytesToEncodeToBase64, int length);
        static std::vector<uc8_t> decode(std::string base64EncodedString);
        static inline std::string getBase64Chars();

    private:
        const static uc8_t CHAR_PAD = '=';
    };
}
#endif