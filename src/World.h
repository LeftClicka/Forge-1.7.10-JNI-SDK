#pragma once

#include "Object.h"

/**
 * Wraps a jobject to expose the World interface.
 */
class World : public Object {
    public:
        /**
         * Constructs a world.
         */
        World(jobject instance, JNIEnv *env);
        ~World();
        /**
         * Returns the entity list object.
         */
        jobject GetEntityList();
        /**
         * Returns the player list object.
         */
        jobject GetPlayerList();
    private:
        jclass worldClass;
};