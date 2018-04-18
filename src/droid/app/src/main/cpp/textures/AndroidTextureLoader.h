#pragma once

#include <jni.h>
#import "ITextureLoader.h"

using Cenraurea::Common::Game::ITextureLoader;

class AndroidTextureLoader : public ITextureLoader {
private:
    JNIEnv* _javaEnvironment;
    jobject _jniWrapperObject;
public:
    AndroidTextureLoader(JNIEnv *javaEnvironment, jobject jniWrapperObject);
    void loadTexture(std::string id) override;
};

