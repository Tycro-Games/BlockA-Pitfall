#pragma once

class Checkpoint : public Entity
{
public:
	Checkpoint();
	~Checkpoint() override;
	void Render(Surface* screen) override;
	void Update(float deltaTime) override;
	void Init(const float2& pos);
	bool GetOnScreen() const;
	const float2& GetPosition() const;
	void GetJSONString() const;
	void SaveToJSON() const;
	void Deactivate();
	void Activate();
	bool IsActivated() const;
	Subject* GetSubject() const;

private:
	Audio::Sound checkSound{"assets/Audio/CheckPoint.wav"};
	Subject* subject = nullptr;

	//inline static Audio::Sound coinSound{"assets//Audio/Pickup_Coin3.wav"};
	SavingLoading* saveLoad;
	float2 position = 0;
	//we only need one coin sprite for all of them
	Sprite* sprite = nullptr;
	Box coll;
	bool onScreen = false;
	const int FRAMES = 2;
	const float DISTANCE_TO_PLAYER = 16.0f;
	const int points = 100;
	const char* saveName = "Checkpoint";
	bool activated = false;
};
