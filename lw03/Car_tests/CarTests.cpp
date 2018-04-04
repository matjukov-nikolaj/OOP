#include "stdafx.h"
#include "../Car/Car/CCar.h"

struct CarFixture
{
	CCar car;
};

struct GearWithSpeedInterval
{
	int gear;
	int minSpeed;
	int maxSpeed;
};

std::vector<GearWithSpeedInterval> GetGearsWithSpeedInterval()
{
	std::vector<GearWithSpeedInterval> carStates;
	for (size_t i = 2; i < SPEED_LIMITS.size(); i++)
	{
		GearWithSpeedInterval currCarState;
		currCarState.gear = static_cast<int>(i - 1);
		currCarState.minSpeed = static_cast<int>(SPEED_LIMITS[i].first);
		currCarState.maxSpeed = static_cast<int>(SPEED_LIMITS[i].second);
		carStates.push_back(currCarState);
	}
	return carStates;
}

namespace std {
	std::ostream& operator << (std::ostream & strm, const GearWithSpeedInterval &carState)
	{
		return strm << carState.gear<< " " << carState.minSpeed << " " << carState.maxSpeed;
	}
}

BOOST_FIXTURE_TEST_SUITE(car, CarFixture)
	BOOST_AUTO_TEST_CASE(is_turned_off_by_default)
	{
		BOOST_CHECK(!car.IsTurnedOn());
	}

	BOOST_AUTO_TEST_CASE(turn_on_engine_if_engine_is_off)
	{
		BOOST_CHECK(car.TurnOnEngine());
	}

	BOOST_AUTO_TEST_CASE(turn_off_engine_if_engine_is_on)
	{
		BOOST_CHECK(car.TurnOnEngine());
		BOOST_CHECK(car.TurnOffEngine());
	}

	struct CarFixtureWhenEngineIsOn : CarFixture
	{
		CarFixtureWhenEngineIsOn()
		{
			car.TurnOnEngine();
		}

		void SwitchToGear(int gear)
		{
			for (int i = 0; i < gear; i++)
			{
				const std::vector<GearWithSpeedInterval> gearsWithSpeedInterval = GetGearsWithSpeedInterval();
				car.SetGear(gearsWithSpeedInterval[i].gear);
				car.SetSpeed(gearsWithSpeedInterval[i].maxSpeed);
			}
		}

		void CheckSpeed(int speed)
		{
			BOOST_CHECK(speed == car.GetSpeed());
		}

		void CheckGear(int gear)
		{
			BOOST_CHECK(gear == car.GetGear());
		}

		void CheckMovementDirection(const CCar::MovementDirection &direction)
		{
			BOOST_CHECK(car.GetMovementDirection() == direction);
		}

		void CheckCarState(int speed, int gear, const CCar::MovementDirection &direction)
		{
			CheckSpeed(speed);
			CheckGear(gear);
			CheckMovementDirection(direction);
		}

		void CheckToSetGearAndSpeed(int speed, int gear, const CCar::MovementDirection &direction)
		{
			BOOST_CHECK(car.SetSpeed(speed));
			BOOST_CHECK(car.SetGear(gear));
			CheckCarState(speed, gear, direction);
		}

		void CheckToSetIncorrectGearAtCurrentSpeed(int speed, int gear, int nextGear, const CCar::MovementDirection &direction)
		{
			BOOST_CHECK(!car.SetGear(nextGear));
			CheckCarState(speed, gear, direction);
		}
	};

	BOOST_FIXTURE_TEST_SUITE(when_engine_is_turned_on, CarFixtureWhenEngineIsOn)
		BOOST_AUTO_TEST_CASE(set_neutral_when_engine_turned_on)
		{
			BOOST_CHECK(car.SetGear(0));
		}

		BOOST_AUTO_TEST_CASE(set_first_gear_from_neutral)
		{
			BOOST_CHECK(car.SetGear(1));
		}

		BOOST_AUTO_TEST_CASE(try_to_set_invalid_gear)
		{
			BOOST_CHECK(!car.SetGear(-2));
			BOOST_CHECK(!car.SetGear(6));
		}

		BOOST_AUTO_TEST_CASE(set_reverse_gear_from_neutral)
		{
			BOOST_CHECK(car.SetGear(-1));
		}

		BOOST_AUTO_TEST_CASE(try_to_turn_off_engine_when_gear_is_not_neutral)
		{
			car.SetGear(-1);
			BOOST_CHECK(!car.TurnOffEngine());
		}

		BOOST_DATA_TEST_CASE(switch_gears_at_the_borders_of_speed_interval, GetGearsWithSpeedInterval())
		{
			SwitchToGear(sample.gear);
			BOOST_CHECK(car.SetGear(sample.gear));
			BOOST_CHECK(car.SetSpeed(sample.minSpeed));
			BOOST_CHECK(car.SetSpeed(sample.maxSpeed));
			BOOST_CHECK(!car.SetSpeed(sample.minSpeed - 1));
			BOOST_CHECK(!car.SetSpeed(sample.maxSpeed + 1));
			CheckCarState(sample.maxSpeed, sample.gear, CCar::MovementDirection::Forward);
		}

		struct carFixtureWhenGearIsReverse : CarFixtureWhenEngineIsOn
		{
			carFixtureWhenGearIsReverse()
			{
				car.SetGear(-1);
			}
		};

		BOOST_FIXTURE_TEST_SUITE(when_gear_is_reverse, carFixtureWhenGearIsReverse)
			BOOST_AUTO_TEST_CASE(set_neutral_gear_from_reverse_gear)
			{
				BOOST_CHECK(car.SetGear(0));
			}

			BOOST_AUTO_TEST_CASE(set_neutral_gear_from_reverse_gear_when_mooving)
			{
				CheckToSetGearAndSpeed(15, 0, CCar::MovementDirection::Back);
			}

			BOOST_AUTO_TEST_CASE(set_speed_twenty_at_reverse_gear)
			{
				BOOST_CHECK(car.SetSpeed(20));
				CheckCarState(20, -1, CCar::MovementDirection::Back);
			}

			BOOST_AUTO_TEST_CASE(try_to_set_speed_twenty_one_at_reverse_gear)
			{
				BOOST_CHECK(!car.SetSpeed(21));
				CheckCarState(0, -1, CCar::MovementDirection::Standing);
			}
		BOOST_AUTO_TEST_SUITE_END()

		struct carFixtureWhenGearIsFirst : CarFixtureWhenEngineIsOn
		{
			carFixtureWhenGearIsFirst()
			{
				car.SetGear(1);
				car.SetSpeed(10);
			}
		};

		BOOST_FIXTURE_TEST_SUITE(when_gear_is_first, carFixtureWhenGearIsFirst)
			BOOST_AUTO_TEST_CASE(set_neutral_gear_from_first_gear)
			{
				BOOST_CHECK(car.SetGear(0));
			}

			BOOST_AUTO_TEST_CASE(set_neutral_gear_from_first_gear_when_mooving)
			{
				CheckToSetGearAndSpeed(15, 0, CCar::MovementDirection::Forward);
			}

			BOOST_AUTO_TEST_CASE(try_to_set_second_gear_at_the_speed_ten)
			{
				CheckToSetIncorrectGearAtCurrentSpeed(10, 1, 2, CCar::MovementDirection::Forward);
			}
		BOOST_AUTO_TEST_SUITE_END()

		struct carFixtureWhenGearIsSecond : carFixtureWhenGearIsFirst
		{
			carFixtureWhenGearIsSecond()
			{
				car.SetSpeed(20);
				car.SetGear(2);
			}
		};

		BOOST_FIXTURE_TEST_SUITE(when_gear_is_second, carFixtureWhenGearIsSecond)
			BOOST_AUTO_TEST_CASE(set_neutral_gear_from_second_gear)
			{
				BOOST_CHECK(car.SetGear(0));
			}

			BOOST_AUTO_TEST_CASE(set_neutral_gear_from_second_gear_when_mooving)
			{
				CheckToSetGearAndSpeed(20, 0, CCar::MovementDirection::Forward);
			}

			BOOST_AUTO_TEST_CASE(set_first_gear_from_second_gear_when_mooving_with_speed_twenty)
			{
				CheckToSetGearAndSpeed(20, 1, CCar::MovementDirection::Forward);
			}

			BOOST_AUTO_TEST_CASE(try_to_set_third_gear_at_the_speed_twenty)
			{
				CheckToSetIncorrectGearAtCurrentSpeed(20, 2, 3, CCar::MovementDirection::Forward);
			}


		BOOST_AUTO_TEST_SUITE_END()
		
		struct carFixtureWhenGearIsThird : carFixtureWhenGearIsSecond
		{
			carFixtureWhenGearIsThird()
			{
				car.SetSpeed(30);
				car.SetGear(3);
			}
		};

		BOOST_FIXTURE_TEST_SUITE(when_gear_is_third, carFixtureWhenGearIsThird)
			BOOST_AUTO_TEST_CASE(set_neutral_gear_from_third_gear)
			{
				BOOST_CHECK(car.SetGear(0));
			}

			BOOST_AUTO_TEST_CASE(set_neutral_gear_from_third_gear_when_mooving)
			{
				CheckToSetGearAndSpeed(30, 0, CCar::MovementDirection::Forward);
			}

			BOOST_AUTO_TEST_CASE(set_second_gear_from_third_gear_when_mooving_with_speed_thirty)
			{
				CheckToSetGearAndSpeed(30, 2, CCar::MovementDirection::Forward);
			}

			BOOST_AUTO_TEST_CASE(try_to_set_fourth_gear_at_the_speed_thirty)
			{
				CheckToSetIncorrectGearAtCurrentSpeed(30, 3, 4, CCar::MovementDirection::Forward);
			}
		BOOST_AUTO_TEST_SUITE_END()
		
		struct carFixtureWhenGearIsFourth : carFixtureWhenGearIsThird
		{
			carFixtureWhenGearIsFourth()
			{
				car.SetSpeed(40);
				car.SetGear(4);
			}
		};

		BOOST_FIXTURE_TEST_SUITE(when_gear_is_fourth, carFixtureWhenGearIsFourth)
			BOOST_AUTO_TEST_CASE(set_neutral_gear_from_fourth_gear)
		{
			BOOST_CHECK(car.SetGear(0));
		}

		BOOST_AUTO_TEST_CASE(set_neutral_gear_from_fourth_gear_when_mooving)
		{
			CheckToSetGearAndSpeed(40, 0, CCar::MovementDirection::Forward);
		}

		BOOST_AUTO_TEST_CASE(set_third_gear_from_fourth_gear_when_mooving_with_speed_fourty)
		{
			CheckToSetGearAndSpeed(40, 3, CCar::MovementDirection::Forward);
		}

		BOOST_AUTO_TEST_CASE(try_to_set_fifth_gear_at_the_speed_fourty)
		{
			CheckToSetIncorrectGearAtCurrentSpeed(40, 4, 5, CCar::MovementDirection::Forward);
		}
		BOOST_AUTO_TEST_SUITE_END()

		struct carFixtureWhenGearIsFifth : carFixtureWhenGearIsThird
		{
			carFixtureWhenGearIsFifth()
			{
				car.SetSpeed(50);
				car.SetGear(5);
			}
		};

		BOOST_FIXTURE_TEST_SUITE(when_gear_is_fifth, carFixtureWhenGearIsFifth)
			BOOST_AUTO_TEST_CASE(set_neutral_gear_from_fifth_gear)
		{
			BOOST_CHECK(car.SetGear(0));
		}

		BOOST_AUTO_TEST_CASE(set_neutral_gear_from_fifth_gear_when_mooving)
		{
			CheckToSetGearAndSpeed(50, 0, CCar::MovementDirection::Forward);
		}

		BOOST_AUTO_TEST_CASE(set_fourth_gear_from_fifth_gear_when_mooving_with_speed_fifty)
		{
			CheckToSetGearAndSpeed(50, 4, CCar::MovementDirection::Forward);
		}
		BOOST_AUTO_TEST_SUITE_END()
	BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()

