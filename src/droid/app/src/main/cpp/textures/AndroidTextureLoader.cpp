#include "AndroidTextureLoader.h"


AndroidTextureLoader::AndroidTextureLoader(JNIEnv *javaEnvironment, jobject jniWrapperObject)
        : _javaEnvironment(javaEnvironment),
          _jniWrapperObject(jniWrapperObject)
{
}

void AndroidTextureLoader::loadTexture(std::string id) {
    const char *cid = id.c_str();
    jstring textureName = _javaEnvironment->NewStringUTF(cid);
    jclass jniWrapper = _javaEnvironment->FindClass("centaureaproj/com/centaurea/GameLibJNIWrapper");
    jmethodID loadMethodId = _javaEnvironment->GetMethodID(jniWrapper, "loadImageToGlTexture", "(Ljava/lang/String;)V");
    _javaEnvironment->CallVoidMethod(_jniWrapperObject, loadMethodId, textureName);
}