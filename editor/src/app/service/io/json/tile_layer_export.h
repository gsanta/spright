#pragma once
#include "../../../../engine/graphics/layer/tileLayer.h"
#include "../../../document/document.h"
#include "../../../document/factory/document_factory.h"

#include <nlohmann/json.hpp>

namespace spright
{
namespace editor
{
    using namespace ::spright::engine;

    class TileLayerExport
    {
        DocumentFactory *m_DocumentFactory;

    public:
        TileLayerExport(DocumentFactory *documentHandler);
        nlohmann::json exportLayer(const TileLayer &layer);
        void importLayer(Document &document, nlohmann::json json);
    };
} // namespace editor
} // namespace spright
