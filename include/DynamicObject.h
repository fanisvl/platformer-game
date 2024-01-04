#pragma once

class DynamicObject {
    const float mGravity = 10.0f;
    const float mAccelVertical = 150.0f;
    const float mAccelHorizontal = 20.0f;
    const float mMaxVelocity = 100.0f;
public:
    float mVelocityX = 0.0f;
    float mVelocityY = 0.0f;
};