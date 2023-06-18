#pragma once
#include "System.h"

class Command
{
public:
	virtual ~Command() = default;
	void virtual execute(System& mySystem) = 0;
};