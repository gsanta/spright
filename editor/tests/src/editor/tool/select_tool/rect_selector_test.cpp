#include "../../test_helpers/document_store_builder.h"
#include "../../test_helpers/drawing_builder.h"
#include "../../test_helpers/tile_layer_builder.h"
#include "../src/app/tool/select_tool/rect_selector.h"
#include "../src/engine/graphics/layer/tileLayer.h"

#include <catch2/catch_approx.hpp>
#include <catch2/catch_test_macros.hpp>
#include <vector>

using namespace ::spright::editor;
using namespace ::spright::engine;
using namespace ::spright::maths;

TEST_CASE("RectSelector", "[rect-selector]")
{
    DocumentStore documentStore = DocumentStoreBuilder()
                                      .withDrawing(DrawingBuilder().withTileLayer(TileLayerBuilder()
                                                                                      .withTile(Vec2Int(0, 1))
                                                                                      .withTile(Vec2Int(1, 1))
                                                                                      .withTile(Vec2Int(0, 2))
                                                                                      .withTile(Vec2Int(1, 2))
                                                                                      .withTile(Vec2Int(0, 4))
                                                                                      .withTile(Vec2Int(4, 0))
                                                                                      .withTile(Vec2Int(4, 1))))
                                      .build();

    TileLayer &layer = documentStore.getActiveDocument().getActiveDrawing().getActiveLayer();

    RectSelector rectSelector(&layer);

    SECTION("can select sprites")
    {
        const Vec2 bottomLeft = layer.getBounds().getBottomLeft();
        Vec2 topRight = bottomLeft + Vec2(2, 2);
        rectSelector.setSelection(bottomLeft, topRight);

        const vector<Rect2D *> selection = rectSelector.getSelection();

        REQUIRE(selection.size() == 4);
        REQUIRE(layer.getTilePos(selection[0]->getPosition2d()) == Vec2Int(0, 1));
        REQUIRE(layer.getTilePos(selection[1]->getPosition2d()) == Vec2Int(1, 1));
        REQUIRE(layer.getTilePos(selection[2]->getPosition2d()) == Vec2Int(0, 2));
        REQUIRE(layer.getTilePos(selection[3]->getPosition2d()) == Vec2Int(1, 2));
    }

    SECTION("can move the selection")
    {
        const Vec2 bottomLeft = layer.getBounds().getBottomLeft();
        Vec2 topRight = bottomLeft + Vec2(2, 2);
        rectSelector.setSelection(bottomLeft, topRight);
        rectSelector.moveSelectionWith(Vec2(layer.getTileSize() * 2, layer.getTileSize() * 2));

        const vector<Rect2D *> selection = rectSelector.getSelection();

        REQUIRE(selection.size() == 4);
        REQUIRE(layer.getTilePos(selection[0]->getPosition2d()) == Vec2Int(2, 3));
        REQUIRE(layer.getTilePos(selection[1]->getPosition2d()) == Vec2Int(3, 3));
        REQUIRE(layer.getTilePos(selection[2]->getPosition2d()) == Vec2Int(2, 4));
        REQUIRE(layer.getTilePos(selection[3]->getPosition2d()) == Vec2Int(3, 4));
    }

    SECTION("can make a point selection")
    {
        Vec2 pos = layer.getRenderables()[0]->getCenterPosition2d();

        rectSelector.setSelection(pos, pos + Vec2(0.11, 0.11));

        const vector<Rect2D *> selection = rectSelector.getSelection();

        REQUIRE(selection.size() == 1);
    }
}
