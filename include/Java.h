#pragma once

#include "../dependency/jni.h"

#define DELETE_LOCAL(thing) ::Java::GetEnv()->DeleteLocalRef(thing)
#define DELETE_GLOBAL(thing) ::Java::GetEnv()->DeleteGlobalRef(thing)

namespace Java {

    /**
     * Attaches the calling thread to the JVM. Must be called before GetEnv(), GetJVM() or GetClass() can be called.
     * Other functions will still work fine.
     */
    bool Attach();

    /**
     * Detaches the calling thread from the jvm.
     */
    void Detach();

    /**
     * Returns the env pointer for the thread that attached by calling Java::Attach.
     * If native code is called from java rather than an independent native thread, this pointer will be invalid.
     */
    JNIEnv *GetEnv();

    /**
     * Returns the JVM pointer that was retrieved by calling Java::Attach().
     */
    JavaVM *GetJVM();

    /**
     * Returns a local reference to a class matching the name.
     * Use this rather than calling FindClass on the env directly, as doing that cannot find classes loaded by Forge's class loader.
     * 
     * Uses Java::GetEnv() as it's env pointer.
     */
    jclass GetClass(const char *name);

    /**
     * Returns a local reference to a class matching the name.
     * Use this rather than calling FindClass on the env directly, as doing that cannot find classes loaded by Forge's class loader.
     */
    jclass GetClass(const char *name, JNIEnv *env);

    /**
     * Helper method that returns a local reference to the value of the static object field specified by class, field name and signature.
     * 
     * Always uses Java::GetEnv() as the env pointer. This is probably problematic, should fix.
     */
    jobject GetStaticObjectField(const char *className, const char *fieldName, const char *fieldSig);

    /**
     * Returns a global reference (!!) to an enum instance, specified by enum class name, enum constant name and signature.
     * 
     * TODO: passing signature is redundant as it can be generated from the class name.
     */
    jobject GetEnumGlobal(const char *className, const char *fieldName, const char *sig, JNIEnv *env);


    /**
     * Must be passed a local ref, UB if a global ref is passed!!
     * Will delete that local ref!!
     * Local ref must have been created by the env passed in.
     * Cleans up created global ref when object is destroyed.
     * 
     * Useful for the following idiom:
     * 
     * void SomeFunction(JNIEnv *env) {
     *      static Java::GlobalRef clazz(<...>);
     *      //some code
     * }
     * 
     * => reference is automatically cleaned up when your code is unloaded.
     * 
     */
    class GlobalRef final {
        public:
            inline GlobalRef(JNIEnv *env, jobject localRef) {
                obj = GetEnv()->NewGlobalRef(localRef);
                env->DeleteLocalRef(localRef);
            }
            inline ~GlobalRef() {
                GetEnv()->DeleteGlobalRef(this->obj);
            }
            inline jobject Object() const {
                return this->obj;
            }
            inline jclass Clazz() const {
                return (jclass)(this->obj);
            }
        private:
            jobject obj;
    };

}