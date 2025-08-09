#include "List.h"

List::List(jobject instance, JNIEnv *env) : Object(instance, env) {
    jclass _class = Java::GetClass("java/util/List", env);
    this->listClass = (jclass) env->NewGlobalRef(_class);
    env->DeleteLocalRef(_class);
}

List::~List() {
    env->DeleteGlobalRef(listClass);
}

jobject List::Get(int index) {
    static jmethodID getMethod = env->GetMethodID(listClass, "get", "(I)Ljava/lang/Object;");
    return env->CallObjectMethod(instance, getMethod, index);
}

int List::GetSize() {
    static jmethodID getSizeMethod = env->GetMethodID(listClass, "size", "()I");
    return env->CallIntMethod(instance, getSizeMethod);
}