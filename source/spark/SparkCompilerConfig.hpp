#ifndef __SPARK_SPARKCOMPILERCONFIG_HPP_INCLUDED__
#define __SPARK_SPARKCOMPILERCONFIG_HPP_INCLUDED__

#include "spark/SparkSetup.hpp"

/**
*  @brief Calling convention.
*/
#if (SPARK_PLATFORM == SPARK_PLATFORM_WINDOWS )
#	define SPARKCALLCONV __cdecl
#	define SPARKLING_API
#else
#	define SPARKCALLCONV
#	define SPARKLING_API
#endif

/**
*  @brief NULL pointer definition
*/
#ifndef NULL
#ifdef __cplusplus
#	define NULL 0
#else
#	define NULL ((void *)0)
#endif
#endif 
#endif

/**
*  @brief pragma warning disable
*/
#ifdef _MSC_VER
#pragma warning(disable : 4250) // 'class1' : inherits 'class2::member' via dominance
#endif