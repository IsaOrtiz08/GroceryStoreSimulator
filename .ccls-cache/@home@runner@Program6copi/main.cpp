#include <iostream>
#include <iomanip>
#include "LinkedList.h"
#include "Queue.h"
#include "Shopper.h"

using namespace std;

int main() {
    // Ask user for number of checkouts
    LinkedList shopperList;
    srand(0);
    int numCheckouts;
    cout << "Enter the number of checkout lines (1-10): ";
    cin >> numCheckouts;
  
    // validate the input for number of checkouts
    while (numCheckouts < 1 || numCheckouts > 10) {
        cout << "Invalid input. Enter the number of checkout lines (1-10): ";
        cin >> numCheckouts;
    }

    // Create queues for each checkout
    vector<Queue> checkoutQueues(numCheckouts);
    
    // Main loop for simulation
    int currentTime = 0;   // initialize currentTime to 0
    int cartId = 1;
  
    while (currentTime < 720) { // simulation runs for 12 hours (720 minutes)
        // generate customers/
        int numCustomers = (rand() % 3) + 1; // generate up to 5 customers at a time
        for (int i = 0; i < numCustomers; i++) {
            Shopper tempShopper;   // // create a new Shopper object
            int enterQTime = currentTime + tempShopper.itemTimes;  // calculate the time customer entered queue
            int checkoutTime = tempShopper.itemsToBuy * 0.15; // 2-7 minutes
            listType cart = { cartId++, tempShopper.itemsToBuy, enterQTime, enterQTime + checkoutTime };
            shopperList.addElement(cart);
            int shortestQueue = 0;
            for (int j = 1; j < numCheckouts; j++) {
                if (checkoutQueues[j].getCount() < checkoutQueues[shortestQueue].getCount()) {
                    shortestQueue = j;
                }
            }
            checkoutQueues[shortestQueue].enQueue({ enterQTime, tempShopper.itemsToBuy }); //enqueue the customer
            checkoutQueues[shortestQueue].enQueueCartList(tempShopper.itemsToBuy);  //enqueue cart
          
        }
        // serve customers
        for (int i = 0; i < numCheckouts; i++) {
            if (!checkoutQueues[i].queueEmpty()) {   // if the queue is not empty
                queueNodeData cart = checkoutQueues[i].peek();  // peek at the front of queue
                if (cart.timeAvailable <= currentTime) {  // if cart is available 
                    checkoutQueues[i].deQueue();    // dequeue customer
                }
            else if (checkoutQueues[i].queueEmpty()){  // if queue is empty
              checkoutQueues[i].addIdleTime(); // increment idle time 
            }
          }          
        }
        currentTime++;   // increment current time
    }

for (int i = 0; i < numCheckouts; i++){
  if (!checkoutQueues[i].queueEmpty()){  // check if queue is not empty
    float timeLeft = checkoutQueues[i].getCount() * 0.15; // calculate time remaining for all items in the queue to be checked out 
    checkoutQueues[i].addOverTime(timeLeft);  //Add the overtime to the checkout queue
    while (checkoutQueues[i].getFront() != nullptr){  
      checkoutQueues[i].addIdleTime();
      checkoutQueues[i].deQueue();
    }
  }
  }
  
    // Print results
    int totalItems = 0;
    float totalWaitTime = 0;
    float totalNumItems = 0;
    int totalPeople = 0;

    for (int i = 0; i < numCheckouts; i++) {
        Queue checkoutQueue = checkoutQueues[i];
        queueData stats = checkoutQueue.getQueueStats();
        cout << "Checkout " << i+1 << " stats:" << endl;
        cout << setw(30) << left << "  Total items: "  << right << stats.totalItems << endl;
        cout << setw(30) << left <<  "  Total customers helped: " << right << checkoutQueue.getTotal() << endl;
        cout << setw(30) << left << "  Maximum queue length: "<< right  << stats.maxQueueLength << endl;
        cout << setw(30) << left <<"  Total Idle Time: " << right  << checkoutQueues[i].getIdleTime() << endl;
      cout << setw(30) << left <<"  Total Over Time: " << right  << checkoutQueues[i].getOverTime() << endl;
      
        cout << endl;
        totalItems += stats.totalItems;
        totalWaitTime += stats.totalItems * checkoutQueue.getAvgWaitTime();
        totalNumItems += stats.currItems;
        totalPeople += checkoutQueue.getTotal();
    }

    cout << "Total number of customers: " << totalPeople << endl;
    cout << "Total items sold: " << totalItems << endl;

    return 0;
}