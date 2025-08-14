#pragma once

#include "Java.h"

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