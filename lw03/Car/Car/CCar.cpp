#include "stdafx.h"
#include "CCar.h"
#include <iostream>

static const std::vector<std::pair<int, int>> SPEED_LIMITS = {
	{ 0, 20 },
	{ INT_MIN, INT_MAX },
	{ 0, 30 },
	{ 20, 50 },
	{ 30, 60 },
	{ 40, 90 },
	{ 50, 150 }
};

CCar::CCar()
{
}

CCar::~CCar()
{
}

bool CCar::IsTurnedOn()
{
	return m_engine_is_turned_on;
}

bool CCar::TurnOnEngine()
{
	if (!m_engine_is_turned_on)
	{
		m_engine_is_turned_on = true;
		return true;
	}
	return false;
}

bool CCar::TurnOffEngine()
{
	if (m_engine_is_turned_on)
	{
		if (m_speed == 0)
		{
			m_engine_is_turned_on = false;
			return true;
		}
		else
		{
			return false;
		}
	}
	return false;
}

enum class CCar::Gear
{
	REVERSE = -1,
	NEUTRAL = 0,
	FIRST = 1,
	SECOND = 2,
	THIRD = 3,
	FOURTH = 4,
	FIFTH = 5
};

bool CCar::SetGear(int gear)
{
	if (!m_engine_is_turned_on && gear != static_cast<int>(Gear::NEUTRAL))
	{
		return false;
	}
	if (gear == static_cast<int>(Gear::REVERSE))
	{
		if (m_speed == 0)
		{
			m_gear = gear;
			return true;
		}
		return false;
	}
	if (gear < static_cast<int>(Gear::REVERSE) || gear > static_cast<int>(Gear::FIFTH))
	{
		return false;
	}
	if (SPEED_LIMITS[gear + 1].first <= m_speed && m_speed <= SPEED_LIMITS[gear + 1].second)
	{
		m_gear = gear;
		return true;
	}
	return false;
}

bool CCar::SetSpeed(int speed)
{
	if (!m_engine_is_turned_on && speed != 0)
	{
		return false;
	}
	if (m_gear == 0 && std::abs(speed) > std::abs(m_speed))
	{
		return false;
	}
	if (SPEED_LIMITS[m_gear + 1].first <= speed && speed <= SPEED_LIMITS[m_gear + 1].second)
	{
		m_speed = speed;
		return true;
	}
	return false;
}

int CCar::GetGear() const
{
	return m_gear;
}

int CCar::GetSpeed() const
{
	return m_speed;
}

CCar::MovementDirection CCar::GetMovementDirection() const
{
	if (m_speed > 0 && m_gear == static_cast<int>(static_cast<int>(Gear::NEUTRAL)))
	{
		return MovementDirection::Back;
	}
	if (m_speed == 0)
	{
		return MovementDirection::Standing;
	}
	return MovementDirection::Forward;
}
