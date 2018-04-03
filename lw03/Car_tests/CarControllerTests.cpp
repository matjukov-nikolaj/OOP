#include "stdafx.h"
#include "../Car/Car/CCar.h"
#include "../Car/Car/ССarController.h"
using boost::none;
using boost::optional;

struct CarControlDependencies
{
	CCar car;
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
		BOOST_CHECK(carController.HandleCommand());
		BOOST_CHECK(car.IsTurnedOn() == true);
		//BOOST_CHECK_EQUAL(car.IsTurnedOn(), expectedGear.is_initialized());
		BOOST_CHECK_EQUAL(car.GetGear(), expectedGear.get_value_or(0));
		BOOST_CHECK_EQUAL(car.GetSpeed(), expectedSpeed.get_value_or(0));
		BOOST_CHECK(input.eof());
		BOOST_CHECK_EQUAL(output.str(), expectedOutput);
	}
};

BOOST_FIXTURE_TEST_SUITE(car_controller, CarControllerFixture)
	BOOST_AUTO_TEST_CASE(can_handle_EngineOn_command)
	{
		VerifyCommandHandling("EngineOn", 0, 0, "  Engine     :   On\n");
	}
BOOST_AUTO_TEST_SUITE_END()
