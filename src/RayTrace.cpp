#include "RayTrace.h"

RayTraceResult::RayTraceResult(jobject instance, JNIEnv *env) : Object(instance, env) {
    jclass clazz = Java::GetClass("net/minecraft/util/MovingObjectPosition", env);
    this->entityHitField = env->GetFieldID(clazz, "field_72308_g", "Lnet/minecraft/entity/Entity;");
    this->hitTypeField = env->GetFieldID(clazz, "field_72313_a", "Lnet/minecraft/util/MovingObjectPosition$MovingObjectType;");
    this->TYPE_ENTITY = Java::GetEnumGlobal("net/minecraft/util/MovingObjectPosition$MovingObjectType", "ENTITY", "Lnet/minecraft/util/MovingObjectPosition$MovingObjectType;", env);
    this->TYPE_BLOCK = Java::GetEnumGlobal("net/minecraft/util/MovingObjectPosition$MovingObjectType", "BLOCK", "Lnet/minecraft/util/MovingObjectPosition$MovingObjectType;", env);
    env->DeleteLocalRef(clazz);
}

RayTraceResult::~RayTraceResult() {
    env->DeleteGlobalRef(TYPE_ENTITY);
    env->DeleteGlobalRef(TYPE_BLOCK);
}

jobject RayTraceResult::GetHitEntity() {
    return env->GetObjectField(instance, entityHitField);
}

jobject RayTraceResult::GetHitType() {
    return env->GetObjectField(instance, hitTypeField);
}

bool RayTraceResult::HitsEntity() {
    jobject hitType = GetHitType();
    bool flag = env->IsSameObject(hitType, TYPE_ENTITY);
    env->DeleteLocalRef(hitType);
    return flag;
}

bool RayTraceResult::HitsBlock() {
    jobject hitType = GetHitType();
    bool flag = env->IsSameObject(hitType, TYPE_BLOCK);
    env->DeleteLocalRef(hitType);
    return flag;
}