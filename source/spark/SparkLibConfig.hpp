#ifndef __SPARK_SPARKLIBCONFIG_HPP_INCLUDED__
#define __SPARK_SPARKLIBCONFIG_HPP_INCLUDED__

/**
* @brief Configure feature level
*/
#define SPARK_USE_OGLFLES2			0x1

/**
* @brief Configure feature to compile
*/
#define SPARK_COMPILE_VULKAN        0x0

/**
* @brief Default shadow map texture size
*/
#define DEFAULT_SHADOW_MAP_WIDTH	1200;
#define DEFAULT_SHADOW_MAP_HEIGHT	1200;

/**
* @brief Pixel to meter ratio used for the box2d physics engine
*/
#define PTM_RATIO					50.0f

/**
* @brief Define logging
*/
#define SPARK_TRACE					0x1
#define SPARK_TRACE_TO_FILE			0x1	// If SPARK_TRACE is switched off, SPARK_TRACE_TO_FILE is also switched off

/**
* @brief Constant values
*/
#define ML_PI						3.14159265f;
#define EPSILON						0.0001f;
#endif
