#pragma once 

namespace GL11 {

    /**
     * Returns a GL constant matching the name passed in. Returns -1 if not found. Results should be cached.
     */
    int GetGLConst(const char *name);

    void PushMatrix();

    void PopMatrix();

    void Enable(int mode);

    void Disable(int mode);

    void BlendFunc(int param1, int param2);

    void Translate(float x, float y, float z);

    void Begin(int mode);

    void End();

    void Color3f(float r, float g, float b);

    void Color4f(float r, float g, float b, float a);

    void Color(int color);

    void Vertex2i(int x, int y);

}