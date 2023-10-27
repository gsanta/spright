#pragma once
#include "../../graphics/renderable/bounds.h"

namespace spright
{
namespace engine
{
    class Canvas
    {
    public:
        Canvas(const Bounds &bounds);

        const Bounds &getBounds() const;

        // Layer &getDecorationLayer();

    private:
        Bounds m_Bounds;
    };
} // namespace engine
} // namespace spright
