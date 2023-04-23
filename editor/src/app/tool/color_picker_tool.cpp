#include "color_picker_tool.h"

namespace spright
{
namespace editor
{

    ColorPickerTool::ColorPickerTool(ToolHandler *toolHandler, EventEmitter *eventEmitter)
        : m_ToolHandler(toolHandler), m_EventEmitter(eventEmitter), Tool("color_picker")
    {
    }

    void ColorPickerTool::pointerDown(const ToolContext &context)
    {

        if (!context.doc.hasActiveDrawing())
        {
            return;
        }

        TileLayer &tileLayer = context.doc.activeDrawing->getActiveLayer();
        Vec2Int tilePos = tileLayer.getTilePos(context.pointer.curr);
        int tileIndex = tileLayer.getTileIndex(tilePos.x, tilePos.y);
        Rect2D *tile = tileLayer.getAtTileIndex(tileIndex);

        if (tile != nullptr)
        {
            unsigned int color = tile->getColor();

            if (color != m_PickedColor)
            {
                m_PickedColor = color;

                for (Colorable *colorable : m_ToolHandler->getColorableTools())
                {
                    colorable->setColor(m_PickedColor);
                }
                emitColorChange();
            }
        }
    }

    unsigned int ColorPickerTool::getPickedColor() const
    {
        return m_PickedColor;
    }

    std::string ColorPickerTool::getData()
    {
        nlohmann::json json = {};

        json["color"] = m_PickedColor;

        return json.dump();
    }

    void ColorPickerTool::emitColorChange() const
    {
        nlohmann::json json = {
            {"tool", getName()},
        };

        m_EventEmitter->emitChange("tool_data_changed", json);
    }
} // namespace editor
} // namespace spright
