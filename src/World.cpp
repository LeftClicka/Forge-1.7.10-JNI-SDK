#include "World.h"

#include "List.h"

World::World(jobject instance, JNIEnv *env) : Object(instance, env) {
    jclass _class = Java::GetClass("net/minecraft/world/World", env);
    this->worldClass = (jclass) env->NewGlobalRef(_class);
    env->DeleteLocalRef(_class);
}

World::~World() {
    env->DeleteGlobalRef(worldClass);
}

List World::GetEntityList() {
    static jfieldID entityListField = env->GetFieldID(worldClass, "field_72996_f", "Ljava/util/List;");
    return List(env->GetObjectField(instance, entityListField), env);
}

List World::GetFilteredEntityList(std::function<bool(Entity*)> filter) {
    List list = GetEntityList();
    jobject filteredList = list.GetFilteredSubList([filter, this](jobject obj) {
        Entity e(obj, this->env);
        return filter(&e);
    });
    return List(filteredList, env);
}

List World::GetPlayerList() {
    static jfieldID playerListField = env->GetFieldID(worldClass, "field_73010_i", "Ljava/util/List;");
    return List(env->GetObjectField(instance, playerListField), env);
}