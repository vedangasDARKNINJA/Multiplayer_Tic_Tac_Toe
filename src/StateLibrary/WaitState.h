#pragma once
#include "IAppState.h"

class TextButton;

class WaitState : public IAppState
{
public:

// Inherited via IAppState
	virtual void OnInit() override;
	virtual void OnUpdate() override;
	virtual void OnRender() override;
	virtual void OnExit() override;

};
