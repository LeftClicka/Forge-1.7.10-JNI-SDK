#include "SDK.h"

void Example() {
    Java::Attach();

    Java::GetEnv()->PushLocalFrame(16);

    Minecraft minecraft(Java::GetEnv());

    Java::GetEnv()->PopLocalFrame(nullptr);

    Java::Detach();

}