#pragma once
#include <array>
#include <string>
#include <memory>
#include <unordered_map>

#include "IAppState.h"

enum class APP_STATE : unsigned int
{
	MENU = 0,
	PLAY,
	POSTGAME,
	MAX_STATES
};

class StateLibrary
{
public:
	static StateLibrary& Get();

	StateLibrary(const StateLibrary&) = delete;
	StateLibrary(StateLibrary&&) = delete;
	StateLibrary& operator=(const StateLibrary&) = delete;
	StateLibrary& operator=(StateLibrary&&) = delete;

	void RegisterState(APP_STATE state, std::unique_ptr<IAppState>&& pState);
	void ProcessStateChanges();
	void RequestStateChange(APP_STATE appState);

#ifdef DEBUG
	void ProcessEvents();
#endif // DEBUG
	
	void Init();
	void Update();
	void Render();

private:
	StateLibrary();
	~StateLibrary() = default;

private:
	std::array<std::unique_ptr<IAppState>, (size_t)APP_STATE::MAX_STATES> m_States;
	APP_STATE m_CurrentState;

	APP_STATE m_PendingState;
	bool m_IsPendingStateChange;
};
