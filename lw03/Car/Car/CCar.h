#pragma once
class CCar
{
public:
	CCar();
	~CCar();
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
	bool m_engine_is_turned_on = false;
	int m_gear = 0;
	int m_speed = 0;
	enum class Gear;
};

enum class CCar::MovementDirection
{
	Back,
	Forward,
	Standing
};
