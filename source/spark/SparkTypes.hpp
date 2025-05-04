#ifndef __SPARK_SPARKTYPES_HPP_INCLUDED__
#define __SPARK_SPARKTYPES_HPP_INCLUDED__

#include "spark/SparkCompilerConfig.hpp"

namespace spark {
    /**
    * @Brief Microsoft Compiler Version: symbol _MSC_VER defined
    */
#if (SPARK_COMPILER == SPARK_COMPILER_VC2010 || \
	SPARK_COMPILER == SPARK_COMPILER_VC2012 ||	\
	SPARK_COMPILER == SPARK_COMPILER_VC2013 ||	\
	SPARK_COMPILER == SPARK_COMPILER_VC2015 ||	\
	SPARK_COMPILER == SPARK_COMPILER_VC2017 ||  \
	SPARK_COMPILER == SPARK_COMPILER_VC2019 ||	\
	SPARK_COMPILER == SPARK_COMPILER_VC2022)			
    // Integer types
    typedef signed		char			c8_t;			// 8 bit char variable (signed is the default )
    typedef unsigned    char			uc8_t;
    typedef signed      short			int16_t;
    typedef unsigned    short			uint16_t;
    typedef signed		__int32			int32_t;		// 32 bit signed variable
    typedef unsigned	__int32			uint32_t;		// 32 bit unsigned variable
    typedef signed		__int64			int64_t;		// 64 bit signed variable
    typedef unsigned	__int64			uint64_t;		// 64 bit unsigned variable
    // Real types
    typedef             float			real32;
    typedef             double			real64;

    /**
    * @Brief GNUC Compiler Version: symbol __GNUC__ defined
    */
#elif (SPARK_COMPILER == SPARK_COMPILER_GCC)
    // Integer types
    typedef signed		char		c8_t;				// 8 bit char variable (signed is the default )
    typedef unsigned    char        uc8_t;
    typedef signed      short       int16_t;
    typedef unsigned    short       uint16_t;
    typedef signed      int         int32_t;
    typedef unsigned    int         uint32_t;
    typedef signed      long long   int64_t;
    typedef unsigned    long long   uint64_t;
    // Real types
    typedef             float       real32;
    typedef             double      real64;
#else
    typedef signed		char		c8_t;				// 8 bit char variable (signed is the default )
#endif
}
#endif
