#include "stdafx.h"

#include "../Car/Car/ССarController.h"
using boost::none;
using boost::optional;

struct CarControlDependencies
{
	std::stringstream input;
	std::stringstream output;
};

struct CarControllerFixture : CarControlDependencies
{
	ССarController carController;

	CarControllerFixture()
		: carController(input, output)
	{
	}

	// Вспомогательная функция для проверки работы команды command
	// Она принимает ожидаемый номер канала expectedChannel и expectedOutput
	void VerifyCommandHandling(const std::string& command, const optional<int>& expectedGear, const optional<int>& expectedSpeed, const std::string& expectedOutput)
	{
		// Предварительно очищаем содержимое выходного потока
		output = std::stringstream();
		input = std::stringstream();
		BOOST_CHECK(input << command);
		if (carController.HandleCommand())
		{
			BOOST_CHECK_EQUAL(carController.IsTurnedOn(), expectedGear.is_initialized());
			BOOST_CHECK_EQUAL(carController.GetGear(), expectedGear.get_value_or(0));
			BOOST_CHECK_EQUAL(carController.GetSpeed(), expectedSpeed.get_value_or(0));
		}
		BOOST_CHECK(input.eof());
		std::cout << output.str() << std::endl;
		BOOST_CHECK_EQUAL(output.str(), expectedOutput);
	}
};

BOOST_FIXTURE_TEST_SUITE(car_controller, CarControllerFixture)
	BOOST_AUTO_TEST_CASE(can_control_engine_on_with_the_command_EngineOn)
	{
		VerifyCommandHandling("EngineOn", 0, 0, "  Engine     :   On\n");
	}
	
	BOOST_AUTO_TEST_CASE(can_control_engine_Off_with_the_command_EngineOff)
	{
		BOOST_CHECK(carController.TurnOnEngine());
		VerifyCommandHandling("EngineOff", none, none, "  Engine     :   Off\n");
	}

	BOOST_AUTO_TEST_CASE(try_to_control_engine_off_when_engine_already_is_off)
	{
		VerifyCommandHandling("EngineOff", none, none, "  The engine is already off\n");
	}

	BOOST_AUTO_TEST_CASE(try_to_control_engine_on_when_engine_already_is_on)
	{
		BOOST_CHECK(carController.TurnOnEngine());
		VerifyCommandHandling("EngineOn", none, none, "  The engine is already on\n");
	}

	BOOST_AUTO_TEST_CASE(can_show_info_when_command_is_Info)
	{
		std::string info = "  Engine     :   Off\n  Gear       :   0\n  Speed      :   0\n  Direction  :   standing\n";
		VerifyCommandHandling("Info", none, none, info);
	}

	BOOST_AUTO_TEST_CASE(can_set_gear_with_the_command_SetGear)
	{
		BOOST_CHECK(carController.TurnOnEngine());
		VerifyCommandHandling("SetGear 1", 1, 0, "  Gear       :   1\n");
	}

	BOOST_AUTO_TEST_CASE(can_set_speed_with_the_command_SetSpeed)
	{
		BOOST_CHECK(carController.TurnOnEngine());
		BOOST_CHECK(carController.CCar::SetGear(1));
		VerifyCommandHandling("SetSpeed 10", 1, 10, "  Speed      :   10\n");
		std::string info = "  Engine     :   On\n  Gear       :   1\n  Speed      :   10\n  Direction  :   forward\n";
		VerifyCommandHandling("Info", 1, 10, info);
	}

	BOOST_AUTO_TEST_CASE(failed_to_set_gear_with_the_command_SetGear)
	{
		BOOST_CHECK(carController.TurnOnEngine());
		VerifyCommandHandling("SetGear 2", 0, 0, "  Failed to set gear.\n");
	}

	BOOST_AUTO_TEST_CASE(failed_to_set_speed_with_the_command_SetGear)
	{
		BOOST_CHECK(carController.TurnOnEngine());
		BOOST_CHECK(carController.CCar::SetGear(1));
		VerifyCommandHandling("SetSpeed 40", 1, 0, "  Failed to set speed.\n");
	}

BOOST_AUTO_TEST_SUITE_END()
