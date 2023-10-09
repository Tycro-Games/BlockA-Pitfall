#include "precomp.h"
#include "MonkeyOnLadderState.h"

MonkeyOnLadderState::~MonkeyOnLadderState()
{
	delete stopTimer;
}

void MonkeyOnLadderState::RandomTime()
{
	randomTime = TIME_TO_THROW + RandomFloat() * VARIABLE_TIME;
}

void MonkeyOnLadderState::OnEnter()
{
	stopTimer = new Timer();
	RandomTime();
}

MonkeyState* MonkeyOnLadderState::Update(Monkey* monkey, float deltaTime)
{

	if (stopTimer->elapsedF() > randomTime&&monkey->GetBall()==nullptr)
	{
		stopTimer->reset();
		monkey->GetBallTimer()->reset();
		const float2 startPos = monkey->GetPosition();
		const float2 endPos = monkey->GetPosition() + END_POS_RELATIVE + RandomFloat() * RANDOM_OFFSET;
		const float2 midPos = lerp(startPos,endPos,0.5f);
		monkey->SetBall(new MonkeyBall(monkey->GetSubject(), monkey, monkey->GetAvatar(), startPos, midPos, endPos,SPEED));
		RandomTime();

	}
	return nullptr;
}

void MonkeyOnLadderState::OnExit()
{
}
