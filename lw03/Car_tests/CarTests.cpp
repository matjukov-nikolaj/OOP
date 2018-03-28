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

		BOOST_AUTO_TEST_CASE(try_to_turn_off_engine_when_gear_is_minus_one)
		{
			BOOST_CHECK(!car.TurnOffEngine());
		}

	BOOST_AUTO_TEST_SUITE_END();

	BOOST_AUTO_TEST_SUITE(gear_shift_at_speed)

		BOOST_AUTO_TEST_CASE(try_to_set_speed_when_engine_turned_off)
		{
			car.SetGear(0);
			car.TurnOffEngine();
			BOOST_CHECK(!car.SetSpeed(10));
			car.TurnOnEngine();
		}

		BOOST_AUTO_TEST_CASE(set_first_gear_at_speed_twenty)
		{
			BOOST_CHECK(car.SetGear(1));
			BOOST_CHECK(car.SetSpeed(20));
		}

		BOOST_AUTO_TEST_CASE(set_speed_thirty_on_first_gear)
		{
			BOOST_CHECK(car.SetSpeed(30));
		}

		BOOST_AUTO_TEST_CASE(try_to_set_speed_thirty_one_on_first_gear)
		{
			BOOST_CHECK(!car.SetSpeed(31));
		}

		BOOST_AUTO_TEST_CASE(try_to_set_speed_minus_one_on_first_gear)
		{
			BOOST_CHECK(!car.SetSpeed(-1));
		}

		BOOST_AUTO_TEST_CASE(set_second_gear_at_speed_twenty)
		{
			BOOST_CHECK(car.SetGear(2));
			BOOST_CHECK(car.SetSpeed(20));
		}

		BOOST_AUTO_TEST_CASE(set_speed_fifty_on_second_gear)
		{
			BOOST_CHECK(car.SetSpeed(50));
		}

		BOOST_AUTO_TEST_CASE(try_to_set_speed_fifty_one_on_second_gear)
		{
			BOOST_CHECK(!car.SetSpeed(51));
		}

		BOOST_AUTO_TEST_CASE(try_to_set_speed_nineteen_on_first_gear)
		{
			BOOST_CHECK(!car.SetSpeed(19));
		}

		BOOST_AUTO_TEST_CASE(set_third_gear_at_speed_thirty)
		{
			BOOST_CHECK(car.SetGear(3));
			BOOST_CHECK(car.SetSpeed(30));
		}

		BOOST_AUTO_TEST_CASE(set_speed_sixty_on_third_gear)
		{
			BOOST_CHECK(car.SetSpeed(60));
		}

		BOOST_AUTO_TEST_CASE(try_to_set_speed_sixty_one_on_third_gear)
		{
			BOOST_CHECK(!car.SetSpeed(61));
		}

		BOOST_AUTO_TEST_CASE(try_to_set_speed_twenty_nine_on_third_gear)
		{
			BOOST_CHECK(!car.SetSpeed(29));
		}

		BOOST_AUTO_TEST_CASE(set_fourth_gear_at_speed_fourty)
		{
			BOOST_CHECK(car.SetGear(4));
			BOOST_CHECK(car.SetSpeed(40));
		}

		BOOST_AUTO_TEST_CASE(set_speed_ninety_on_fourth_gear)
		{
			BOOST_CHECK(car.SetSpeed(90));
		}

		BOOST_AUTO_TEST_CASE(try_to_set_speed_ninety_one_on_fourth_gear)
		{
			BOOST_CHECK(!car.SetSpeed(91));
		}

		BOOST_AUTO_TEST_CASE(try_to_set_speed_thirty_nine_on_fourth_gear)
		{
			BOOST_CHECK(!car.SetSpeed(39));
		}

		BOOST_AUTO_TEST_CASE(set_fifth_gear_at_speed_fifty)
		{
			BOOST_CHECK(car.SetGear(5));
			BOOST_CHECK(car.SetSpeed(50));
		}

		BOOST_AUTO_TEST_CASE(set_speed_one_hundred_fifty_on_fifth_gear)
		{
			BOOST_CHECK(car.SetSpeed(150));
		}

		BOOST_AUTO_TEST_CASE(try_to_set_speed_one_hundred_fifty_one_on_fifth_gear)
		{
			BOOST_CHECK(!car.SetSpeed(151));
		}

		BOOST_AUTO_TEST_CASE(try_to_set_speed_fourty_nine_on_fifth_gear)
		{
			BOOST_CHECK(!car.SetSpeed(49));
		}

		BOOST_AUTO_TEST_CASE(set_first_gear_from_fifth_having_lowered_speed_to_ten)
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

		BOOST_AUTO_TEST_CASE(try_to_set_reverse_gear_and_speed_twenty_one)
		{
			BOOST_CHECK(!car.SetSpeed(21));
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
