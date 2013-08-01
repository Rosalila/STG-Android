LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := main

SDL_PATH := ../SDL
SDL_IMAGE_PATH := ../SDL2_image

LOCAL_C_INCLUDES := $(LOCAL_PATH)/$(SDL_PATH)/include
LOCAL_C_INCLUDES := $(LOCAL_PATH)/$(SDL_IMAGE_PATH)
LOCAL_C_INCLUDES := $(LOCAL_PATH)/Rosalila

# Add your application source files here...
LOCAL_SRC_FILES := $(SDL_PATH)/src/main/android/SDL_android_main.c \
	main.cpp
LOCAL_SRC_FILES += $(LOCAL_PATH)/STGUtility/STGUtility.cpp
LOCAL_SRC_FILES += $(LOCAL_PATH)/STGMenu/STGMenu.cpp
LOCAL_SRC_FILES += $(LOCAL_PATH)/Stage/Dialogue.cpp
LOCAL_SRC_FILES += $(LOCAL_PATH)/Stage/Layer.cpp
LOCAL_SRC_FILES += $(LOCAL_PATH)/Stage/Stage.cpp
LOCAL_SRC_FILES += $(LOCAL_PATH)/Character/Character.cpp
LOCAL_SRC_FILES += $(LOCAL_PATH)/Character/Enemy.cpp
LOCAL_SRC_FILES += $(LOCAL_PATH)/Character/Modifier.cpp
LOCAL_SRC_FILES += $(LOCAL_PATH)/Character/Player.cpp
LOCAL_SRC_FILES += $(LOCAL_PATH)/STG.cpp
LOCAL_SRC_FILES += $(LOCAL_PATH)/Spells/Bullet.cpp
LOCAL_SRC_FILES += $(LOCAL_PATH)/Spells/Hitbox.cpp
LOCAL_SRC_FILES += $(LOCAL_PATH)/Spells/Pattern.cpp
LOCAL_SRC_FILES += $(LOCAL_PATH)/Rosalila/RosalilaInputs/Receiver.cpp
LOCAL_SRC_FILES += $(LOCAL_PATH)/Rosalila/RosalilaInputs/RosalilaInputs.cpp
LOCAL_SRC_FILES += $(LOCAL_PATH)/Rosalila/RosalilaGraphics/RosalilaGraphics.cpp
LOCAL_SRC_FILES += $(LOCAL_PATH)/Rosalila/RosalilaGraphics/Image.cpp
LOCAL_SRC_FILES += $(LOCAL_PATH)/Rosalila/RosalilaGraphics/Explosion.cpp
LOCAL_SRC_FILES += $(LOCAL_PATH)/Rosalila/RosalilaGraphics/Explosion2.cpp
LOCAL_SRC_FILES += $(LOCAL_PATH)/Rosalila/RosalilaGraphics/Cube.cpp
LOCAL_SRC_FILES += $(LOCAL_PATH)/Rosalila/RosalilaGraphics/Object3D.cpp
LOCAL_SRC_FILES += $(LOCAL_PATH)/Rosalila/RosalilaGraphics/Timer.cpp
LOCAL_SRC_FILES += $(LOCAL_PATH)/Rosalila/RosalilaGraphics/Animation.cpp
LOCAL_SRC_FILES += $(LOCAL_PATH)/Rosalila/RosalilaSound/RosalilaSound.cpp
LOCAL_SRC_FILES += $(LOCAL_PATH)/Rosalila/TinyXml/tinystr.cpp
LOCAL_SRC_FILES += $(LOCAL_PATH)/Rosalila/TinyXml/tinyxml.cpp
LOCAL_SRC_FILES += $(LOCAL_PATH)/Rosalila/TinyXml/tinyxmlerror.cpp
LOCAL_SRC_FILES += $(LOCAL_PATH)/Rosalila/TinyXml/tinyxmlparser.cpp
LOCAL_SRC_FILES += $(LOCAL_PATH)/Rosalila/RosalilaUtility/RosalilaUtility.cpp
LOCAL_SRC_FILES += $(LOCAL_PATH)/Rosalila/RosalilaMenus/Elemento.cpp
LOCAL_SRC_FILES += $(LOCAL_PATH)/Rosalila/RosalilaMenus/MenuBarra.cpp
LOCAL_SRC_FILES += $(LOCAL_PATH)/Rosalila/RosalilaMenus/MenuBoton.cpp
LOCAL_SRC_FILES += $(LOCAL_PATH)/Rosalila/RosalilaMenus/MenuCharSelect.cpp
LOCAL_SRC_FILES += $(LOCAL_PATH)/Rosalila/RosalilaMenus/MenuContenedor.cpp
LOCAL_SRC_FILES += $(LOCAL_PATH)/Rosalila/RosalilaMenus/MenuGallery.cpp
LOCAL_SRC_FILES += $(LOCAL_PATH)/Rosalila/RosalilaMenus/MenuImagen.cpp
LOCAL_SRC_FILES += $(LOCAL_PATH)/Rosalila/RosalilaMenus/MenuLista.cpp
LOCAL_SRC_FILES += $(LOCAL_PATH)/Rosalila/RosalilaMenus/MenuTexto.cpp
LOCAL_SRC_FILES += $(LOCAL_PATH)/Rosalila/RosalilaNetwork/RosalilaNetwork.cpp
LOCAL_SRC_FILES += $(LOCAL_PATH)/Rosalila/RosalilaInputs/Boton.cpp
LOCAL_SRC_FILES += $(LOCAL_PATH)/Rosalila/RosalilaAI/Automata.cpp
LOCAL_SRC_FILES += $(LOCAL_PATH)/Rosalila/RosalilaAI/Estado.cpp
LOCAL_SRC_FILES += $(LOCAL_PATH)/Rosalila/RosalilaAI/RosalilaAI.cpp
LOCAL_SRC_FILES += $(LOCAL_PATH)/Rosalila/RosalilaAI/Transicion.cpp


#LOCAL_SRC_FILES := $(wildcard $(LOCAL_PATH)/*/*.cpp)

LOCAL_SHARED_LIBRARIES := SDL2 SDL2_image

LOCAL_STATIC_LIBRARIES := android_native_app_glue 

LOCAL_CXXFLAGS := -DFREEGLUT_GLES2

LOCAL_LDLIBS := -landroid -llog -lEGL -lGLESv1_CM -lOpenSLES -lGLESv2
#-lGLESv1_CM
#-lGLESv2

#-lglut
#-lGL
#-lGLU

include $(BUILD_SHARED_LIBRARY)
$(call import-module,android/native_app_glue)
