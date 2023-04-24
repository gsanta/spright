#include "../src/app/algorithm/flip_drawing.h"
#include "../src/app/core/colors.h"
#include "../src/engine/graphics/layer/tileLayer.h"
#include "../test_helpers/document_store_builder.h"
#include "../test_helpers/drawing_builder.h"
#include "../test_helpers/tile_layer_builder.h"

#include <catch2/catch_test_macros.hpp>

using namespace spright::editor;
using namespace spright::engine;

TEST_CASE("flipDrawing", "[flip-drawing]")
{
    SECTION("can flip a drawing")
    {
        DocumentStore documentStore =
            DocumentStoreBuilder()
                .withDrawing(DrawingBuilder().withTileLayer(TileLayerBuilder()
                                                                .withTile(Vec2Int(0, 1), COLOR_RED)
                                                                .withTile(Vec2Int(1, 1), COLOR_RED)
                                                                .withTile(Vec2Int(0, 2), COLOR_RED)
                                                                .withTile(Vec2Int(11, 1), COLOR_BLUE)
                                                                .withTile(Vec2Int(10, 1), COLOR_BLUE)
                                                                .withTile(Vec2Int(11, 2), COLOR_BLUE)))
                .build();

        TileLayer &layer = documentStore.getActiveDocument().getActiveDrawing().getActiveLayer();

        int tileWidth = layer.getTileBounds().getWidth();
        int tileHeight = layer.getTileBounds().getHeight();

        Drawing& drawing = documentStore.getActiveDocument().getActiveDrawing();
        flip_drawing(drawing, drawing.getActiveFrame().getIndex());

        REQUIRE(layer.getAtTilePos(tileWidth - 1, 1)->getColor() == COLOR_RED);
        REQUIRE(layer.getTileIndex(tileWidth - 1, 1) == 23);
        REQUIRE(layer.getAtTilePos(tileWidth - 2, 1)->getColor() == COLOR_RED);
        REQUIRE(layer.getTileIndex(tileWidth - 2, 1) == 22);
        REQUIRE(layer.getAtTilePos(tileWidth - 1, 2)->getColor() == COLOR_RED);
        REQUIRE(layer.getTileIndex(tileWidth - 1, 2) == 35);
        REQUIRE(layer.getAtTilePos(0, 1)->getColor() == COLOR_BLUE);
        REQUIRE(layer.getTileIndex(0, 1) == 12);
        REQUIRE(layer.getAtTilePos(1, 1)->getColor() == COLOR_BLUE);
        REQUIRE(layer.getTileIndex(1, 1) == 13);
        REQUIRE(layer.getAtTilePos(0, 2)->getColor() == COLOR_BLUE);
        REQUIRE(layer.getTileIndex(0, 2) == 24);
    }
}
