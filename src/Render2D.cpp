#include "Render2D.h"

namespace Render2D {

    void DrawTextWithBloom(const char *text, int x, int y, int color, JNIEnv *env) {

    }

    void DrawText(const char *text, int x, int y, int color, JNIEnv *env) {
        jobject fontRenderer = GetFontRendererObject(env);

        env->DeleteLocalRef(fontRenderer);
    }

    jobject GetFontRendererObject(JNIEnv *env) {

    }

}