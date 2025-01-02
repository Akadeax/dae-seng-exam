#pragma once
#include <concepts>
#include "sol/sol.hpp"

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
