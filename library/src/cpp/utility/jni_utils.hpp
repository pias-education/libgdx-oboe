#pragma once

#include "jni.h"

inline std::string jni_utf8_string(JNIEnv *env, jstring str) {
    const char *native = env->GetStringUTFChars(str, nullptr);
    std::string result(native);
    env->ReleaseStringUTFChars(str, native);
    return result;
}

class SynchronizedMethodGuard {
public:
    SynchronizedMethodGuard(JNIEnv *env, jobject obj) : m_env(env), m_obj(obj) {
        m_env->MonitorEnter(m_obj);
    }

    ~SynchronizedMethodGuard() {
        m_env->MonitorExit(m_obj);
    }

private:
    JNIEnv *m_env;
    jobject m_obj;
};