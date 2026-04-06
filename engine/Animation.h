#pragma once

class Animation {
public:
    int frameCount;
    float frameTime;

    float timer = 0.0f;
    int currentFrame = 0;

    Animation(int frames, float speed)
        : frameCount(frames), frameTime(speed) {}

    void update(float dt) {
        timer += dt;
        if (timer >= frameTime) {
            timer = 0;
            currentFrame = (currentFrame + 1) % frameCount;
        }
    }

    float getU1() { return (float)currentFrame / frameCount; }
    float getU2() { return (float)(currentFrame + 1) / frameCount; }
};
