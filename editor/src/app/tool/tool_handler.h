#pragma once
#include "../../engine/graphics/camera/camera.h"
#include "../../engine/graphics/camera/ortho_projection_info.h"
#include "../../engine/system/window/input_listener.h"
#include "../../engine/system/window/window.h"
#include "../algorithm/flip_horizontal.h"
#include "../algorithm/shear.h"
#include "../document/factory/document_factory.h"
#include "../document/resize_drawing.h"
#include "../editor_config.h"
#include "../service/io/image_export.h"
#include "../service/services.h"
#include "brush_tool.h"
#include "color_picker_tool.h"
#include "eraser_tool/eraser_tool.h"
#include "handler/tool_store.h"
#include "rectangle_tool/rectangle_tool.h"
#include "select_tool/select_tool.h"
#include "tool/document_info.h"
#include "tool/pointer_info.h"
#include "tool/tool.h"
#include "tool/tool_context.h"

#include <algorithm>
#include <iostream>
#include <vector>

namespace spright
{
namespace editor
{
    using namespace std;
    using namespace ::spright::engine;

    class ToolHandler : public InputListener
    {
    public:
        ToolHandler(Window *window, DocumentStore *documentStore);

        ~ToolHandler();

        ToolHandler &operator=(const ToolHandler &toolHandler);

        // TODO: destructor
        virtual void onMouseUp(bool buttons[3]) override;

        virtual void onMouseDown(bool buttons[3]) override;

        virtual void onMouseMove(double x, double y) override;

        virtual void onScroll(double x, double y) override;

        void execute();

        ToolStore &getToolStore();

        inline vector<Tool *> *getActiveTool() const
        {
            return m_ActiveTools;
        }

        Tool *getSelectedTool();

        void setSelectedTool(string name);

        inline void addActiveTool(string name)
        {
            m_ActiveTools->push_back(getToolStore().getTool(name));
        }

        inline void removeActiveTool(string name)
        {
            auto it = find(m_ActiveTools->begin(), m_ActiveTools->end(), getToolStore().getTool(name));

            if (it != m_ActiveTools->end())
            {
                m_ActiveTools->erase(it);
            }
        }

        bool isActiveTool(string name);

    private:
        Window *m_Window;

        vector<Tool *> *m_ActiveTools;

        Tool *m_SelectedTool = nullptr;

        ToolStore m_ToolStore;

        DocumentStore *m_DocumentStore;

        ToolContext m_ToolContext;
    };
} // namespace editor
} // namespace spright
