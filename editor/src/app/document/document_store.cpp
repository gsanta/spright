#include "document_store.h"

namespace spright { namespace editor {

	DocumentStore::DocumentStore() {
	}

	Document& DocumentStore::getActiveDocument() {
		return m_Documents[m_ActiveDocument];
	}

	void DocumentStore::addDocument(Document document) {
		m_Documents.push_back(document);
	}

	void DocumentStore::setActiveDocument(size_t index)
	{
		m_ActiveDocument = index;
	}

	bool DocumentStore::hasActiveDocument() const {
		return m_Documents.size() > m_ActiveDocument;
	}
}}