#include "Java.h"

#include <unordered_map>

namespace Java {
    
    static JNIEnv *env;
    static JavaVM *jvm;

    static jobject cl_object;
    static jmethodID find_class_method;

    //Initialization of JNI
    //Required for anything else to work; called once in the main method
    bool Attach() {
        int result = JNI_GetCreatedJavaVMs(&jvm, 1, nullptr);
        if (result != 0)
            return false;
		jvm->AttachCurrentThread((void**)&env, nullptr);
        if (!env)
            return false;
        jclass cl_class = env->FindClass("net/minecraft/launchwrapper/LaunchClassLoader");
        if (!cl_class)
            return false;
        jclass launch_class = env->FindClass("net/minecraft/launchwrapper/Launch");
        if (!launch_class)
            return false;
        jfieldID cl_field = env->GetStaticFieldID(launch_class, "classLoader", "Lnet/minecraft/launchwrapper/LaunchClassLoader;");
        if (!cl_field)
            return false;
        jobject temp = env->GetStaticObjectField(launch_class, cl_field);
        if (!temp)
            return false;
        cl_object = env->NewGlobalRef(temp);
        DELETE_LOCAL(temp);
        find_class_method = env->GetMethodID(cl_class, "loadClass", "(Ljava/lang/String;)Ljava/lang/Class;");
        if (!find_class_method)
            return false;
        env->DeleteLocalRef(cl_class);
        env->DeleteLocalRef(launch_class);
        return true;
    }

    void Detach() {
        env->DeleteGlobalRef(cl_object);
        jvm->DetachCurrentThread();
    }

    JNIEnv *GetEnv() {
        return env;
    }

    JavaVM *GetJVM() {
        return jvm;
    }

    jclass GetClass(const char* name) {
        jstring jname = env->NewStringUTF(name);
		jclass _class = (jclass)env->CallObjectMethod(cl_object, find_class_method, jname);
		env->DeleteLocalRef(jname);
        return _class;
    }

    jclass GetClass(const char *name, JNIEnv *customEnv) {
        jstring jname = customEnv->NewStringUTF(name);
		jclass _class = (jclass)customEnv->CallObjectMethod(cl_object, find_class_method, jname);
        if (!_class) {
            _class = customEnv->FindClass(name);
            if (!_class) {
                //error handling ig
            }
        }
		customEnv->DeleteLocalRef(jname);
		return _class;
    }

    jobject GetStaticObjectField(const char *className, const char *fieldName, const char *fieldSig) {
        jclass clazz = GetClass(className);
        jfieldID field = GetEnv()->GetStaticFieldID(clazz, fieldName, fieldSig);
        jobject value = GetEnv()->GetStaticObjectField(clazz, field);
        DELETE_LOCAL(clazz);
        return value;
    }


    jobject GetEnumGlobal(const char *className, const char *fieldName, const char *sig, JNIEnv *env) {
        jclass clazz = Java::GetClass(className, env);
        jfieldID field = env->GetStaticFieldID(clazz, fieldName, sig);
        jobject local = env->GetStaticObjectField(clazz, field);
        jobject global = env->NewGlobalRef(local);
        env->DeleteLocalRef(clazz);
        env->DeleteLocalRef(local);
        return global;
    }


}