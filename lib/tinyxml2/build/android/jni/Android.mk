LOCAL_PATH := $(call my-dir)

LS_CPP=$(subst $(1)/,,$(wildcard $(1)/$(2)/*.cpp))
LS_C=$(subst $(1)/,,$(wildcard $(1)/$(2)/*.c))

TINYXML2_SRC_FILES:= $(call LS_CPP,$(LOCAL_PATH),../../../) \
			
#----------------------------------------------------------------------------------------------------
# Build static library
#----------------------------------------------------------------------------------------------------
include $(CLEAR_VARS)
LOCAL_MODULE		:= tinyxml2
LOCAL_SRC_FILES  	:= $(TINYXML2_SRC_FILES)
include $(BUILD_STATIC_LIBRARY)




