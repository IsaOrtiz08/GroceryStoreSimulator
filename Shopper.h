#pragma once
#include "LinkedList.h"
#include <iostream>
#include <vector>
using namespace std;

class Shopper {
public:
	Shopper();
	int sP = (rand() % 100) + 1;
	int itemsToBuy;
	int itemsCollected;
	float itemTimes;
	void calcItemstoBuy();
	void calcItemTimes();
	listType convertType();
};