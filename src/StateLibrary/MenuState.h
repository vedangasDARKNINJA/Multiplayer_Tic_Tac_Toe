#pragma once
#include "IAppState.h"

class TextButton;

class MenuState : public IAppState
{
public:

// Inherited via IAppState
	virtual void OnInit() override;
	virtual void OnUpdate() override;
	virtual void OnRender() override;
	virtual void OnExit() override;

private:
	TextButton* m_PlayButton = nullptr;
	TextButton* m_ExitButton = nullptr;
};
