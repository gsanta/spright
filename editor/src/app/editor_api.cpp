#include "editor_api.h"

extern class Editor *editor;

#ifdef SPARKY_EMSCRIPTEN

void setLayerIndex(size_t oldIndex, size_t newIndex)
{
    editor->getActiveDocument().getActiveDrawing().getActiveFrame().changeLayerOrder(oldIndex, newIndex);
}

void removeLayer(size_t layerIndex)
{
    editor->getActiveDocument().getActiveDrawing().getActiveFrame().removeLayer(layerIndex);
}

std::string exportDocument()
{
    return editor->getJsonIO()->exportDocument(editor->getDocumentStore()->getActiveDocument());
}

void importDocument(std::string json)
{
    return editor->getJsonIO()->importDocument(json);
}

std::string getToolData(std::string tool)
{
    return editor->getToolHandler()->getTool(tool)->getData();
}

std::vector<std::string> getFrames()
{
    const std::vector<Frame> &frames = editor->getActiveDocument().getActiveDrawing().getFrames();

    std::vector<std::string> target;

    for (const Frame &frame : frames)
    {
        target.push_back(frame.getJson().dump());
    }

    return target;
}

void addFrame()
{
    editor->getDocumentFactory()->createFrame(editor->getDocumentStore()->getActiveDocument());
}

void removeFrame(size_t index)
{
    editor->getActiveDocument().getActiveDrawing().removeFrame(index);
}

void setActiveFrame(size_t index)
{
    editor->getActiveDocument().getActiveDrawing().setActiveFrame(index);
}

std::string getActiveFrame()
{
    return editor->getActiveDocument().getActiveDrawing().getActiveFrame().getJson().dump();
}

void activateFramePlayer()
{
    // editor->getActiveDocument().getFramePlayer().setIsActive(true);
}

void deActivateFramePlayer()
{
    // editor->getActiveDocument().getFramePlayer().setIsActive(false);
}

void api_flip_horizontal()
{
    Drawing &drawing = editor->getActiveDocument().getActiveDrawing();
    if (drawing.getState().getBounds().isNull())
    {
        flip_horizontal(editor->getActiveDocument().getActiveFrame().getLayers());
    }
    else
    {
        flip_horizontal(editor->getActiveDocument().getActiveFrame().getLayers(), drawing.getState().getBounds());
    }
}

void set_circle_tool_filled(bool isFilled)
{
    CircleTool *circleTool = static_cast<CircleTool *>(editor->getToolHandler()->getTool("circle"));
    circleTool->setFilled(isFilled);
}

bool is_circle_tool_filled()
{
    CircleTool *circleTool = static_cast<CircleTool *>(editor->getToolHandler()->getTool("circle"));
    return circleTool->isFilled();
}

bool is_rectangle_tool_filled()
{
    RectangleTool *rectangleTool = static_cast<RectangleTool *>(editor->getToolHandler()->getTool("rectangle"));
    return rectangleTool->isFilled();
}

void set_rectangle_tool_filled(bool isFilled)
{
    RectangleTool *rectangleTool = static_cast<RectangleTool *>(editor->getToolHandler()->getTool("rectangle"));
    rectangleTool->setFilled(isFilled);
}

EMSCRIPTEN_BINDINGS(spright)
{
    emscripten::function("getFrames", &getFrames);
    emscripten::function("addFrame", &addFrame);
    emscripten::function("removeFrame", &removeFrame);
    emscripten::function("setActiveFrame", &setActiveFrame);
    emscripten::function("getActiveFrame", &getActiveFrame);
    emscripten::function("setLayerIndex", &setLayerIndex);
    emscripten::function("removeLayer", &removeLayer);
    emscripten::function("exportDocument", &exportDocument);
    emscripten::function("importDocument", &importDocument);
    emscripten::function("getToolData", &getToolData);
    emscripten::function("activateFramePlayer", &activateFramePlayer);
    emscripten::function("deActivateFramePlayer", &deActivateFramePlayer);
    emscripten::function("flipHorizontal", &api_flip_horizontal);
    emscripten::function("setCircleToolFilled", &set_circle_tool_filled);
    emscripten::function("isCircleToolFilled", &is_circle_tool_filled);
    emscripten::function("setRectangleToolFilled", &set_rectangle_tool_filled);
    emscripten::function("isRectangleToolFilled", &is_rectangle_tool_filled);
}

#endif
