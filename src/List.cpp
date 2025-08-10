#include "List.h"

#include <limits>

List::List(jobject instance, JNIEnv *env) : Object(instance, env) {
    //cannot use GetObjectClass because the runtime class will be some List implementation, not the List interface
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

void List::Add(jobject thing) {
    static jmethodID addMethod = env->GetMethodID(listClass, "add", "(Ljava/lang/Object;)Z");
    env->CallBooleanMethod(instance, addMethod, thing);
}

jobject List::GetFilteredSubList(std::function<bool(jobject)> filter) {
    jobject listObject = NewArrayList(env);

    List list(listObject, env);

    const int size = GetSize();
    for (int i = 0; i < size; ++i) {
        jobject obj = Get(i);
        if (filter(obj)) {
            list.Add(obj);
        }
        env->DeleteLocalRef(obj);
    }

    return listObject;
}

jobject List::FindMin(std::function<double(jobject)> metric) {
    const int size = GetSize();
    double minimum = std::numeric_limits<double>::max();
    jobject minimumObject = nullptr;
    for (int i = 0; i < size; ++i) {
        jobject object = Get(i);
        double value = metric(object);
        if (value < minimum) {
            minimum = value;
            if (minimumObject != nullptr) {
                env->DeleteLocalRef(minimumObject);
            }
            minimumObject = object;
        } else {
            env->DeleteLocalRef(object);
        }
    }
    return minimumObject;
}

jobject List::FindMax(std::function<double(jobject)> metric) {
    const int size = GetSize();
    double maximum = std::numeric_limits<double>::min();
    jobject maximumObject = nullptr;
    for (int i = 0; i < size; ++i) {
        jobject object = Get(i);
        double value = metric(object);
        if (value > maximum) {
            maximum = value;
            if (maximumObject != nullptr) {
                env->DeleteLocalRef(maximumObject);
            }
            maximumObject = object;
        } else {
            env->DeleteLocalRef(object);
        }
    }
    return maximumObject;
}

jobject List::NewArrayList(JNIEnv *env) {

    jclass arrayListClass = Java::GetClass("java/util/ArrayList", env);
    static jmethodID noArgsConstructor = env->GetMethodID(arrayListClass, "<init>", "()V");

    jobject listObject = env->NewObject(arrayListClass, noArgsConstructor);

    env->DeleteLocalRef(arrayListClass);

    return listObject;
}