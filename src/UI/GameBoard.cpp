#include "GameBoard.h"
#include "raymath.h"

GameBoard::GameBoard()
	: m_BoxSize({64, 64})
	, m_SymbolSizePercent(1.0f)
	, m_Origin({0.5f, 0.5f})
	, m_Position({0.0f, 0.0f})
	, m_Bounds({0, 0, 0, 0})
	, m_Padding({5, 5})
	, m_Rows(1)
	, m_Cols(1)
	, m_SymbolTexture()
{
	Image image = LoadImage("assets/symbols.png");
	m_SymbolTexture = LoadTextureFromImage(image);
	UnloadImage(image);
}

void GameBoard::SetBlockSize(float size)
{
	m_BoxSize.x = size;
	m_BoxSize.y = size;
}

void GameBoard::SetSymbolSizePercent(float sizePercent)
{
	m_SymbolSizePercent = Clamp(sizePercent, 0.0f, 1.0f);
}

void GameBoard::SetPadding(float padding)
{
	m_Padding.x = padding;
	m_Padding.y = padding;
}

void GameBoard::SetOrigin(Vector2 origin)
{
	origin.x = Clamp(origin.x, 0.0f, 1.0f);
	origin.y = Clamp(origin.y, 0.0f, 1.0f);
	m_Origin = origin;
}

void GameBoard::SetPosition(Vector2 position)
{
	m_Position = position;
}

void GameBoard::Init(unsigned int rows, unsigned int cols)
{
	m_Rows = rows;
	m_Cols = cols;
	CalculateBounds(rows, cols);

	const size_t totalCount = (size_t)rows * (size_t)cols;
	FillBoxes();
}

int GameBoard::Update(const int* data, bool checkForInput /*= true*/)
{
	int selectedTile = -1;
	int hovered = -1;
	Vector2 mousePoint = GetMousePosition();

	for(int y = 0; y < m_Rows; ++y)
	{
		for(int x = 0; x < m_Cols; ++x)
		{
			if(selectedTile != -1)
			{
				continue;
			}

			const int linearIndex = m_Cols * y + x;
			if(data != nullptr)
			{
				m_SymbolStates[linearIndex] = data[linearIndex];
				if(data[linearIndex] > 0)
				{
					m_BoxStates[linearIndex] = 2;
				}
			}

			if(checkForInput)
			{
				if(m_BoxStates[linearIndex] != 2)
				{
					if(CheckCollisionPointRec(mousePoint, m_Boxes[linearIndex]) && hovered == -1)
					{
						if(IsMouseButtonDown(MOUSE_LEFT_BUTTON))
						{
							m_BoxStates[linearIndex] = 2;
							selectedTile = linearIndex;
						}
						else
						{
							m_BoxStates[linearIndex] = 1;
							hovered = linearIndex;
						}
					}
					else
					{
						m_BoxStates[linearIndex] = 0;
						if(hovered > -1)
						{
							hovered = -1;
						}
					}
				}
			}
		}
	}

	return selectedTile;
}

void GameBoard::Render()
{
	for(int y = 0; y < m_Rows; ++y)
	{
		for(int x = 0; x < m_Cols; ++x)
		{
			const int linearIndex = m_Cols * y + x;
			Color boxColor = LIGHTGRAY;

			switch(m_BoxStates[linearIndex])
			{
			case 1: {
				boxColor = DARKGRAY;
				break;
			}
			default:
				break;
			}

			DrawRectangleRec(m_Boxes[linearIndex], boxColor);
			if(m_SymbolStates[linearIndex] > 0)
			{

				const float offsetPercent = 0.5f * (1.0f - m_SymbolSizePercent);
				Vector2 offset;
				offset.x = m_Boxes[linearIndex].x + offsetPercent * m_BoxSize.x;
				offset.y = m_Boxes[linearIndex].y + offsetPercent * m_BoxSize.y;

				Rectangle frameRect = {(m_SymbolStates[linearIndex] - 1) * 0.5f *
										   m_SymbolTexture.width,
									   0,
									   0.5f * m_SymbolTexture.width,
									   (float)m_SymbolTexture.height};

				Rectangle dstRect = {offset.x,
									 offset.y,
									 m_SymbolSizePercent * m_BoxSize.x,
									 m_SymbolSizePercent * m_BoxSize.y};

				DrawTexturePro(m_SymbolTexture, frameRect, dstRect, Vector2{0, 0}, 0, WHITE);
			}
		}
	}
}

void GameBoard::CalculateBounds(unsigned int rows, unsigned int cols)
{
	const float totalWidth = cols * m_BoxSize.x + (cols > 1 ? cols - 1 : 0) * m_Padding.x;
	const float totalHeight = rows * m_BoxSize.y + (rows > 1 ? rows - 1 : 0) * m_Padding.y;

	const float positionX = m_Position.x - (m_Origin.x * totalWidth);
	const float positionY = m_Position.y - (m_Origin.y * totalHeight);

	m_Bounds = Rectangle{positionX, positionY, totalWidth, totalHeight};
}

void GameBoard::FillBoxes()
{
	m_Boxes.clear();
	m_BoxStates.clear();
	m_SymbolStates.clear();

	for(int y = 0; y < m_Rows; ++y)
	{
		for(int x = 0; x < m_Cols; ++x)
		{
			//const int linearIndex = m_Cols * y + x;
			Rectangle boxBound;
			boxBound.x = m_Bounds.x + x * m_BoxSize.x + (x >= 1 ? x : 0) * m_Padding.x;
			boxBound.y = m_Bounds.y + y * m_BoxSize.y + (y >= 1 ? y : 0) * m_Padding.y;
			boxBound.width = m_BoxSize.x;
			boxBound.height = m_BoxSize.y;
			m_Boxes.push_back(boxBound);
			m_BoxStates.push_back(0);
			m_SymbolStates.push_back(0);
		}
	}
}
