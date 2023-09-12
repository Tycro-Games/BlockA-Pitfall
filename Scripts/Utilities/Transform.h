#pragma once

class Transform
{
public:
	Transform();
	void ToWorldPos() const;
	float2 GetPosition()const;
	void SetParent(Transform& _parent);
	void SetPointerPos(float2& _pos);
	void SetPos(float2 _pos);
	Transform* GetParent();
	virtual ~Transform();
private:
	Transform* parent;
	float2* pos;
};
