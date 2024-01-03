#pragma once
#include <cmath>
#include <algorithm>
#include "graphics.h"

struct Box
{
    float mPosX = 0.0f;
    float mPosY = 0.0f;
    float mWidth = 1.0f;
    float mHeight = 1.0f;
    float mSpeed = 1.0f;

    /** Detects intersection (overlap) between this Box and another Box instance.
    *   \param other is a reference to another Box instance to check for collision with
    *   \return true if the two boxes overlap
    */
    bool intersect(const Box &other)
    {
        return (fabs(mPosX - other.mPosX) * 2.0f < (mWidth + other.mWidth)) &&
               (fabs(mPosY - other.mPosY) * 2.0f < (mHeight + other.mHeight));
    }

    /** Detects an intersection when this Box is "above" (smaller y values) a target box (other)
    *   and reports the adjustment offset so that the two boxes are separated.
    *
    *   \param other is the second (target) Box to test collision on the vertical axis with.
    *   \return the offset this Box needs to move in the y axis, so that it does not collide
    *   anymore with the target Box (other), or 0.0f if no collision is found.
    */
    float intersectDown(Box &other)
    {
        if (fabs(mPosX - other.mPosX) * 2.0f >= (mWidth + other.mWidth) || mPosY > other.mPosY)
            return 0.0f;
        return std::min<float>(0.0f, other.mPosY - (other.mHeight / 2.0f) - mPosY - (mHeight / 2.0f));
    }

    /** Detects a horizontal intersection this Box is beside a target box (other).
    *   and reports the adjustment offset so that the two boxes are separated.
    *
    *   \param other is the second (target) Box to test collision on the horizontal axis with.
    *   \return the offset this Box needs to move in the x axis, so that it does not collide
    *   anymore with the target Box (other), or 0.0f if no collision is found.
    */
    float intersectSideways(Box &other)
    {
        if (fabs(mPosY - other.mPosY) * 2.0f >= (mWidth + other.mWidth))
            return 0.0f;
        if (mPosX > other.mPosX)
            return std::max<float>(0.0f, other.mPosX + (other.mWidth / 2.0f) - mPosX + (mWidth / 2.0f));
        else
            return std::min<float>(0.0f, other.mPosX - (other.mWidth / 2.0f) - mPosX - (mWidth / 2.0f));
    }

    virtual void move(float dx, float dy) {};

    /** Default ctor
    */
    Box() {}

    /** Basic Box ctor.
    *   \param x is the x coordinate of the box center
    *   \param y is the y coordinate of the box center
    *   \param w is the mWidth of the box
    *   \param h is the mHeight of the box
    */
    Box(float x, float y, float w, float h)
            : mPosX(x), mPosY(y), mWidth(w), mHeight(h) {}
};

