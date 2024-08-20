#include "Shopper.h"
#include <iostream>
using namespace std;

Shopper::Shopper() {
    calcItemstoBuy();
    calcItemTimes();
 }
//determines how many items to buy based on a percentage
void Shopper::calcItemstoBuy() {
    if (sP > 0 && sP <= 40) {
        itemsToBuy = (rand() % 9) + 1;
    }
    else if (sP > 40 && sP <= 70) {
        itemsToBuy = (rand() % (21 - 10)) + 10;
    }
    else if (sP > 70 && sP <= 90) {
        itemsToBuy = (rand() % (31 - 20)) + 20;
    }
    else if (sP > 90 && sP <= 100) {
        itemsToBuy = (rand() % (61 - 30)) + 30;
    }
}
//determines the total amount of time it takes to shop for the iems
void Shopper::calcItemTimes() {
    itemTimes = 0;
    for (int i = 0; i < itemsToBuy; i++) {
        float time = (static_cast<float>((rand() % 30)) + 30.0) / 60.0;// randomly generates a time for each item
        itemTimes += time;// adds it to a sum
    }
}
// changes a shopper to listType in order to go into a checkout lane
listType Shopper::convertType() {
    listType newShopper;
    newShopper.cartId = rand() % 1000 + 1;
    newShopper.itemCount = itemsToBuy;
    return newShopper;
}