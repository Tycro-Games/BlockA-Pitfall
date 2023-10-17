#include "precomp.h"
#include "MonkeyThrowState.h"

MonkeyThrowState::~MonkeyThrowState()
{
	delete stopTimer;
}

void MonkeyThrowState::OnEnter()
{
	stopTimer = new Timer();



}
void MonkeyThrowState::SpawnBall(Monkey* monkey) const
{
	const float2 startPos = monkey->GetPosition();
	const float2 finalPos = float2{ monkey->GetAvatar()->GetCollisionChecker()->GetBoxColliderPos().x,startPos.y };
	const float2 midPos = lerp(startPos, finalPos, 0.5f + Rand(0.2f)) + float2{ 0,MID_POINT_MIN + MID_POINT_RANDOM * RandomFloat() };
	monkey->SetBall(new MonkeyBall(monkey->GetSubject(), monkey, monkey->GetAvatar(), startPos, midPos, finalPos));
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
