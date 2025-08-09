#pragma once

#include "Object.h"
#include "Entity.h"

#undef GetObject

/**
 * Use instances of this class are used to expose the Minecraft class' interface.
 */
class Minecraft : public Object {
    public:
        /**
         * Returns a local ref to the minecraft class.
         */
        static jclass GetClass(JNIEnv *env);
        /**
         * Returns a local ref to the singleton minecraft object.
         */
        static jobject GetObject(JNIEnv *env);
        /**
         * Constructs a minecraft.
         * 
         * No underlying jobject is passed to a Minecraft instance because, on the java side, it is a singleton.
         * A global reference is used under the hood, but it is deleted in the destructor.
         */
        Minecraft(JNIEnv *env);
        ~Minecraft();
        /**
         * Returns whether the player is in game.
         */
        bool IsInGame();
        /**
         * Returns whether the gameplay has focus (the player is not inside a GUI).
         */
        bool HasGameplayFocus();
        /**
         * Returns the local player object.
         */
        jobject GetPlayer();
        /**
         * Returns the local world object.
         */
        jobject GetWorld();
        /**
         * Returns the latest ray trace result (MovingObjectPosition) object.
         */
        jobject GetCurrentRayTrace();
    private:
        jfieldID playerField, worldField, rayTraceField;
        jfieldID gameFocusField;    
};