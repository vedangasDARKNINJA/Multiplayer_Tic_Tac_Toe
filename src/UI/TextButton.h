#pragma once
#include "raylib.h"
#include <string>

class TextButton
{
public:
	TextButton();
	~TextButton() = default;
	// Settings
	void SetSize(const Vector2& size);
	void SetPosition(const Vector2& position);
	void SetFontSize(unsigned int fontSize);
	void SetText(const std::string& text);
	// Update
	bool IsClicked();
	//Render
	void Render();

private:
	Rectangle m_Bounds;
	std::string m_Text;
	unsigned int m_FontSize;

	unsigned int m_ButtonState;
};
