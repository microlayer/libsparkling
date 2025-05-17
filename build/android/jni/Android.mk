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
			$(call LS_CPP,$(LOCAL_PATH),../../../source/renderer/texture) \
			$(call LS_CPP,$(LOCAL_PATH),../../../source/renderer/vertexbuffer) \
			$(call LS_CPP,$(LOCAL_PATH),../../../source/perspective) \
			$(call LS_CPP,$(LOCAL_PATH),../../../source/ui) \
			$(call LS_CPP,$(LOCAL_PATH),../../../source/drawing) \
			$(call LS_CPP,$(LOCAL_PATH),../../../source/file) \
			$(call LS_CPP,$(LOCAL_PATH),../../../source/mesh) \
			$(call LS_CPP,$(LOCAL_PATH),../../../source/mesh/generator) \
			$(call LS_CPP,$(LOCAL_PATH),../../../source/scene) \
			$(call LS_CPP,$(LOCAL_PATH),../../../source/animator) \
			$(call LS_CPP,$(LOCAL_PATH),../../../source/timer) \
			$(call LS_CPP,$(LOCAL_PATH),../../../source/mlstl) \
			$(call LS_CPP,$(LOCAL_PATH),../../../source/forms) \
			$(call LS_CPP,$(LOCAL_PATH),../../../source/game) \
			$(call LS_CPP,$(LOCAL_PATH),../../../source/fonts)
			
SPARKLING_C_INCLUDES := $(LOCAL_PATH)/../../../include
SPARKLING_C_INCLUDES += $(LOCAL_PATH)/../../../source
SPARKLING_C_INCLUDES += $(LOCAL_PATH)/../../../lib

#----------------------------------------------------------------------------------------------------
# Include liblodepng.a
#----------------------------------------------------------------------------------------------------
include $(CLEAR_VARS)
LOCAL_MODULE := liblodepng
LOCAL_SRC_FILES := ../../../lib/lodepng/build/android/obj/local/$(TARGET_ARCH_ABI)/liblodepng.a
include $(PREBUILT_STATIC_LIBRARY)

#----------------------------------------------------------------------------------------------------
# Include libtinyxml2.a
#----------------------------------------------------------------------------------------------------
include $(CLEAR_VARS)
LOCAL_MODULE := libtinyxml2
LOCAL_SRC_FILES := ../../../lib/tinyxml2/build/android/obj/local/$(TARGET_ARCH_ABI)/libtinyxml2.a
include $(PREBUILT_STATIC_LIBRARY)

#----------------------------------------------------------------------------------------------------
# Include libbox2d.a
#----------------------------------------------------------------------------------------------------
include $(CLEAR_VARS)
LOCAL_MODULE := libbox2d
LOCAL_SRC_FILES := ../../../lib/Box2D/build/android/obj/local/$(TARGET_ARCH_ABI)/libbox2d.a
include $(PREBUILT_STATIC_LIBRARY)


#----------------------------------------------------------------------------------------------------
# Build shared library
#----------------------------------------------------------------------------------------------------
include $(CLEAR_VARS)
LOCAL_MODULE		:= libsparkling
LOCAL_C_INCLUDES    	:= $(SPARKLING_C_INCLUDES)
LOCAL_SRC_FILES  	:= $(LIBSPARKLING_SRC_FILES)
LOCAL_LDLIBS		:= -landroid -llog -lEGL -lGLESv3 
LOCAL_CFLAGS		:= -DSPARK_USE_ROOT_HOME_DIR

LOCAL_STATIC_LIBRARIES := android_native_app_glue liblodepng libtinyxml2 libbox2d

include $(BUILD_SHARED_LIBRARY)

$(call import-module,android/native_app_glue)







