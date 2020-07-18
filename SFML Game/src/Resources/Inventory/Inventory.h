#pragma once

#include <iostream>
#include <vector>
#include "Item.h"

class Inventory 
{
public:

	std::vector<Item> items;

	void AddItem(const Item& item);
	void AddItem(unsigned&& itemID);
	void AddItem(const char* itemName);
	void RemoveItem(unsigned&& index);
	void RemoveItem(const char* itemName);
	
};