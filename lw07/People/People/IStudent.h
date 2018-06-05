#pragma once
#include "stdafx.h"
#include "IPerson.h"


class IStudent : public IPerson
{
public:
	virtual std::string GetUniversityName() const = 0;
	virtual size_t GetStudentTicketNumber() const = 0;
};
