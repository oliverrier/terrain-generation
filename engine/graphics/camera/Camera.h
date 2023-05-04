#pragma once
#include <utils/math/Math.h>

using Mat4f = Mat4<float>;
using Point3f = Point3d<float>;

class Camera {
public:

    Camera() {
        _cameraYaw = 0.f;
        _cameraPitch = 0.f;
        _cameraSpeed = 1.f;
    };

    Point3f _cameraPos;
    float _cameraYaw;
    float _cameraPitch;
    float _cameraSpeed;


    const float _aspect = 800.f / 600.f;
    const float _fov = 45.f / 180.f * 3.141592f;
    const float _nearPlane = 0.1f;
    const float _farPlane = 100.f;

    Mat4f ViewMatrix;
    Mat4f ProjectionMatrix = Mat4<float>::projection(_aspect, _fov, _farPlane, _nearPlane);
};