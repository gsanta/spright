#include "content_builder.h"


ContentBuilder::ContentBuilder(Document &document, ToolContext &context) : m_Document(document), m_Context(context)
{
}

ContentBuilder &ContentBuilder::buildRect(const BoundsInt &bounds)
{
    TileLayer &activeLayer = m_Context.doc.activeDrawing->getActiveLayer();
    Vec2 start = activeLayer.getCenterPos(bounds.getBottomLeft());

    m_Context.pointer.curr = m_Context.pointer.down = m_Context.pointer.prev = start;
    m_Context.pointer.isDown = true;

    RectangleTool rectTool;
    rectTool.setFilled(true);

    rectTool.execPointerDown(m_Context);

    m_Context.pointer.curr = activeLayer.getCenterPos(bounds.getTopRight());

    rectTool.execPointerMove(m_Context);
    rectTool.execPointerUp(m_Context);

    return *this;
}

ContentBuilder &ContentBuilder::buildTile(const Vec2Int &pos)
{
    TileLayer &activeLayer = m_Context.doc.activeDrawing->getActiveLayer();

    BrushTool brushTool;

    m_Context.pointer.curr = m_Context.pointer.down = m_Context.pointer.prev = activeLayer.getCenterPos(pos);

    brushTool.execPointerDown(m_Context);
    brushTool.execPointerUp(m_Context);

    return *this;
}

ContentBuilder &ContentBuilder::setPrevCurrDown(const Vec2Int &pos)
{
    m_Context.pointer.curr = m_Context.pointer.prev = m_Context.pointer.down =
        m_Context.doc.activeDrawing->getActiveLayer().getCenterPos(pos);

    m_Context.pointer.isDown = true;

    return *this;
}

ContentBuilder &ContentBuilder::setCurr(const Vec2Int &pos)
{
    m_Context.pointer.curr = m_Context.doc.activeDrawing->getActiveLayer().getCenterPos(pos);

    return *this;
}

ContentBuilder &ContentBuilder::selectTiles(const std::vector<Rect2D *> &tiles)
{
    TileLayer &activeLayer = m_Context.doc.activeDrawing->getActiveLayer();

    vector<int> tileIndexes;
    for (Rect2D *rect : activeLayer.getTiles())
    {
        tileIndexes.push_back(activeLayer.getTileIndex(rect->getCenterPosition2d()));
    }

    m_Context.tools->getSelectTool().setSelection(tileIndexes, *m_Context.doc.activeDrawing);

    return *this;
}

ContentBuilder &ContentBuilder::selectRect(const BoundsInt &bounds)
{
    TileLayer &activeLayer = m_Context.doc.activeDrawing->getActiveLayer();
    Vec2 start = activeLayer.getCenterPos(bounds.getBottomLeft());

    m_Context.pointer.curr = m_Context.pointer.down = m_Context.pointer.prev = start;
    m_Context.pointer.isDown = true;

    SelectTool &selectTool = m_Context.tools->getSelectTool();

    selectTool.execPointerDown(m_Context);

    m_Context.pointer.curr = activeLayer.getCenterPos(bounds.getTopRight());

    selectTool.execPointerMove(m_Context);
    selectTool.execPointerUp(m_Context);

    return *this;
}
