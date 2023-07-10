#include "resize_drawing.h"

namespace spright
{
namespace engine
{
    TileLayer resize_tile_layer(TileLayer &orig, const Bounds &bounds)
    {
        TileLayer newTileLayer(orig.getName(),
                               Group<Rect2D>(orig.m_Group.getRenderer()->clone()),
                               bounds,
                               orig.getTileSize(),
                               orig.getZPos());
        for (Rect2D *rect : orig.getRenderables())
        {
            Vec2 rectCenter = rect->getCenterPosition2d();
            if (newTileLayer.getBounds().contains(rectCenter.x, rectCenter.y))
            {
                newTileLayer.add(*rect);
            }
        }

        return newTileLayer;
    }
} // namespace engine
} // namespace spright

namespace spright
{
namespace editor
{
    Drawing resize_drawing(Drawing &orig, Bounds bounds)
    {
        Drawing newDrawing(bounds);
        for (Frame &frame : orig.getFrames())
        {
            Frame &newFrame = newDrawing.addFrame(Frame(frame.getIndex()));
            for (TileLayer &layer : frame.getLayers())
            {
                TileLayer newLayer = resize_tile_layer(layer, bounds);
                newFrame.addLayer(newLayer);
            }
        }

        for (TileLayer &layer : orig.getBackgroundLayers()) {
            TileLayer newLayer = resize_tile_layer(layer, bounds);
            newDrawing.addBackgroundLayer(newLayer);
        }

        return newDrawing;
    }
} // namespace editor
} // namespace spright
