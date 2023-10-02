#pragma once

constexpr int MAX_OBSERVERS = 10;
class Subject
{
public:
	void AddObserver(Observer& obs);
	void RemoveObserver(Observer& obs);
	void Notify(int ctx, EVENT ev) const;
private:
	//TODO use linked list
	Observer* observers[MAX_OBSERVERS]{};
	size_t index = 0;
};
