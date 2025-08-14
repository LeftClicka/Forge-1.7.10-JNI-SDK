#include "Object.h"

void Object::MakeGlobal() {
    jobjectRefType refType = env->GetObjectRefType(instance);
    if (refType == JNILocalRefType) {
        jobject globalRef = env->NewGlobalRef(instance);
        DeleteLocal();
        this->instance = globalRef;
    }
}

void Object::Delete() {
    jobjectRefType refType = env->GetObjectRefType(instance);
    if (refType == JNILocalRefType) {
        DeleteLocal();
    } else if (refType == JNIGlobalRefType) {
        DeleteGlobal();
    }
}