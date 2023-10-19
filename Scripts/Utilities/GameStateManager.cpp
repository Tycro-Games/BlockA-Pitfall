#include "precomp.h"
#include "GameStateManager.h"

void GameStateManager::Notify(int context, EVENT ev)
{
	context;
	switch (ev)
	{
	case ALL_ENEMIES_DEAD:
		//win
		SetState(WIN);
		break;
	case PLAYER_DEAD:
		//reset

		SetState(LOSE);
		break;
	default:
		break;
	}
}

GameStateManager::GameState GameStateManager::GetState() const
{
	return state;
}

void GameStateManager::SetState(GameState _state)
{
	state = _state;
}
