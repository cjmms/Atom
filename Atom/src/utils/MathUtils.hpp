

#ifndef MATHUTILS_HPP
#define MATHUTILS_HPP
#include "Pch.hpp"
#include "core/Types.hpp"




glm::mat4 Rotate(const int i, const float theta)
{
    glm::mat4 R;
    const float radians = theta * PI / 180;
    const float cosRad = cos(radians);
    const float sinRad = sin(radians);
    if (i == 0)
    {
        R = glm::mat4(
            1.0f, 0.0f, 0.0f, 0.0f,
            0.0f, cosRad, -sinRad, 0.0f,
            0.0f, sinRad, cosRad, 0.0f,
            0.0f, 0.0f, 0.0f, 1.0);
    }
    else if (i == 1)
    {
        R = glm::mat4(
            cosRad, 0.0f, sinRad, 0.0f,
            0.0f, 1.0f, 0.0f, 0.0f,
            -sinRad, 0.0f, cosRad, 0.0f,
            0.0f, 0.0f, 0.0f, 1.0);
    }
    else if (i == 2)
    {
        R = glm::mat4(
            cosRad, -sinRad, 0.0f, 0.0f,
            sinRad, cosRad, 0.0f, 0.0f,
            0.0f, 0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 1.0);
    }
    return R;
}

// Return a scale matrix
glm::mat4 Scale(const float x, const float y, const float z)
{
    const glm::mat4 S = glm::mat4(
        x, 0.0f, 0.0f, 0.0f,
        0.0f, y, 0.0f, 0.0f,
        0.0f, 0.0f, z, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0);
    return S;
}

// Return a translation matrix
glm::mat4 Translate(const float x, const float y, const float z)
{
    //todo y is inverted ?
    const glm::mat4 T = glm::mat4(
        1.0f, 0.0f, 0.0f, x,
        0.0f, 1.0f, 0.0f, -y,
        0.0f, 0.0f, 1.0f, z,
        0.0f, 0.0f, 0.0f, 1.0);
    return T;
}

#endif 


















/*

nclude <Pch.hpp>
#include "Transform.hpp"

Transform::Transform()// : Component(TYPE_TRANSFORM)
{
    positionX = positionY = 0.0f;
    scaleX = scaleY = 0.1f;
    angle = 0.0f;

    transformationMatrix = glm::mat4(0.0);
}

Transform::~Transform()
{

}

void Transform::Update()
{
    transformationMatrix = Scale(scaleX, scaleY, 1) * Rotate(2, angle) * Translate(positionX, positionY, positionZ);
    //mTransformationMatrix = Rotate(2, mAngle) * Translate(mPositionX, mPositionY, mPositionZ) * Scale(mScaleX, mScaleY, 1);
    //mTransformationMatrix = Rotate(2, mAngle) * Scale(mScaleX, mScaleY, 1);

}

float* Transform::GetTransform()
{
    return &(transformationMatrix[0][0]);
}

const float pi = 3.14159f;
glm::mat4 Transform::Rotate(const int i, const float theta)
{
    glm::mat4 R;
    const float radians = theta * pi / 180;
    const float cosRad = cos(radians);
    const float sinRad = sin(radians);
    if (i == 0)
    {
        R = glm::mat4(
            1.0f, 0.0f, 0.0f, 0.0f,
            0.0f, cosRad, -sinRad, 0.0f,
            0.0f, sinRad, cosRad, 0.0f,
            0.0f, 0.0f, 0.0f, 1.0);
    }
    else if (i == 1)
    {
        R = glm::mat4(
            cosRad, 0.0f, sinRad, 0.0f,
            0.0f, 1.0f, 0.0f, 0.0f,
            -sinRad, 0.0f, cosRad, 0.0f,
            0.0f, 0.0f, 0.0f, 1.0);
    }
    else if (i == 2)
    {
        R = glm::mat4(
            cosRad, -sinRad, 0.0f, 0.0f,
            sinRad, cosRad, 0.0f, 0.0f,
            0.0f, 0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 1.0);
    }
    return R;
}

// Return a scale matrix
glm::mat4 Transform::Scale(const float x, const float y, const float z)
{
    const glm::mat4 S = glm::mat4(
        x, 0.0f, 0.0f, 0.0f,
        0.0f, y, 0.0f, 0.0f,
        0.0f, 0.0f, z, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0);
    return S;
}

// Return a translation matrix
glm::mat4 Transform::Translate(const float x, const float y, const float z)
{
    //todo y is inverted ?
    const glm::mat4 T = glm::mat4(
        1.0f, 0.0f, 0.0f, x,
        0.0f, 1.0f, 0.0f, -y,
        0.0f, 0.0f, 1.0f, z,
        0.0f, 0.0f, 0.0f, 1.0);
    return T;
}




*/