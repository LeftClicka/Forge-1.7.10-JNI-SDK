#include "Render2D.h"

#include "Minecraft.h"
#include "Timer.h"
#include "GL11.h"

namespace Render2D {

    static const unsigned int GL_SRC_ALPHA = GL11::GetGLConst("GL_SRC_ALPHA"), GL_ONE_MINUS_SRC_ALPHA = GL11::GetGLConst("GL_ONE_MINUS_SRC_ALPHA");

    void DrawText(const char *text, int x, int y, int color, JNIEnv *env) {
        static jmethodID drawStringMethod = Java::GetMethod("net/minecraft/client/gui/FontRenderer", "func_78276_b", "(Ljava/lang/String;III)I", env);

        jstring jText = env->NewStringUTF(text);
        jobject fontRenderer = GetFontRendererObject(env);

        env->CallIntMethod(fontRenderer, drawStringMethod, jText, x, y, color);

        env->DeleteLocalRef(jText);
        env->DeleteLocalRef(fontRenderer);
    }

    void DrawTextWithBloom(const char *text, int x, int y, int color, JNIEnv *env) {
        GL11::PushMatrix();
        GL11::BlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        const float pulse = Math::GetPulse(3500);
        constexpr int alphaMin = 64;
        constexpr int alphaMax = 128; 
        const int alpha = (int)(alphaMin + pulse * (alphaMax - alphaMin));
        const int bloomColor = (alpha << 24) | (color & 0x00FFFFFF);

        constexpr float radius = 1.0f;
        constexpr int layers = 8;

        static jmethodID drawStringMethod = Java::GetMethod("net/minecraft/client/gui/FontRenderer", "func_78276_b", "(Ljava/lang/String;III)I", env);
        jstring jText = env->NewStringUTF(text);
        jobject fontRenderer = GetFontRendererObject(env);

        //render bloom
        for (int i = 0; i < layers; i++) {
            double angle = (2 * Math::PI / layers) * i;
            float xOffset = (float)(cos(angle) * radius);
            float yOffset = (float)(sin(angle) * radius);
            env->CallIntMethod(fontRenderer, drawStringMethod, jText, x + (int)xOffset, y + (int)yOffset, bloomColor);
        }

        //render original text
        env->CallIntMethod(fontRenderer, drawStringMethod, jText, x, y, color);

        env->DeleteLocalRef(jText);
        env->DeleteLocalRef(fontRenderer);
        GL11::PopMatrix();
    }

    void DrawRect(int x1, int y1, int x2, int y2, int color) {
        static const unsigned int GL_QUADS= GL11::GetGLConst("GL_QUADS");
        GL11::Color(color);
        GL11::Begin(GL_QUADS);
        GL11::Vertex2i(x1, y1);
        GL11::Vertex2i(x1, y2);
        GL11::Vertex2i(x2, y1);
        GL11::Vertex2i(x2, y2);
        GL11::End();
    }

    void DrawRectWithBloom(int x1, int y1, int x2, int y2, int color) {
        GL11::BlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        const float pulse = Math::GetPulse(3500);
        constexpr int alphaMin = 64;
        constexpr int alphaMax = 128; 
        const int alpha = (int)(alphaMin + pulse * (alphaMax - alphaMin));
        const int bloomColor = (alpha << 24) | (color & 0x00FFFFFF);

        DrawRect(x1-1, y1-1, x2+1, y2+1, bloomColor);
        DrawRect(x1, y1, x2, y2, color);
    }

    jobject GetFontRendererObject(JNIEnv *env) {
        static jfieldID fontRendererField = Java::GetField("net/minecraft/client/Minecraft", "field_71466_p", "Lnet/minecraft/client/gui/FontRenderer;", env);
        jobject mc = Minecraft::GetObject(env);
        jobject fontRenderer = env->GetObjectField(mc, fontRendererField);
        env->DeleteLocalRef(mc);
        return fontRenderer;
    }

}