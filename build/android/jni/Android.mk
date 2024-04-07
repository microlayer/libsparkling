LOCAL_PATH := $(call my-dir)


LS_CPP=$(subst $(1)/,,$(wildcard $(1)/$(2)/*.cpp))
LS_C=$(subst $(1)/,,$(wildcard $(1)/$(2)/*.c))

LIBSPARKLING_SRC_FILES:= $(call LS_CPP,$(LOCAL_PATH),../../../testbed/bootstrap/android) \
			$(call LS_CPP,$(LOCAL_PATH),../../../testbed) \
			$(call LS_CPP,$(LOCAL_PATH),../../../source/spark) \
			$(call LS_CPP,$(LOCAL_PATH),../../../source/device) \
			$(call LS_CPP,$(LOCAL_PATH),../../../source/device/window) \
			$(call LS_CPP,$(LOCAL_PATH),../../../source/log) \
			$(call LS_CPP,$(LOCAL_PATH),../../../source/renderer) \
			$(call LS_CPP,$(LOCAL_PATH),../../../source/renderer/common) \
			$(call LS_CPP,$(LOCAL_PATH),../../../source/renderer/shader) \
			$(call LS_CPP,$(LOCAL_PATH),../../../source/perspective) \
			$(call LS_CPP,$(LOCAL_PATH),../../../source/ui) \
			$(call LS_CPP,$(LOCAL_PATH),../../../source/app) \
			$(call LS_CPP,$(LOCAL_PATH),../../../source/drawing) \
			$(call LS_CPP,$(LOCAL_PATH),../../../source/file) \
			$(call LS_CPP,$(LOCAL_PATH),../../../source/mesh) \
			$(call LS_CPP,$(LOCAL_PATH),../../../source/scene) \
			$(call LS_CPP,$(LOCAL_PATH),../../../source/mlstl)
			
SPARKLING_C_INCLUDES := $(LOCAL_PATH)/../../../include
SPARKLING_C_INCLUDES += $(LOCAL_PATH)/../../../source
SPARKLING_C_INCLUDES += $(LOCAL_PATH)/../../../lib


#----------------------------------------------------------------------------------------------------
# Build shared library
#----------------------------------------------------------------------------------------------------
include $(CLEAR_VARS)
LOCAL_MODULE		:= libsparkling
LOCAL_C_INCLUDES    	:= $(SPARKLING_C_INCLUDES)
LOCAL_SRC_FILES  	:= $(LIBSPARKLING_SRC_FILES)
LOCAL_LDLIBS		:= -landroid -llog -lEGL -lGLESv1_CM -lGLESv2 
LOCAL_CFLAGS		:= -DSPARK_USE_ROOT_HOME_DIR

LOCAL_STATIC_LIBRARIES := android_native_app_glue

include $(BUILD_SHARED_LIBRARY)

$(call import-module,android/native_app_glue)


#----------------------------------------------------------------------------------------------------
# Build static library
#----------------------------------------------------------------------------------------------------
#include $(CLEAR_VARS)
#LOCAL_MODULE		:= libsparkling
#LOCAL_C_INCLUDES   := $(SPARKLING_C_INCLUDES)
#LOCAL_SRC_FILES  	:= $(SPARKLING_SRC_FILES)

#LOCAL_STATIC_LIBRARIES := android_native_app_glue png

#include $(BUILD_STATIC_LIBRARY)

#$(call import-module,android/native_app_glue)




