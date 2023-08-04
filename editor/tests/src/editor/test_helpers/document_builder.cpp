#include "document_builder.h"

DocumentBuilder &DocumentBuilder::withEmptyDocument() {
    m_IsEmptyDocument = true;
    return *this;
}


Document DocumentBuilder::build()
{
    Camera camera(m_WindowSize, m_WindowSize, m_DocumentBounds, -1.0f, 1.0f);

    Document document(m_DocumentBounds,
                      camera,
                      DrawingBuilder().withBounds(m_DocumentBounds).build(),
                      std::make_shared<DocumentHistory>());

    if (!m_IsEmptyDocument) {
        document.addDrawing(DrawingBuilder().build());
    }

    return document;
}
