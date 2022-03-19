#include "TextButton.h"

TextButton::TextButton()
	: m_Text("Button")
	, m_Bounds({100, 100, 150, 40})
	, m_FontSize(32)
	, m_ButtonState(0)

{}

void TextButton::SetSize(const Vector2& size)
{
	m_Bounds.width = size.x;
	m_Bounds.height = size.y;
}

void TextButton::SetPosition(const Vector2& position)
{
	m_Bounds.x = position.x;
	m_Bounds.y = position.y;
}

void TextButton::SetFontSize(unsigned int fontSize)
{
	m_FontSize = fontSize;
}

void TextButton::SetText(const std::string& text)
{
	m_Text = text;
}

bool TextButton::IsClicked()
{
	Vector2 mousePoint = GetMousePosition();

	// Check button state
	if(CheckCollisionPointRec(mousePoint, m_Bounds))
	{
		if(IsMouseButtonDown(MOUSE_LEFT_BUTTON))
		{
			m_ButtonState = 2;
		}
		else
		{
			m_ButtonState = 1;
		}

		if(IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
		{
			return true;
		}
	}
	else
	{
		m_ButtonState = 0;
	}
	return false;
}

void TextButton::Render()
{
	const float spacing = m_FontSize / 10.0f;

	Vector2 textDimensions = MeasureTextEx(GetFontDefault(), m_Text.c_str(), m_FontSize, spacing);
	Vector2 textPos;
	textPos.x = m_Bounds.x + 0.5f * m_Bounds.width - 0.5f * textDimensions.x;
	textPos.y = m_Bounds.y + 0.5f * m_Bounds.height - 0.5f * textDimensions.y;

	Color buttonBGColor = LIGHTGRAY;
	Color textColor = DARKGRAY;
	switch(m_ButtonState)
	{
	case 1: {
		buttonBGColor = DARKGRAY;
		textColor = WHITE;
		break;
	}
	case 2: {
		buttonBGColor = GRAY;
		textColor = BLACK;
		break;
	}
	default:
		break;
	}

	DrawRectangleRec(m_Bounds, buttonBGColor);
	DrawTextEx(GetFontDefault(), m_Text.c_str(), textPos, m_FontSize, spacing, textColor);
}
