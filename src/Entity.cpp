#include "Entity.h"

Entity::Entity(jobject instance, JNIEnv *env) : Object (instance, env) {
    jclass clazz = Java::GetClass("net/minecraft/entity/Entity", env);

    this->entityClass = (jclass) (env->NewGlobalRef(clazz));
    this->posXField = env->GetFieldID(clazz, "field_70165_t", "D");
    this->posYField = env->GetFieldID(clazz, "field_70163_u", "D");
    this->posZField = env->GetFieldID(clazz, "field_70161_v", "D");
    this->motionXField = env->GetFieldID(clazz, "field_70159_w", "D");
    this->motionYField = env->GetFieldID(clazz, "field_70181_x", "D");
    this->motionZField = env->GetFieldID(clazz, "field_70179_y", "D");
    this->yawField = env->GetFieldID(clazz, "field_70177_z", "F");
    this->pitchField = env->GetFieldID(clazz, "field_70125_A", "F");
    this->entityIdField = env->GetFieldID(clazz, "field_145783_c", "I");
    this->fallDistanceField = env->GetFieldID(clazz, "field_70143_R", "F");
    this->hurtResistanceField = env->GetFieldID(clazz, "field_70172_ad", "I");

    env->DeleteLocalRef(clazz);

    clazz = Java::GetClass("net/minecraft/entity/player/EntityPlayer", env);
    this->playerClass = (jclass) env->NewGlobalRef(clazz);

    env->DeleteLocalRef(clazz);
}

Entity::~Entity() {
    env->DeleteGlobalRef(this->entityClass);
    env->DeleteGlobalRef(this->playerClass);
}

Vec3 Entity::GetPosition() {
    return Vec3 {
        env->GetDoubleField(instance, posXField),
        env->GetDoubleField(instance, posYField),
        env->GetDoubleField(instance, posZField)
    };
}

Vec3 Entity::GetMotion() {
    return Vec3 {
        env->GetDoubleField(instance, motionXField),
        env->GetDoubleField(instance, motionYField),
        env->GetDoubleField(instance, motionZField)
    };
}

void Entity::SetMotion(Vec3 motion) {
    env->SetDoubleField(instance, motionXField, motion.x);
    env->SetDoubleField(instance, motionYField, motion.y);
    env->SetDoubleField(instance, motionZField, motion.z);
}

Angles Entity::GetAngles() {
    return Angles {
        env->GetFloatField(instance, yawField),
        env->GetFloatField(instance, pitchField)
    };
}

void Entity::SetAngles(Angles angles) {
    env->SetFloatField(instance, yawField, angles.a);
    env->SetFloatField(instance, pitchField, angles.b);
}

int Entity::GetEntityID() {
    return env->GetIntField(instance, entityIdField);
}

int Entity::GetHurtResistantTime() {
    return env->GetIntField(instance, hurtResistanceField);
}

float Entity::GetFallDistance() {
    return env->GetFloatField(instance, fallDistanceField);
}

bool Entity::IsPlayer() {
    return instance != nullptr && env->IsInstanceOf(instance, playerClass);
}