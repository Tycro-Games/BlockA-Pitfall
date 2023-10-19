#pragma once

class GameStateManager : public Observer
{
public:
	void Notify(int context, EVENT ev) override;


	enum GameState
	{
		PLAYING,
		LOSE,
		WIN,
		START_MENU
	};


	GameState GetState() const;

	void SetState(GameState _state);

private:
	GameState state = START_MENU;
};
