#ifndef __SPARK_MLSTL_GUID_MLGUID_HPP_INCLUDED__
#define __SPARK_MLSTL_GUID_MLGUID_HPP_INCLUDED__

#include <string>
#include <iostream>
#include <ctime>

namespace spark::mlstl::guid {
    /**
    * Calculates guid based on randowm numbers
    */
    class MLGuid
    {
    private:
        inline static bool seeded = false;

    public:
        static std::string createGuid()
        {
            if (!seeded)
            {
                std::srand(static_cast<unsigned int>(std::time(0)));
                seeded = true;
            }
            std::string guid;

            auto getHexDigit = [](uint32_t val) -> char {
                return val < 10 ? '0' + val : 'a' + (val - 10);
                };

            // GUID: 9f3c7a0e - 9d4c - 4e12 - 8a3b - 4f9c27a122de
            const int groupSizes[] = { 8, 4, 4, 4, 12 };
            for (int g = 0; g < 5; ++g)
            {
                for (int i = 0; i < groupSizes[g]; ++i)
                {
                    uint32_t val = std::rand() % 16;
                    if (g == 2 && i == 0) val = 4;                      // version 4
                    if (g == 3 && i == 0) val = 8 + std::rand() % 4;    // 
                    guid += getHexDigit(val);
                }
                guid += "-";
            }
            size_t len = std::strlen(guid.c_str());
            guid[len - 1] = '\0';
            return guid;
        }
    };
}
#endif