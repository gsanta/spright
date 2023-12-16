#include "temp_rect_drawer.h"

namespace spright
{
namespace editing
{
    void TempRectDrawer::reset()
    {
        m_Filled = nullptr;
        m_OutlinedTop = nullptr;
        m_OutlinedRight = nullptr;
        m_OutlinedBottom = nullptr;
        m_OutlinedLeft = nullptr;
    }

    const Bounds &TempRectDrawer::getBounds() const
    {
        return m_Bounds;
    }

    void TempRectDrawer::drawFilled(TileLayer &tileLayer, Vec2 from, Vec2 to, int color)
    {
        if (m_Filled == nullptr)
        {
            m_Filled = &tileLayer.add(Rect2D(0, 0, 0.1f, 0.1f, color));
        }

        float tileSize = tileLayer.getTileSize();

        Bounds bounds = Bounds::createWithPositions(tileLayer.getCenterPos(from), tileLayer.getCenterPos(to));
        bounds.expandWith(tileSize / 2.0);

        m_Filled->setPosition2d(bounds.getCenter());
        m_Filled->setSize(Vec2(bounds.getWidth(), bounds.getHeight()));

        m_Bounds = bounds;
    }

    void TempRectDrawer::drawOutlined(TileLayer &tileLayer, Vec2 from, Vec2 to, int color)
    {
        float tileSize = tileLayer.getTileSize();

        Bounds initialBounds = Bounds::createWithPositions(tileLayer.getCenterPos(from), tileLayer.getCenterPos(to));

        Vec2 bottomLeft = initialBounds.getBottomLeft() - tileSize / 2;
        Vec2 topRight = initialBounds.getTopRight() + tileSize / 2;

        Bounds bounds = Bounds::createWithPositions(bottomLeft.x, bottomLeft.y, topRight.x, topRight.y);

        if (m_OutlinedTop == nullptr)
        {
            m_OutlinedTop = &tileLayer.add(Rect2D(0, 0, 0.1f, 0.1f, color));
            m_OutlinedRight = &tileLayer.add(Rect2D(1, 0, 0.1f, 0.1f, color));
            m_OutlinedBottom = &tileLayer.add(Rect2D(2, 0, 0.1f, 0.1f, color));
            m_OutlinedLeft = &tileLayer.add(Rect2D(3, 0, 0.1f, 0.1f, color));
        }

        m_OutlinedTop->setSize(Vec2(bounds.getWidth(), tileSize));
        m_OutlinedTop->setPosition2d(Vec2(bounds.getCenter().x, bounds.getTopRight().y - tileSize / 2.0));

        m_OutlinedRight->setSize(Vec2(tileSize, bounds.getHeight() - 2 * tileSize));
        m_OutlinedRight->setPosition2d(Vec2(bounds.getTopRight().x - tileSize / 2.0, bounds.getCenter().y));

        m_OutlinedBottom->setSize(Vec2(bounds.getWidth(), tileSize));
        m_OutlinedBottom->setPosition2d(Vec2(bounds.getCenter().x, bounds.getBottomLeft().y + tileSize / 2.0));

        m_OutlinedLeft->setSize(Vec2(tileSize, bounds.getHeight() - 2 * tileSize));
        m_OutlinedLeft->setPosition2d(Vec2(bounds.getBottomLeft().x + tileSize / 2.0, bounds.getCenter().y));

        m_Bounds = bounds;
    }
} // namespace editing
} // namespace spright
