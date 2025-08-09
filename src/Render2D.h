#pragma once

#include "Java.h"

/**
 * NOT YET IMPLEMENTED
 */
namespace Render2D {

    void DrawTextWithBloom(const char *text, int x, int y, int color, JNIEnv *env);

    void DrawText(const char *text, int x, int y, int color);

    jobject GetFontRendererObject(JNIEnv *env);

}