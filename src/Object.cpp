#include "Java.h"

void Java::Object::MakeGlobal() {
    jobjectRefType refType = env->GetObjectRefType(instance);
    if (refType == JNILocalRefType) {
        jobject globalRef = env->NewGlobalRef(instance);
        DeleteLocal();
        this->instance = globalRef;
    }
}

void Java::Object::Delete() {
    jobjectRefType refType = env->GetObjectRefType(instance);
    if (refType == JNILocalRefType) {
        DeleteLocal();
    } else if (refType == JNIGlobalRefType) {
        DeleteGlobal();
    }
}