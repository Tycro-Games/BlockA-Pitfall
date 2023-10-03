#pragma once
enum EVENT
{
	ENEMY_CLOSE,
	COIN_COLLECTED,
	ENEMY_DEAD,
	ENEMY_HIT,
	ZOOM,
	PLAYER_HIT,
	PLAYER_DEAD
};
//source http://gameprogrammingpatterns.com/observer.html
class Observer
{
public:
	virtual ~Observer() = default;
	virtual  void Notify(int context, EVENT ev) = 0;

};

