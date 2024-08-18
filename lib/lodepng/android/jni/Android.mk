LOCAL_PATH := $(call my-dir)

LS_CPP=$(subst $(1)/,,$(wildcard $(1)/$(2)/*.cpp))
LS_C=$(subst $(1)/,,$(wildcard $(1)/$(2)/*.c))

LODEPNG_SRC_FILES:= $(call LS_CPP,$(LOCAL_PATH),../) \
			
#----------------------------------------------------------------------------------------------------
# Build shared library
#----------------------------------------------------------------------------------------------------
include $(CLEAR_VARS)
LOCAL_MODULE		:= lodepng
LOCAL_SRC_FILES  	:= $(LODEPNG_SRC_FILES)
include $(BUILD_SHARED_LIBRARY)
$(call import-module,android/native_app_glue)


#----------------------------------------------------------------------------------------------------
# Build static library
#----------------------------------------------------------------------------------------------------
#include $(CLEAR_VARS)
#LOCAL_MODULE		:= lodepng
#LOCAL_SRC_FILES  	:= $(LODEPNG_SRC_FILES)
#include $(BUILD_STATIC_LIBRARY)
#$(call import-module,android/native_app_glue)




