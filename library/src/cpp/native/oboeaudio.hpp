#pragma once
#include "jni.h"

#define OBOEAUDIO_METHOD(result, method) \
    JNIEXPORT result JNICALL \
    Java_barsoosayque_libgdxoboe_OboeAudio ## _ ## method

extern "C" {

// fun OboeAudio::init(AssetManager): Unit
OBOEAUDIO_METHOD(void, init) (JNIEnv*, jobject);

// fun OboeAudio::createSoundpool(): NativeSoundpool
OBOEAUDIO_METHOD(jlong, createSoundpool) (JNIEnv*, jobject, jstring);

// fun OboeAudio::createMusic(): NativeMusic
OBOEAUDIO_METHOD(jlong, createMusic) (JNIEnv*, jobject, jstring);

// fun OboeAudio::createAudioEngine(): NativeAudioDevice
OBOEAUDIO_METHOD(jlong, createAudioEngine) (JNIEnv*, jobject, jint, bool);

// fun OboeAudio::dispose(): Unit
OBOEAUDIO_METHOD(void, dispose) (JNIEnv*, jobject);

// fun OboeAudio::resume(): Unit
OBOEAUDIO_METHOD(void, resume) (JNIEnv*, jobject);

// fun OboeAudio::stop(): Unit
OBOEAUDIO_METHOD(void, stop) (JNIEnv*, jobject);

}
