#pragma once
//Standard input functions

#include <functional>
#include <iostream>

namespace InputActions
{


	//Any are down
	std::function<bool(bool* current, bool* last, int count)> downOrFunc =
		[](bool* current, bool* last, int count)->bool
	{
		for (int i = 0; i < count; ++i)
		{
			if (current[i])
			{
				return true;
			}
		}
		return false;
		std::cout << "Error\n";
	};

	std::function<bool(bool* current, bool* last, int count)> pressedOrFunc =
		[](bool* current, bool* last, int count)->bool
	{
		for (int i = 0; i < count; ++i)
		{
			if (current[i] && !last[i])
			{
				return true;
			}
		}
		return false;
	};

	std::function<bool(bool* current, bool* last, int count)> releasedOrFunc =
		[](bool* current, bool* last, int count)->bool
	{
		for (int i = 0; i < count; ++i)
		{
			if (!current[i] && last[i])
			{
				return true;
			}
		}
		return false;
	};

	//Can be updated using de Morgan's law
	std::function<bool(bool* current, bool* last, int count)> downAndFunc =
		[](bool* current, bool* last, int count)->bool
	{
		for (int i = 0; i < count; ++i)
		{
			if (!current[i])
			{
				return false;
			}
		}
		return true;
	};

	std::function<bool(bool* current, bool* last, int count)> pressedAndFunc =
		[](bool* current, bool* last, int count)->bool
	{
		for (int i = 0; i < count; ++i)
		{
			if (!current[i] || last[i])
			{
				return false;
			}
		}
		return false;
	};

	std::function<bool(bool* current, bool* last, int count)> releasedAndFunc =
		[](bool* current, bool* last, int count)->bool
	{
		for (int i = 0; i < count; ++i)
		{
			if (current[i] || !last[i])
			{
				return false;
			}
		}
		return true;
	};

}