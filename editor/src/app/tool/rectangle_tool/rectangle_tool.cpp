#include "rectangle_tool.h"

namespace spright
{
namespace editor
{

    RectangleTool::RectangleTool() : Tool("rectangle")
    {
    }

    void RectangleTool::pointerDown(const ToolContext &context)
    {
        if (!context.doc.hasActiveDrawing())
        {
            return;
        }
    }

    void RectangleTool::pointerUp(const ToolContext &context)
    {
        if (!context.doc.hasActiveDrawing())
        {
            return;
        }

        TileLayer &activeLayer = context.doc.activeDrawing->getActiveLayer();
        int color = context.editorState->color;

        if (m_IsFilled)
        {
            draw_filled_rect(activeLayer, m_TempRectDrawer.getBounds(), color);
        }
        else
        {
            draw_outlined_rect(activeLayer, m_TempRectDrawer.getBounds(), color);
        }

        context.doc.activeDrawing->getForegroundLayer().clear();
        m_TempRectDrawer.reset();
    }

    void RectangleTool::pointerMove(const ToolContext &context)
    {
        if (!context.pointer.isDown || !context.doc.hasActiveDrawing())
        {
            return;
        }

        TileLayer &tileLayer = context.doc.activeDrawing->getForegroundLayer();

        if (m_IsFilled)
        {
            m_TempRectDrawer.drawFilled(tileLayer,
                                        context.pointer.down,
                                        context.pointer.curr,
                                        context.editorState->color);
        }
        else
        {
            m_TempRectDrawer.drawOutlined(tileLayer,
                                          context.pointer.down,
                                          context.pointer.curr,
                                          context.editorState->color);
        }
    }

    void RectangleTool::setFilled(bool isFilled)
    {
        m_IsFilled = isFilled;
    }

    bool RectangleTool::isFilled()
    {
        return m_IsFilled;
    }
} // namespace editor
} // namespace spright