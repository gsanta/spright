#include "tileLayer.h"

namespace engine { namespace graphics {

	TileLayer::TileLayer(std::string name, std::string id, Shader* shader, Renderer2D* renderer, Camera* camera, Dimensions dimensions, float tileSize)
		: Layer(name, id, renderer, shader, camera, dimensions), m_TileSize(tileSize) {
	
		int width = (dimensions.right - dimensions.left) / m_TileSize;
		int height = (dimensions.top - dimensions.bottom) / m_TileSize;
		int left = (dimensions.left / m_TileSize) - 1;
		int bottom = (dimensions.bottom / m_TileSize) - 1;

		m_TileBounds = BoundsInt(left, left + width, bottom, bottom + height);

		m_IndexSize = width * height;
		m_TileIndexes = new Renderable2D*[m_IndexSize]();
	}

	TileLayer::~TileLayer() {
		delete[] m_TileIndexes;
	}

	Vec2 TileLayer::getBottomLeftPos(Vec2 pointer)
	{
		maths::Vec2Int tilePos = getTilePos(pointer);

		float tileSize = m_TileSize;

		float x = static_cast<float>(tilePos.x) * tileSize + m_Dimensions.left;
		float y = static_cast<float>(tilePos.y) * tileSize + m_Dimensions.bottom;

		return Vec2(x, y);
	}

	Vec2 TileLayer::getBottomLeftPos(int tileIndex)
	{
		int y = tileIndex / m_TileBounds.getWidth();
		int x = tileIndex % m_TileBounds.getWidth();

		return Vec2(x * m_TileSize + m_Dimensions.left, y * m_TileSize + m_Dimensions.bottom);
	}

	Vec2 TileLayer::getCenterPos(int tileIndex) {
		Vec2 bottomLeftPos = getBottomLeftPos(tileIndex);
		bottomLeftPos.x += m_TileSize / 2.0f;
		bottomLeftPos.y += m_TileSize / 2.0f;

		return bottomLeftPos;
	}

	// TODO: check if it works for both even and odd number of tiles
	maths::Vec2Int TileLayer::getTilePos(Vec2 pos) {
		Vec2 adjustedPos(pos.x - m_Camera->getDimensions().left, pos.y - m_Camera->getDimensions().bottom);
		float tileSize = m_TileSize;
		int tileX = (int)(adjustedPos.x / tileSize);
		int tileY = (int)(adjustedPos.y / tileSize);

		return maths::Vec2Int(tileX, tileY);
	}

	maths::Vec2Int TileLayer::getTilePos(int tileIndex) {
		return maths::Vec2Int(getColumn(tileIndex), getRow(tileIndex));
	}

	unsigned int TileLayer::getColumn(int tileIndex) {
		return tileIndex % m_TileBounds.getWidth();
	}
	
	unsigned int TileLayer::getRow(int tileIndex) {
		return tileIndex / m_TileBounds.getWidth();
	}

	Vec2 TileLayer::getWorldPos(int x, int y)
	{
		float tileSize = m_TileSize;

		float worldX = x * tileSize + tileSize / 2 + m_Dimensions.left;
		float worldY = y * tileSize + tileSize / 2 + m_Dimensions.bottom;

		return Vec2(worldX, worldY);
	}

	nlohmann::json TileLayer::getJson()
	{
		nlohmann::json json;

		for (Renderable2D* renderable : m_Renderables) {
			json["tiles"] += renderable->getJson();
		}

		return json;
	}

	void TileLayer::setJson(std::string json)
	{
		nlohmann::json parsedJson = nlohmann::json::parse(json);

		this->clear();

		for (nlohmann::json j : parsedJson)
		{
			float posX = j["posX"];
			float posY = j["posY"];
			float posZ = j["posZ"];
			float sizeX = j["sizeX"];
			float sizeY = j["sizeY"];

			engine::graphics::Rect2D* sprite = new engine::graphics::Rect2D(posX, posY, sizeX, sizeY, 0xff0000ff);
			add(sprite);
		}
	}

	void TileLayer::add(Rect2D* sprite)
	{
		Layer::add(sprite);

		Vec2 pos = sprite->getBounds()->getCenter();
		maths::Vec2Int tilePos = getTilePos(pos);

		int index = m_TileBounds.getWidth() * tilePos.y + tilePos.x;
		if (m_IndexSize > index) {
			m_TileIndexes[index] = sprite;
			sprite->setTileIndex(index);
		}
	}

	void TileLayer::updateTileIndex(int oldIndex, int newIndex) {
		Rect2D* sprite = dynamic_cast<Rect2D*>(getAtTileIndex(oldIndex));
		sprite->setTileIndex(newIndex);
		m_TileIndexes[oldIndex] = nullptr;
		m_TileIndexes[newIndex] = sprite;
	}

	int TileLayer::getTileIndex(int tileX, int tileY)
	{
		return m_TileBounds.getWidth() * tileY + tileX;
	}

	int TileLayer::getTileIndex(Vec2 worldPos)
	{
		maths::Vec2Int tilePos = getTilePos(worldPos);

		return getTileIndex(tilePos.x, tilePos.y);
	}

	const BoundsInt& TileLayer::getTileBounds() const
	{
		return m_TileBounds;
	}

	Renderable2D* TileLayer::getAtTileIndex(int tilePos)
	{
		for (int i = 0; i < m_IndexSize; i++) {
			if (m_TileIndexes[i] != nullptr) {
				int a = 1;
			}
		}
		return m_TileIndexes[tilePos];
	}

	int TileLayer::getIndexSize() const {
		return m_IndexSize;
	}

}}