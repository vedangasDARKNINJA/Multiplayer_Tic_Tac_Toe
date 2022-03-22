#pragma once
#include "raylib.h"
#include <vector>

class GameBoard
{
public:
	GameBoard();
	~GameBoard() = default;

	void SetBlockSize(float size);
	void SetSymbolSizePercent(float sizePercent);
	void SetPadding(float padding);
	void SetOrigin(Vector2 origin);
	void SetPosition(Vector2 position);
	
	void Init(unsigned int rows, unsigned int cols);
	int Update(const int* data,bool checkForInput = true);
	void Render();

private:
	void CalculateBounds(unsigned int rows, unsigned int cols);
	void FillBoxes();

private:
	int m_Rows;
	int m_Cols;

	std::vector<int> m_BoxStates;
	std::vector<int> m_SymbolStates;
	std::vector<Rectangle> m_Boxes;

	Vector2 m_BoxSize;
	Vector2 m_Padding;
	Vector2 m_Origin;
	Vector2 m_Position;

	float m_SymbolSizePercent;
	Rectangle m_Bounds;

	Texture2D m_SymbolTexture;

};
