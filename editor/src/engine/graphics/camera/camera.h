#pragma once

#include "../../../maths/mat4.h"
#include "../../../maths/mathFuncs.h"
#include "../../../maths/vec2.h"
#include "../../../maths/vec2_int.h"
#include "../../../maths/vec3.h"
#include "../../system/window/window.h"
#include "../renderable/bounds.h"
#include "./ortho_projection_info.h"

namespace spright
{
namespace engine
{
    using namespace ::spright::maths;

    class Camera
    {
    public:
        Camera(const Window *window, float near = -1.0f, float far = 1.0f, int zoomFactor = 17);

        void translate2D(Vec2 delta);

        void setTranslate(Vec2 translate);

        void setZoom(float zoom);

        void zoomIn();

        void zoomOut();

        void zoomToFit(const Bounds &bounds);

        float getZoom();

        const Mat4 getProjectionMatrix() const;

        const Mat4 &getViewMatrix() const;

        Vec2 getCenter2D();

        Vec2 screenToWorldPos(float x, float y) const;

        Vec2Int worldToScreenPos(float x, float y) const;

    private:
        float getScaleFactor() const;

    private:
        Mat4 m_ProjectionMatrix;

        Mat4 m_View;

        Vec2 m_Translate;

        float m_Near;

        float m_Far;

        float m_Z = 0.5f;

        float m_Zoom = 2.0f;

        int m_ZoomFactor = 1;

        const Window *m_Window;
    };
} // namespace engine
} // namespace spright
