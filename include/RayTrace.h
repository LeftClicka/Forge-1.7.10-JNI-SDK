#pragma once

#include "Object.h"

/**
 * Wraps a jobject to expose the MovingObjectPosition interface.
 */
class RayTraceResult : public Object {
    public:
        /**
         * Constructs a ray trace result.
         */
        RayTraceResult(jobject instance, JNIEnv *env);
        ~RayTraceResult();
        /**
         * Returns the entity that was hit, null if no entity was hit.
         */
        jobject GetHitEntity();
        /**
         * Returns the type of hit, as an enum constant.
         * 
         * Should probably not use this directly, instead use HitsEntity() and HitsBlock().
         */
        jobject GetHitType();
        /**
         * Returns whether this ray trace hits an entity.
         * 
         * If this returns true, GetHitEntity() will return non-null.
         */
        bool HitsEntity();
        /**
         * Returns whether this ray trace hits a block.
         */
        bool HitsBlock();
        /**
         * Returns whether this ray trace missed both blocks and entities.
         */
        inline bool IsMiss() {
            return !HitsEntity() && !HitsBlock();
        }
    private:
        jfieldID entityHitField;
        jfieldID hitTypeField;
        jobject TYPE_ENTITY, TYPE_BLOCK;
};