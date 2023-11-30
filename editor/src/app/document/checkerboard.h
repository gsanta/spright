#pragma once

#include "../../engine/graphics/mesh/meshes/rect2d.h"
#include "../../engine/scene/containers/tile_layer.h"

namespace spright
{
namespace editor
{

    using namespace engine;

    class Checkerboard
    {

    public:
        void create(TileLayer &layer) const;
    };
} // namespace editor
} // namespace spright
