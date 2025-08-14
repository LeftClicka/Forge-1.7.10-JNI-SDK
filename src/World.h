#pragma once

#include "Object.h"
#include "Entity.h"
#include "List.h"

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
        List GetEntityList();
        /**
         * Returns a list containing only loaded entities that pass the specified filter.
         */
        List GetFilteredEntityList(std::function<bool(Entity*)> filter);
        /**
         * Returns the player list object.
         */
        List GetPlayerList();
    private:
        jclass worldClass;
};