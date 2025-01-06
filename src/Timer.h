#pragma once
#include <concepts>
#include "sol/sol.hpp"

// This timer class exists as a flexible way to invoke a Callable after a certain time.
// The way this is set up allows for multiple different types of callable to be treated the same
// as each other; a Timer<sol::function> and Timer<std::function> can coexist.
// To keep these types in the same list, ITimer serves as an interface for the purpose of referring to any Timer by pointer.
class ITimer
{
public:
	virtual ~ITimer() = default;

	virtual bool MarkedForDeletion() = 0;
	virtual void Tick(float deltaTime) = 0;
};

template<typename TCallable>
concept TimerCallable = requires(TCallable t)
{
	t();
};

template<TimerCallable TCallable>
class Timer final : public ITimer
{
public:
	explicit Timer(float seconds, TCallable function, bool repeats);

	Timer(const Timer& rhs) = delete;
	Timer(Timer&& rhs) noexcept = delete;
	Timer& operator=(const Timer& rhs) = delete;
	Timer& operator=(Timer&& rhs) noexcept = delete;

	bool MarkedForDeletion() override { return m_MarkedForDeletion; }
	void Tick(float deltaTime) override;

private:
	float m_Seconds;
	TCallable m_Function;
	bool m_Repeats;

	float m_CurrentSeconds{ 0.f};
	bool m_MarkedForDeletion{ false };
};

#include "Timer.tpp"
