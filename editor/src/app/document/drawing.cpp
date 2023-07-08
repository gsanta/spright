#include "drawing.h"

namespace spright
{
namespace editor
{

    Drawing resize_drawing(Drawing &orig, Bounds bounds);

    Drawing::Drawing(Bounds bounds) : Container(bounds)
    {
    }

    std::vector<Frame> &Drawing::getFrames()
    {
        return m_Frames;
    }

    Frame &Drawing::getActiveFrame()
    {
        return m_Frames[m_ActiveFrameIndex];
    }

    void Drawing::setActiveFrame(size_t index)
    {
        if (index >= m_Frames.size())
        {
            throw std::invalid_argument("No frame at index " + std::to_string(index));
        }

        m_ActiveFrameIndex = index;
    }

    Frame &Drawing::addFrame(const Frame &frame)
    {
        int index = m_Frames.size();
        m_Frames.push_back(frame);
        m_Frames.back().setIndex(index);

        return m_Frames.back();
    }

    void Drawing::removeFrame(size_t index)
    {
        if (m_Frames.size() <= 1)
        {
            throw std::invalid_argument("The last frame can not be removed");
        }

        m_Frames.erase(m_Frames.begin() + index);

        for (int i = 0; i < m_Frames.size(); i++)
        {
            m_Frames[i].setIndex(i);
        }

        m_ActiveFrameIndex = index < m_Frames.size() ? index : 0;
    }

    Frame &Drawing::getFrame(size_t frameIndex)
    {
        auto it =
            find_if(m_Frames.begin(), m_Frames.end(), [=](Frame &frame) { return frame.getIndex() == frameIndex; });

        if (it != m_Frames.end())
        {
            return *it;
        }

        throw std::invalid_argument("Frame with index " + std::to_string(frameIndex) + " not found");
    }

    TileLayer &Drawing::addLayer(const TileLayer &tileLayer)
    {
        if (getBounds() != tileLayer.getBounds())
        {
            throw std::invalid_argument("Can not add a TileLayer to a Drawing with different bounds");
        }

        Frame &frame = getActiveFrame();
        // check bounds
        return frame.addLayer(tileLayer);
    }

    TileLayer &Drawing::getActiveLayer()
    {
        return getActiveFrame().getLayers()[m_ActiveLayerIndex];
    }

    void Drawing::setActiveLayer(size_t index)
    {
        m_ActiveLayerIndex = index;
    }

    TileLayer &Drawing::getForegroundLayer()
    {
        return m_ForegroundLayers[0];
    }

    TileLayer &Drawing::getBackgroundLayer()
    {
        return m_BackgroundLayers[0];
    }

    void Drawing::addBackgroundLayer(const TileLayer &tileLayer)
    {
        m_BackgroundLayers.push_back(tileLayer);
    }

    void Drawing::addForegroundLayer(const TileLayer &tileLayer)
    {
        m_ForegroundLayers.push_back(tileLayer);
    }

    std::string Drawing::getJson()
    {
        nlohmann::json json = getActiveFrame().getLayer(m_ActiveLayerIndex).getJson();

        return json.dump();
    }

    void Drawing::render(const Camera &camera)
    {
        for (TileLayer &layer : m_BackgroundLayers)
        {
            layer.render(camera);
        }

        for (TileLayer &layer : getActiveFrame().getLayers())
        {
            layer.render(camera);
        }

        for (TileLayer &layer : m_ForegroundLayers)
        {
            layer.render(camera);
        }
    }

    DrawingState &Drawing::getState()
    {
        return m_DrawingState;
    }

    void Drawing::resize(Bounds newBounds)
    {
        *this = resize_drawing(*this, newBounds);
    }

} // namespace editor
} // namespace spright
