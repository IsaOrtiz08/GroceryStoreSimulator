#include "Queue.h"
// deault constructor
Queue::Queue() {
  front = nullptr;
  rear = nullptr;
  count = 0;
  totalCount = 0;
  idleTime = 0;
  queueStats = queueData();
}
// adds person to a queue
void Queue::enQueue(queueNodeData item) {
  queueNode *newPtr = new queueNode{item, nullptr};
  // sets front ptr if list is empty
  if (queueEmpty()) {
    front = newPtr;
  }
  // otherwise adds a new pointer to the very end
  else {
    rear->nextPtr = newPtr;
  }
  rear = newPtr;
  //increments statistics
  count++;
  totalCount++;
  queueStats.currItems += item.itemCount;
  queueStats.totalItems += item.itemCount;
  queueStats.queueCount++;
  // if the amount of people in line is greater than max queue length, update max queue length
  if (queueStats.queueCount > queueStats.maxQueueLength) {
    queueStats.maxQueueLength = queueStats.queueCount;
  }
}

//removes person from queue
queueNodeData Queue::deQueue() {
  queueNodeData dequeuedData = front->data;
  queueNode *tempPtr = front;
  front = front->nextPtr;
  if (queueEmpty()) {
    rear = nullptr;
  }
  delete tempPtr;
  //decrements counts
  count--;
  queueStats.queueCount--;
  queueStats.currItems -= dequeuedData.itemCount;
  // increses idletime if the queue is now empty
  if (queueStats.queueCount == 0) {
    queueStats.totalIdleTime++;
  }
  // increments overtime if opening hours are now over
  if (dequeuedData.timeAvailable < 720 && queueStats.queueCount > 0) {
    queueStats.totalOverTime++;
  }
  return dequeuedData;
}
//returns the headptrs data
queueNodeData Queue::peek() { return front->data; }
//returns true if the queue is empty
bool Queue::queueEmpty() { 
  return front == nullptr;
}
// outputs the current queue stats
void Queue::printQueue() {
  if (queueEmpty()) {
    cout << "Queue is empty." << endl;
  } else {
    queueNode *currentPtr = front;
    while (currentPtr != nullptr) {
      cout << "Time available: " << currentPtr->data.timeAvailable
           << ", Item count: " << currentPtr->data.itemCount << endl;
      currentPtr = currentPtr->nextPtr;
    }
  }
}
// returns how many people in line
int Queue::getCount() { return count; }

// calculates the average wait time
float Queue::getAvgWaitTime() {
  if (count == 0) {
    return 0;
  } else {
    return (float)queueStats.totalItems / count;
  }
}

//returns the total amount of people served
int Queue::getTotal() {return totalCount;}

// calcs average number of items
float Queue::getAvgNumItems() {
  if (count == 0) {
    return 0;
  } else {
    return (float)queueStats.currItems / count;
  }
}

// returns queue stats
queueData Queue::getQueueStats() { return queueStats; }

//updates current queue stats
void Queue::setQueueStats(queueData stats) { queueStats = stats; }

//increses queue stats when someone is enqueued
void Queue::enQueueStats(int totalItems, int itemCount) {
  queueStats.totalItems += totalItems;
  queueStats.currItems += itemCount;
}

//increases Queue item count
void Queue::enQueueCartList(int itemCount) {
  queueStats.cartList.push_back(itemCount);
}

//returns idle time
int Queue::getIdleTime() {return idleTime;};

//increments idle time
void  Queue::addIdleTime(){idleTime++;};

//returns over time
float Queue::getOverTime() {return queueStats.totalOverTime;}

//increments idle time
void Queue::addOverTime(float time){
  queueStats.totalOverTime += time;
}

// returns the front pointer memory address
queueNode* Queue::getFront(){return front;}