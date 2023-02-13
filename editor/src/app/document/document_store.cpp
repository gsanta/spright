#include "document_store.h"

namespace spright { namespace editor {

	DocumentStore::DocumentStore() {
		std::cout << "Constructor\n";
	}

	DocumentStore::~DocumentStore() {
		std::cout << "Destructor\n";
	}

	Document* DocumentStore::getActiveDocument() const {
		return m_ActiveDocument;
	}

	void DocumentStore::setActiveDocument(Document* document)
	{
		m_ActiveDocument = document;
	}

	bool DocumentStore::hasActiveDocument() const {
		return m_ActiveDocument != nullptr;
	}
}}