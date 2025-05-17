LOCAL_PATH := $(call my-dir)

LS_CPP=$(subst $(1)/,,$(wildcard $(1)/$(2)/*.cpp))
LS_C=$(subst $(1)/,,$(wildcard $(1)/$(2)/*.c))

BOX2D_SRC_FILES:= 	$(call LS_CPP,$(LOCAL_PATH),../../../Collision) \
					$(call LS_CPP,$(LOCAL_PATH),../../../Collision/Shapes) \
					$(call LS_CPP,$(LOCAL_PATH),../../../Common) \
					$(call LS_CPP,$(LOCAL_PATH),../../../Dynamics) \
					$(call LS_CPP,$(LOCAL_PATH),../../../Dynamics/Contacts) \
					$(call LS_CPP,$(LOCAL_PATH),../../../Dynamics/Joints) \
					$(call LS_CPP,$(LOCAL_PATH),../../../Rope) 

BOX2D_C_INCLUDES := $(LOCAL_PATH)/../../../../

#----------------------------------------------------------------------------------------------------
# Build static library
#----------------------------------------------------------------------------------------------------
include $(CLEAR_VARS)
LOCAL_MODULE		:= box2d
LOCAL_C_INCLUDES    := $(BOX2D_C_INCLUDES)
LOCAL_SRC_FILES  	:= $(BOX2D_SRC_FILES)
include $(BUILD_STATIC_LIBRARY)




