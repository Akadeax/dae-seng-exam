#pragma once
#include "Timer.h"

template <TimerCallable TCallable>
Timer<TCallable>::Timer(float seconds, TCallable function, bool repeats)
	: m_Seconds{ seconds }, m_Function{ function }, m_Repeats{ repeats }
{
}

template <TimerCallable TCallable>
void Timer<TCallable>::Tick(float deltaTime)
{
	m_CurrentSeconds += deltaTime;
	if (m_CurrentSeconds < m_Seconds) return;

	m_Function();

	if (m_Repeats)
	{
		m_CurrentSeconds = 0.f;
	}
	else
	{
		m_MarkedForDeletion = true;
	}
}
