#include "GL11.h"

#include <windows.h>
#include <cstring>

/**
 * TODO: As of now there is no error handling for when GetProcAddress fails.
 */
namespace GL11 {

    using FN_PushMatrix = void(APIENTRY*)();
    using FN_PopMatrix = void(APIENTRY*)();
    using FN_Enable = void(APIENTRY*)(unsigned int);
    using FN_Disable = void(APIENTRY*)(unsigned int);
    using FN_BlendFunc = void(APIENTRY*)(unsigned int, unsigned int);
    using FN_Translate = void(APIENTRY*)(float, float, float);
    using FN_Begin = void(APIENTRY*)(unsigned int);
    using FN_End = void(APIENTRY*)();
    using FN_Color3f = void(APIENTRY*)(float, float, float);
    using FN_Color4f = void(APIENTRY*)(float, float, float, float);
    using FN_Vertex2 = void(APIENTRY*)(int, int);

    static FN_PushMatrix glPushMatrix = nullptr;
    static FN_PopMatrix glPopMatrix = nullptr;
    static FN_Enable glEnable = nullptr;
    static FN_Disable glDisable = nullptr;
    static FN_BlendFunc glBlendFunc = nullptr;
    static FN_Translate glTranslate = nullptr;
    static FN_Begin glBegin = nullptr;
    static FN_End glEnd = nullptr;
    static FN_Color3f glColor3f = nullptr;
    static FN_Color4f glColor4f = nullptr;
    static FN_Vertex2 glVertex2i = nullptr;

    constexpr int GL_BLEND = 0x0BE2;
    constexpr int GL_MODELVIEW = 0x1700;
    constexpr int GL_PROJECTION = 0x1701;
    constexpr int GL_TEXTURE_2D = 0x0DE1;
    constexpr int GL_DEPTH_TEST = 0x0B71;
    constexpr int GL_SRC_ALPHA = 0x0302;
    constexpr int GL_ONE_MINUS_SRC_ALPHA = 0x0303;
    constexpr int GL_ONE = 0x0001;
    constexpr int GL_QUADS = 0x0007;

    static HMODULE GL_MODULE = GetModuleHandleA("opengl32.dll");

    /**
     * TODO: Implement this better; this works for now though.
     */
    int GetGLConst(const char *name) {
        if (!name) return -1;

        if (strcmp(name, "GL_BLEND") == 0) return GL_BLEND;
        if (strcmp(name, "GL_MODELVIEW") == 0) return GL_MODELVIEW;
        if (strcmp(name, "GL_PROJECTION") == 0) return GL_PROJECTION;
        if (strcmp(name, "GL_TEXTURE_2D") == 0) return GL_TEXTURE_2D;
        if (strcmp(name, "GL_DEPTH_TEST") == 0) return GL_DEPTH_TEST;
        if (strcmp(name, "GL_SRC_ALPHA") == 0) return GL_SRC_ALPHA;
        if (strcmp(name, "GL_ONE_MINUS_SRC_ALPHA") == 0) return GL_ONE_MINUS_SRC_ALPHA;
        if (strcmp(name, "GL_ONE") == 0) return GL_ONE;
        if (strcmp(name, "GL_QUADS") == 0) return GL_QUADS;

        return -1;
    }

    void PushMatrix() {
        if (!glPushMatrix) {
            glPushMatrix = (FN_PushMatrix) GetProcAddress(GL_MODULE, "glPushMatrix"); 
        }
        glPushMatrix();
    }

    void PopMatrix() {
        if (!glPopMatrix) {
            glPopMatrix = (FN_PopMatrix) GetProcAddress(GL_MODULE, "glPopMatrix");
        }
        glPopMatrix();
    }

    void Enable(int mode) {
        if (!glEnable) {
            glEnable = (FN_Enable) GetProcAddress(GL_MODULE, "glEnable");
        }
        glEnable(static_cast<unsigned int>(mode));
    }

    void Disable(int mode) {
        if (!glDisable) {
            glDisable = (FN_Disable) GetProcAddress(GL_MODULE, "glDisable");
        } 
        glDisable(static_cast<unsigned int>(mode));
    }

    void BlendFunc(int param1, int param2) {
        if (!glBlendFunc) {
            glBlendFunc = (FN_BlendFunc) GetProcAddress(GL_MODULE, "glBlendFunc");
        }
        glBlendFunc(static_cast<unsigned int>(param1), static_cast<unsigned int>(param2));
    }

    void Translate(float x, float y, float z) {
        if (!glTranslate) {
            glTranslate = (FN_Translate) GetProcAddress(GL_MODULE, "glTranslatef");
        }
        glTranslate(x, y, z);
    }

    void Begin(int mode) {
        if (!glBegin) {
            glBegin = (FN_Begin) GetProcAddress(GL_MODULE, "glBegin");
        }
        glBegin(mode);
    }

    void End() {
        if (!glEnd) {
            glEnd = (FN_End) GetProcAddress(GL_MODULE, "glEnd");
        }
        glEnd();
    }

    void Color3f(float r, float g, float b) {
        if (!glColor3f) {
            glColor3f = (FN_Color3f) GetProcAddress(GL_MODULE, "glColor3f");
        }
        glColor3f(r, g, b);
    }

    void Color4f(float r, float g, float b, float a) {
        if (!glColor4f) {
            glColor4f = (FN_Color4f) GetProcAddress(GL_MODULE, "glColor4f");
        }
        glColor4f(r, g, b, a);
    }

    void Color(int color) {
        const int alpha = (color >> 24) & 0xFF;
        const int red   = (color >> 16) & 0xFF;
        const int green = (color >> 8)  & 0xFF;
        const int blue  = (color)       & 0xFF;
        Color4f(red/255.0f, green/255.0f, blue/255.0f, alpha/255.0f);
    }

    void Vertex2i(int x, int y) {
        if (!glVertex2i) {
            glVertex2i = (FN_Vertex2) GetProcAddress(GL_MODULE, "glVertex2i");
        }
        glVertex2i(x, y);
    }

}