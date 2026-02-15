#ifndef __SPARK_NETWORK_ISPARKHTTPCLIENT_HPP_INCLUDED__
#define __SPARK_NETWORK_ISPARKHTTPCLIENT_HPP_INCLUDED__

#include "SparkRefCount.hpp"
#include <functional>
#include <string>
#include <vector>

namespace spark::network {
    /**
    *
    */
    class ISparkHttpClient : public virtual spark::SparkRefCount
    {
    public:
        virtual void get(const std::string& url, std::function<void(std::vector<uc8_t>)> callback) = 0;
    };
}
#endif