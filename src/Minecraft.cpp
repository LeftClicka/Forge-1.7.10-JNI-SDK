#include "Minecraft.h"

jclass Minecraft::GetClass(JNIEnv *env) {
    return Java::GetClass("net/minecraft/client/Minecraft", env);
}

jobject Minecraft::GetObject(JNIEnv *env) {
    jclass clazz = GetClass(env);
    static jfieldID mcField = env->GetStaticFieldID(clazz, "field_71432_P", "Lnet/minecraft/client/Minecraft;");
    jobject obj = env->GetStaticObjectField(clazz, mcField);
    env->DeleteLocalRef(clazz);
    return obj;
}


Minecraft::Minecraft(JNIEnv *env) : Object(GetObject(env), env) {
    jclass mcClass = GetClass(env);

    this->playerField = env->GetFieldID(mcClass, "field_71439_g", "Lnet/minecraft/client/entity/EntityClientPlayerMP;");
    this->worldField = env->GetFieldID(mcClass, "field_71441_e", "Lnet/minecraft/client/multiplayer/WorldClient;");
    this->gameFocusField = env->GetFieldID(mcClass, "field_71415_G", "Z");
    this->rayTraceField = env->GetFieldID(mcClass, "field_71476_x", "Lnet/minecraft/util/MovingObjectPosition;");

    env->DeleteLocalRef(mcClass);
}

Minecraft::~Minecraft() {
    this->env->DeleteGlobalRef((this->instance));
}

bool Minecraft::IsInGame() {
    jobject player = env->GetObjectField(instance, playerField);
    jobject world = env->GetObjectField(instance, worldField);
    bool flag = player != nullptr && world != nullptr;
    env->DeleteLocalRef(player);
    env->DeleteLocalRef(world);
    return flag;
}

bool Minecraft::HasGameplayFocus() {
    return env->GetBooleanField(instance, gameFocusField);
}

Entity Minecraft::GetPlayer() {
    return Entity(env->GetObjectField(instance, playerField), env);
}

World Minecraft::GetWorld() {
    return World(env->GetObjectField(instance, worldField), env);
}

RayTraceResult Minecraft::GetCurrentRayTrace() {
    return RayTraceResult(env->GetObjectField(instance, rayTraceField), env);
}
