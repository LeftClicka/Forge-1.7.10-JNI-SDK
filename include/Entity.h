#pragma once

#include "Object.h"
#include "Math.h"

/**
 * Wraps a jobject to expose interface for minecraft's entity class.
 */
class Entity : public Object {
    public:
        /**
         * Constructs an entity.
         */
        Entity(jobject instance, JNIEnv *env);
        ~Entity();
        /**
         * Returns the entity's current position as a Vec3
         */
        Vec3 GetPosition();
        /**
         * Returns the entity's current motion as a Vec3
         */
        Vec3 GetMotion();
        /**
         * Sets the entity's motion.
         * Takes the three arguments in wrapped into a Vec3.
         */
        void SetMotion(Vec3 motion);
        /**
         * Returns current yaw and pitch of the entity wrapped into an Angles struct (Vec2).
         */
        Angles GetAngles();
        /**
         * Sets the entity's yaw and pitch.
         * Takes the two arguments in wrapped into an Angles struct (Vec2).
         */
        void SetAngles(Angles angles);
        /**
         * Returns the entity's ID.
         */
        int GetEntityID();
        /**
         * Returns the entity's current hurt resistant time.
         */
        int GetHurtResistantTime();
        /**
         * Returns the entity's current falling distance.
         */
        float GetFallDistance();
        /**
         * Returns whether the entity is a player.
         */
        bool IsPlayer();
    private:
        jclass entityClass;
        jclass playerClass;
        jfieldID posXField, posYField, posZField;
        jfieldID motionXField, motionYField, motionZField;
        jfieldID yawField, pitchField;
        jfieldID entityIdField;
        jfieldID hurtResistanceField;
        jfieldID fallDistanceField;
};