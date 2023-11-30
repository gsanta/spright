#pragma once

#include "../../engine/graphics/layer/tile_layer.h"
#include "../../engine/structure/tile_canvas.h"
#include "../tool/tools/select_tool/rect_selector.h"

namespace spright
{
namespace editor
{
    using namespace engine;

    void flip_horizontal(TileLayer &layer);

    void flip_horizontal(TileLayer &layer, const Bounds &bounds);

    void flip_horizontal(std::vector<TileLayer> &layers);

    void flip_horizontal(std::vector<TileLayer> &layers, const Bounds &bounds);
} // namespace editor
} // namespace spright
