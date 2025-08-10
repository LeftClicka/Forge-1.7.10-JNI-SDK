#pragma once

#include "Object.h"
#include "Entity.h"

#include <functional>

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
         * Returns a list containing only loaded entities that pass the specified filter.
         */
        jobject GetFilteredEntityList(std::function<bool(Entity*)> filter);
        /**
         * Returns the player list object.
         */
        jobject GetPlayerList();
    private:
        jclass worldClass;
};