#pragma once
#include "stdafx.h"
#include "IStudent.h"


class IAdvancedStudent : public IStudent
{
public:
	virtual std::string GetDissertationThesis() const = 0;
};