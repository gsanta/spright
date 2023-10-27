#include "tool_handler.h"

int x_tmp;
int y_tmp;

namespace spright
{
namespace editor
{
    ToolHandler::ToolHandler(DocumentStore *documentStore) : m_DocumentStore(documentStore)
    {
        m_ActiveTools = new vector<Tool *>();
        m_ToolStore = std::make_shared<ToolStore>();
        m_ToolContext.tools = m_ToolStore;
    }

    ToolHandler::~ToolHandler()
    {
    }

    ToolHandler &ToolHandler::operator=(const ToolHandler &toolHandler)
    {
        m_ActiveTools = toolHandler.m_ActiveTools;
        m_SelectedTool = toolHandler.m_SelectedTool;

        return *this;
    }

    void ToolHandler::onMouseUp(bool buttons[3])
    {
        Drawing *activeDrawing = &m_DocumentStore->getActiveDocument().getDrawing(0);

        m_ToolContext.doc.document = &m_DocumentStore->getActiveDocument();

        for (Tool *tool : *m_ActiveTools)
        {
            m_ToolContext.pointer.buttons[0] = buttons[0];
            m_ToolContext.pointer.buttons[1] = buttons[1];
            m_ToolContext.pointer.buttons[2] = buttons[2];

            tool->execPointerUp(m_ToolContext);
            m_ToolContext.pointer.isDown = false;
        }
    }

    void ToolHandler::onMouseDown(bool buttons[3])
    {
        Vec2 pos = m_DocumentStore->getActiveDocument().getCamera().screenToWorldPos(x_tmp, y_tmp);

        m_ToolContext.doc.document = &m_DocumentStore->getActiveDocument();

        m_ToolContext.pointer.isDown = true;
        m_ToolContext.pointer.down = m_ToolContext.pointer.curr;
        m_ToolContext.pointer.buttons[0] = buttons[0];
        m_ToolContext.pointer.buttons[1] = buttons[1];
        m_ToolContext.pointer.buttons[2] = buttons[2];

        Drawing *activeDrawing = &m_DocumentStore->getActiveDocument().getDrawing(0);
        for (Tool *tool : *m_ActiveTools)
        {
            tool->execPointerDown(m_ToolContext);
        }
    }

    void ToolHandler::onMouseMove(double x, double y)
    {
        Vec2 pos = m_DocumentStore->getActiveDocument().getCamera().screenToWorldPos(x, y);

        Document &document = m_DocumentStore->getActiveDocument();
        m_ToolContext.doc.document = &m_DocumentStore->getActiveDocument();

        if (!m_ToolContext.pointer.isDown) {
            document.setActiveDrawing(-1);

            for (size_t i = 0; i < document.getDrawings().size(); i++) {
                if (document.getDrawings()[i].getBounds().contains(pos.x, pos.y)) {
                    document.setActiveDrawing(i);
                    break;
                }
            }
        }

        Drawing *activeDrawing = m_DocumentStore->getActiveDocument().getActiveDrawing();

        m_ToolContext.doc.prevDrawing = activeDrawing;
        m_ToolContext.doc.activeDrawing = activeDrawing;

        x_tmp = x;
        y_tmp = y;
        m_ToolContext.pointer.prev = m_ToolContext.pointer.curr;
        m_ToolContext.pointer.curr = pos;

        for (Tool *tool : *m_ActiveTools)
        {
            tool->execPointerMove(m_ToolContext);
        }
    }

    void ToolHandler::onScroll(double x, double y)
    {
        m_ToolContext.pointer.scroll = Vec2(x, y);

        for (Tool *tool : *m_ActiveTools)
        {
            tool->scroll(m_ToolContext);
        }
    }

    ToolStore &ToolHandler::getToolStore()
    {
        return *m_ToolStore;
    }


    void ToolHandler::executeTool(const string &toolName)
    {
        getToolStore().getTool(toolName)->execute(m_ToolContext);
    }

    Tool *ToolHandler::getSelectedTool()
    {
        return m_SelectedTool;
    }

    void ToolHandler::setSelectedTool(string name)
    {
        if (m_SelectedTool != nullptr)
        {
            removeActiveTool(m_SelectedTool->getName());

            m_SelectedTool->execDeactivate(m_ToolContext);
        }

        if (!isActiveTool(name))
        {
            addActiveTool(name);
        }

        m_SelectedTool = getToolStore().getTool(name);
        m_SelectedTool->activate();
    }

    void ToolHandler::addActiveTool(string name)
    {
        m_ActiveTools->push_back(getToolStore().getTool(name));
    }

    void ToolHandler::removeActiveTool(string name)
    {
        auto it = find(m_ActiveTools->begin(), m_ActiveTools->end(), getToolStore().getTool(name));

        if (it != m_ActiveTools->end())
        {
            m_ActiveTools->erase(it);
        }
    }

    bool ToolHandler::isActiveTool(string name)
    {
        Tool *tool = getToolStore().getTool(name);

        auto it = find((*m_ActiveTools).begin(), (*m_ActiveTools).end(), tool);

        return it != (*m_ActiveTools).end();
    }
} // namespace editor
} // namespace spright
