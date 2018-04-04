#pragma once
class CCar
{
public:
	bool IsTurnedOn();
	bool TurnOnEngine();
	bool TurnOffEngine();
	bool SetGear(int gear);
	bool SetSpeed(int speed);
	int GetGear() const;
	int GetSpeed() const;
	enum class MovementDirection;
	MovementDirection GetMovementDirection() const;

private:
	bool m_engineIsTurnedOn = false;
	int m_gear = 0;
	int m_speed = 0;
	static bool SpeedIsRangeOfGear(int speed, int gear);
	enum class Gear;
};

enum class CCar::Gear
{
	Reverse = -1,
	Neutral = 0,
	First = 1,
	Second = 2,
	Third = 3,
	Fourth = 4,
	Fifth = 5
};

enum class CCar::MovementDirection
{
	Back,
	Forward,
	Standing
};

static const std::vector<std::pair<int, int>> SPEED_LIMITS = {
	{ -20, 0 },
	{ INT_MIN, INT_MAX },
	{ 0, 30 },
	{ 20, 50 },
	{ 30, 60 },
	{ 40, 90 },
	{ 50, 150 }
};
