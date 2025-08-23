#pragma once

#include "../dependency/jni.h"

#include <unordered_map>
#include "Object.h"
#include <thread>

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
     * Redundant, only exists for backwards compatability. Use GetEnumGlobal(const char *, const char *, JNIEnv *) instead.
     * Field signature is now derived from class name.
     */
    jobject GetEnumGlobal(const char *className, const char *fieldName, const char *sig, JNIEnv *env);

    /**
     * Returns a global reference (!!) to an enum instance, specified by enum class name, enum constant name and signature.
     */
    jobject GetEnumGlobal(const char *className, const char *fieldName, JNIEnv *env);

    /**
     * Returns a field ID based on class name, field name and signature.
     */
    jfieldID GetField(const char *className, const char *fieldName, const char *sig, JNIEnv *env);

    /**
     * Returns a method ID based on class name, method name and signature.
     */
    jmethodID GetMethod(const char *className, const char *fieldName, const char *sig, JNIEnv *env);


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

    /**
     * Base class for all jobject wrappers.
    * 
    * Instances of Object subclasses do not take ownership of the jobject that they operate on!
     * They are simply meant as a wrapper around java objects to make working with them more user friendly.
     * If you want to cache/keep such an Object, make sure to pass it a global reference.
     * You have to free the jobject references yourself.
     * 
     * Some subclasses may be implemented in a way that does not require a jobject to be passed into the constructor (e.g. Minecraft).
     * In that case, the instance *does* take ownership of the underlying jobject and handles everything by itself - nothing has to be freed.
     * 
     * The SwapInstance method may be used to swap out the underlying instance. This can be useful when, for example, iterating a list so things cached
     * by an implementing class can be kept while operating on different instances.
     * 
     */
    class Object {
        public:
            inline Object(jobject instance, JNIEnv *env) {
                this->instance = instance;
                this->env = env;
            }
            inline virtual ~Object() {
                Delete();
            }
            Object(const Object&) = delete;
            Object& operator=(const Object&) = delete;
            Object(Object&&) = default;
            Object& operator=(Object&&) = default;
            /**
             * Swaps the underlying instance. Delets the old ref.
             */
            inline void SwapInstance(jobject instance) {
                Delete();
                this->instance = instance;
            }
            /**
             * Returns the underlying instance.
             */
            inline jobject GetInstance() const {
                return instance;
            }
            /**
             * Deletes the underlying ref (local ref).
             */
            inline void DeleteLocal() {
                env->DeleteLocalRef(instance);
            }
            /**
             * Deletes the underlying ref (global ref).
             */
            inline void DeleteGlobal() {
                env->DeleteGlobalRef(instance);
            }
            /**
             * If the underlying ref is local, it will be deleted and replaced with a global one.
             */
            void MakeGlobal();
            /**
             * Free's the underlying ref.
             */
            void Delete();
            /**
             * Returns a new local copy of the underlying reference.
             */
            inline jobject NewLocalRef() {
                return env->NewLocalRef(instance);
            }
            /**
             * Returns a new global copy of the underlying reference.
             */
            inline jobject NewGlobalRef() {
                return env->NewGlobalRef(instance);
            }
        protected:
            jobject instance;
            JNIEnv *env;
    };

}