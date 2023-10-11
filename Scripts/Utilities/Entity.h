#pragma once


/**
 * \brief This is an object that gets rendered and updated
 */
class Entity
{
public:
	virtual ~Entity() = default;
	virtual void Render(Surface* screen) = 0;
	virtual void Update(float deltaTime) = 0;
	void SetActive(bool val);
	bool GetActive() const;
private:
	bool isActive = true;
};
