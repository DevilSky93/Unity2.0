#pragma once

#include <vector>

template <typename... Args>
class Event
{
public:
	using Subscriber = void(Args...);
	
	void operator+=(Subscriber subscriber);
	void operator-=(Subscriber subscriber);
	
	void invoke(Args... args);

private:
	std::vector<Subscriber*> _subscribers;
};

template <typename... Args>
void Event<Args...>::operator+=(Subscriber subscriber)
{
	_subscribers.push_back(subscriber);
}

template <typename... Args>
void Event<Args...>::operator-=(Subscriber subscriber)
{
	std::erase(_subscribers, subscriber);
}

template <typename... Args>
void Event<Args...>::invoke(Args... args)
{
	for (Subscriber* subscriber : _subscribers)
	{
		(*subscriber)(args...);
	}
}
