#pragma once
#include <vector>
#include "../src/engine/graphics/layer/tileLayer.h"
#include "../src/engine/graphics/renderable/bounds.h"
#include "../src/app/document/document.h"
#include "../src/engine/graphics/impl/headless/headless_renderer2d.h"
#include "../src/app/document/document_store.h"
#include "../src/app/document/document_factory.h"
#include "test_event_emitter.h"

using namespace ::spright::engine;
using namespace ::spright::editor;

class TestDocumentFactory {
	static TestEventEmitter eventEmitter;
public:
	static std::vector<TileLayer> createTileLayers(size_t num);
	static TileLayer createTileLayer(size_t index, float tileSize = TileLayer::defaultTileSize, Bounds bounds = Bounds::createWithPositions(-3.0f, 3.0f, -3.0f, 3.0f));
	static Drawing createDrawing(Bounds bounds);
	static DocumentStore createDocumentStore();
	static DocumentFactory createDocumentFactory(Container& windowContainer);
};
