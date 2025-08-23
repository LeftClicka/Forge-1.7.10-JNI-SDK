#pragma once 

#include "Object.h"

#include <functional>

/**
 * Wraps a jobject to expose interface for the java.util.List interface.
 */
class List : public Java::Object {
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
        /**
         * Adds an object to the end of this list.
         */
        void Add(jobject thing);
        /**
         * Returns a new list containing all members of this list that pass the filter passed in.
         */
        jobject GetFilteredSubList(std::function<bool(jobject)> filter);
        /**
         * Returns the member of this list that produces the minimal output being passed into the metric function.
         * 
         * Returns nullptr if the list is empty.
         */
        jobject FindMin(std::function<double(jobject)> metric);
        /**
         * Returns the member of this list that produces the maximum output being passed into the metric function.
         * 
         * Returns nullptr if the list is empty.
         */
        jobject FindMax(std::function<double(jobject)> metric);
        /**
         * Creates a new, empty array list
         */
        static jobject NewArrayList(JNIEnv *env);
    private:
        jclass listClass;    
};