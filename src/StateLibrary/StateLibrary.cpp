#include "StateLibrary.h"

#ifdef DEBUG

#include "raylib.h"

#endif // DEBUG

StateLibrary& StateLibrary::Get()
{
	static StateLibrary library;
	return library;
}

void StateLibrary::RegisterState(APP_STATE state, std::unique_ptr<IAppState>&& pState)
{
	if(state < APP_STATE::MAX_STATES)
	{
		m_States[(size_t)state] = std::move(pState);
	}
}

void StateLibrary::ProcessStateChanges()
{
	if(m_IsPendingStateChange)
	{
		m_States[(size_t)m_CurrentState]->OnExit();
		m_CurrentState = m_PendingState;
		m_IsPendingStateChange = false;
		m_States[(size_t)m_CurrentState]->OnInit();
	}
}

void StateLibrary::RequestStateChange(APP_STATE appState)
{
	if(appState != m_CurrentState)
	{
		m_PendingState = appState;
		m_IsPendingStateChange = true;
	}
}

#ifdef DEBUG
void StateLibrary::ProcessEvents()
{
	if(IsKeyDown(KEY_ONE))
	{
		RequestStateChange(APP_STATE::MENU);
	}
	else if(IsKeyDown(KEY_TWO))
	{
		RequestStateChange(APP_STATE::PLAY);
	}
	else if(IsKeyDown(KEY_THREE))
	{
		RequestStateChange(APP_STATE::POSTGAME);
	}
}
#endif // DEBUG

void StateLibrary::Init() 
{
	m_States[(size_t)m_CurrentState]->OnInit();
}

void StateLibrary::Update()
{
	m_States[(size_t)m_CurrentState]->OnUpdate();
}

void StateLibrary::Render()
{
	m_States[(size_t)m_CurrentState]->OnRender();
}

StateLibrary::StateLibrary()
	: m_CurrentState(APP_STATE::MENU)
	, m_IsPendingStateChange(false)
	, m_PendingState(APP_STATE::MENU)
{
}
