#pragma once 

#include <windows.h>
#include <utility>

namespace GL11 {

    /**
     * Returns a GL constant matching the name passed in. Returns -1 if not found. Results should be cached.
     */
    int GetGLConst(const char *name);

    /**
     * Calls glPushMatrix.
     */
    void PushMatrix();

    /**
     * Calls glPopMatrix().
     */
    void PopMatrix();

    /**
     * Calls glEnable(unsigned int mode)
     */
    void Enable(unsigned int mode);

    /**
     * Calls glDisable(unsigned int mode);
     */
    void Disable(unsigned int mode);

    /**
     * Calls glBlendFunc(int param1, int param2);
     */
    void BlendFunc(int param1, int param2);

    /**
     * Calls glTranslate3f(float x, float y, float z).
     */
    void Translate(float x, float y, float z);

    /**
     * Calls glBegin(int mode);
     */
    void Begin(int mode);

    /**
     * Calls glEnd().
     */
    void End();

    /**
     * Calls glColor3f(float r, float g, float b).
     */
    void Color3f(float r, float g, float b);

    /**
     * Calls glColor4f(float r, float g, float b, float a).
     */
    void Color4f(float r, float g, float b, float a);

    /**
     * Extracts ARGB values from the parameter and calls glColor4f(float r, float g, float b, float a).
     * 
     * Color parameter should be in ARGB format (format used by Minecraft's java code).
     */
    void Color(int color);

    /**
     * Calls glVertex2i(int x, int y).
     */
    void Vertex2i(int x, int y);

    /**
     * Returns a pointer to a GL function.
     */
    void *GetGLProc(const char *name);

    /**
     * Calls any GL function.
     * 
     * Use this if the function you need is not explicitly implemented here (yet).
     */
    template<typename R, typename... ARGS>
    R Call(const char *functionName, ARGS... args) {
        using FnPtr = R(*)(ARGS...);
        FnPtr fnPtr = reinterpret_cast<FnPtr>(GetGLProc(functionName));
        return fnPtr(std::forward<ARGS>(args)...);
    }

}