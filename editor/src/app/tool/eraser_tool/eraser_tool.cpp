#include "eraser_tool.h"

namespace spright
{
namespace editor
{
    EraserTool::EraserTool(DocumentStore *documentStore, int eraserSize)
        : m_documentStore(documentStore), m_Size(eraserSize), Tool("erase")
    {
        m_EraserStroke = EraserStroke(m_Size);
    }

    void EraserTool::pointerDown(PointerInfo &pointerInfo, Drawing *activeDrawing)
    {
        if (activeDrawing == nullptr)
        {
            return;
        }

        TileLayer &activeLayer = activeDrawing->getActiveLayer();
        m_Eraser.erase(activeLayer, activeLayer.getTilePos(pointerInfo.curr), m_Size);
    }

    void EraserTool::pointerMove(PointerInfo &pointerInfo, Drawing *activeDrawing)
    {
        if (activeDrawing == nullptr)
        {
            return;
        }

        TileLayer &activeLayer = activeDrawing->getActiveLayer();
        TileLayer &drawLayer = activeDrawing->getForegroundLayer();

        m_EraserStroke.draw(activeLayer, drawLayer, pointerInfo.curr);

        if (pointerInfo.isDown)
        {
            m_Eraser.erase(activeLayer, activeLayer.getTilePos(pointerInfo.curr), m_Size);
        }
    }

    void EraserTool::deactivate()
    {
        m_EraserStroke.clear();
    }
    void EraserTool::setOptions(std::string json)
    {
        nlohmann::json parsedJson = nlohmann::json::parse(json);

        m_Size = parsedJson["size"];
    }

    std::string EraserTool::getOptions()
    {
        nlohmann::json json;

        json["size"] = m_Size;

        return json.dump();
    }
} // namespace editor
} // namespace spright
