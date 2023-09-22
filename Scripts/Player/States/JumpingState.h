#pragma once
class JumpingState :  public State
{
    // Inherited via State
    void OnEnter() override;
    void OnExit() override;

    // Inherited via State
    void Update(Avatar& player, Input input, float deltaTime) override;
};

