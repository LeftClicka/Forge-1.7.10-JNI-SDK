#pragma once

#include "Java.h"

#include "Math.h"
#include "Object.h"

/**
 * Utility functions for 2D rendering.
 */
namespace Render2D {

    /**
     * Draws text using minecraft's font renderer.
     */
    void DrawText(const char *text, int x, int y, int color, JNIEnv *env);

    /**
     * Draws text using minecraft's font renderer and a bloom effect.
     */
    void DrawTextWithBloom(const char *text, int x, int y, int color, JNIEnv *env);

    /**
     * Draws a rectangle.
     * 
     * Uses raw OpenGL, so no JNIEnv pointer required!
     */
    void DrawRect(int x1, int y1, int x2, int y2, int color);

    /**
     * Draws a rectangle with a bloom effect.
     * 
     * Uses raw OpenGL, so no JNIEnv pointer required!
     */
    void DrawRectWithBloom(int x1, int y1, int x2, int y2, int color);

    /**
     * Returns the font height.
     */
    int GetFontHeight(JNIEnv *env);

    /**
     * Returns the render width of a given string.
     */
    int GetStringWidth(const char *str, JNIEnv *env);

    /**
     * Returns the screen resolution as a Vec2.
     */
    Vec2 GetResolution(JNIEnv *env);

    /**
     * Returns a local reference to minecraft's font renderer object.
     */
    jobject GetFontRendererObject(JNIEnv *env);

}