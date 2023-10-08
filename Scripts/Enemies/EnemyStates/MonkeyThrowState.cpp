#include "precomp.h"
#include "MonkeyThrowState.h"

MonkeyThrowState::~MonkeyThrowState()
{
}

void MonkeyThrowState::OnEnter()
{
	stopTimer = new Timer();



}
void MonkeyThrowState::SpawnBall(Monkey* monkey)
{
	monkey->SetBall(new MonkeyBall(monkey->GetSubject(),monkey, monkey->GetAvatar(), monkey->GetPosition()));
}
MonkeyState* MonkeyThrowState::Update(Monkey* monkey, float deltaTime)
{
	deltaTime;
	if (stopTimer->elapsed() > TIME_TO_THROW)
	{
		cout << "Thorws some stuff'\n";
		SpawnBall(monkey);
		monkey->GetBallTimer()->reset();
		monkey->GetThrowTimer()->reset();
		MonkeyTurnState* turnState = new MonkeyTurnState();
		
		return turnState;
	}
	return nullptr;

}

void MonkeyThrowState::OnExit()
{

}
