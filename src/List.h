#pragma once 

#include "Object.h"

/**
 * Wraps a jobject to expose interface for the java.util.List interface.
 */
class List : public Object {
    public:
        /**
         * Constructs a list.
         */
        List(jobject instance, JNIEnv *env);
        ~List();
        /**
         * Gets the object at the specified index.
         */
        jobject Get(int index);
        /**
         * Returns the length of the list.
         */
        int GetSize();
    private:
        jclass listClass;    
};