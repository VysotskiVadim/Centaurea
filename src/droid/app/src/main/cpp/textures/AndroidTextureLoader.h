#pragma once

#include <jni.h>
#include "ITextureLoader.h"

using namespace Cenraurea::Common::GameEngine;

class AndroidTextureLoader : public ITextureLoader {
private:
    JNIEnv* _javaEnvironment;
    jobject _jniWrapperObject;
public:
    AndroidTextureLoader(JNIEnv *javaEnvironment, jobject jniWrapperObject);
    void loadTexture(std::string id) override;
};

