#include "stdafx.h"
#include "../Car/Car/CCar.h"


using namespace std;

CCar car;

BOOST_AUTO_TEST_SUITE(car_state)

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
		BOOST_CHECK(car.TurnOffEngine());
	}

	BOOST_AUTO_TEST_SUITE(gear_shift_without_speed)

		BOOST_AUTO_TEST_CASE(set_neutral_gear_when_engine_turnded_off)
		{
			BOOST_CHECK(car.SetGear(0));
		}

		BOOST_AUTO_TEST_CASE(set_neutral_when_engine_turned_on)
		{
			car.TurnOnEngine();
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
			car.SetGear(0);
			BOOST_CHECK(car.SetGear(-1));
		}

	BOOST_AUTO_TEST_SUITE_END();

	BOOST_AUTO_TEST_SUITE(gear_shift_at_speed)

		BOOST_AUTO_TEST_CASE(try_to_set_speed_when_engine_turned_off)
		{
			car.TurnOffEngine();
			BOOST_CHECK(!car.SetSpeed(10));
			car.TurnOnEngine();
		}

		BOOST_AUTO_TEST_CASE(set_first_gear_at_speed_twenty)
		{
			BOOST_CHECK(car.SetGear(1));
			BOOST_CHECK(car.SetSpeed(20));
		}

		BOOST_AUTO_TEST_CASE(try_to_set_the_speed_fourty_in_the_first_gear)
		{
			BOOST_CHECK(!car.SetSpeed(40));
		}

		BOOST_AUTO_TEST_CASE(set_second_gear_and_speed_forty)
		{
			BOOST_CHECK(car.SetGear(2));
			BOOST_CHECK(car.SetSpeed(40));
		}

		BOOST_AUTO_TEST_CASE(set_third_gear_at_speed_forty)
		{
			BOOST_CHECK(car.SetGear(3));
		}

		BOOST_AUTO_TEST_CASE(set_fourth_gear_at_speed_forty)
		{
			BOOST_CHECK(car.SetGear(4));
		}

		BOOST_AUTO_TEST_CASE(try_to_set_fifth_gear_at_speed_forty)
		{
			BOOST_CHECK(!car.SetGear(5));
		}

		BOOST_AUTO_TEST_CASE(set_first_gear_from_fourth_having_lowered_speed_to_ten)
		{
			car.SetGear(0);
			car.SetSpeed(10);
			BOOST_CHECK(car.SetGear(1));
		}

		BOOST_AUTO_TEST_CASE(set_reverse_gear_and_speed_ten)
		{
			car.SetGear(0);
			car.SetSpeed(0);
			BOOST_CHECK(car.SetGear(-1));
			BOOST_CHECK(car.SetSpeed(10));
		}

		BOOST_AUTO_TEST_CASE(try_to_set_reverse_gear_and_speed_thirty)
		{
			BOOST_CHECK(!car.SetSpeed(30));
		}

		BOOST_AUTO_TEST_CASE(try_to_set_second_gear_and_speed_ten)
		{
			car.SetSpeed(10);
			BOOST_CHECK(!car.SetGear(2));
		}

		BOOST_AUTO_TEST_CASE(try_to_increase_the_speed_in_neutral_gear)
		{
			car.SetGear(0);
			BOOST_CHECK(!car.SetSpeed(15));
		}

	BOOST_AUTO_TEST_SUITE_END();

	BOOST_AUTO_TEST_SUITE(get_speed)

		BOOST_AUTO_TEST_CASE(try_to_get_speed)
		{
			car.SetGear(1);
			int speed = 10;
			car.SetSpeed(speed);
			BOOST_CHECK(speed == car.GetSpeed());
		}

	BOOST_AUTO_TEST_SUITE_END();

	BOOST_AUTO_TEST_SUITE(get_gear)

		BOOST_AUTO_TEST_CASE(try_to_get_gear)
		{
			int gear = 1;
			BOOST_CHECK(gear == car.GetGear());
		}

	BOOST_AUTO_TEST_SUITE_END();

	BOOST_AUTO_TEST_SUITE(get_movement_direction)

		BOOST_AUTO_TEST_CASE(the_car_rides_ahead)
		{
			car.SetGear(1);
			car.SetSpeed(10);
			BOOST_CHECK(car.GetMovementDirection() == CCar::MovementDirection::Forward);
		}

		BOOST_AUTO_TEST_CASE(the_car_rides_backwards)
		{
			car.SetGear(0);
			car.SetGear(-1);
			BOOST_CHECK(car.GetMovementDirection() == CCar::MovementDirection::Back);
		}

		BOOST_AUTO_TEST_CASE(the_car_is_standing)
		{
			car.SetGear(0);
			car.SetSpeed(0);
			BOOST_CHECK(car.GetMovementDirection() == CCar::MovementDirection::Standing);
		}

	BOOST_AUTO_TEST_SUITE_END();

BOOST_AUTO_TEST_SUITE_END();
