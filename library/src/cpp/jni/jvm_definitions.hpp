#pragma once
#include <jni.h>
#include "jvm_signature.hpp"
#include <vector>
#include <iterator>

struct AssetFileDescriptor {
    static constexpr auto cls = "android/content/res/AssetFileDescriptor"_fstr;
    jobject m_object;

    AssetFileDescriptor(const jobject object): m_object(object) {}
    operator jobject() const { return m_object; }
};

struct Pcm {
    static constexpr auto cls = "barsoosayque/libgdxoboe/AudioDecoder$Pcm"_fstr;
    jobject m_object;

    Pcm(const jobject object): m_object(object) {}
    operator jobject() const { return m_object; }
};

struct ByteBuffer {
    static constexpr auto cls = "java/nio/ByteBuffer"_fstr;
    jobject m_object;

    ByteBuffer(const jobject object): m_object(object) {}
    operator jobject() const { return m_object; }
};
