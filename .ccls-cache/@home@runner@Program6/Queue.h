#include <iostream>
#include <vector>

using namespace std;

struct queueNodeData {
  int timeAvailable; // clock time when current customer is dequeued
  int itemCount;     // the number of items for current customer
};

struct queueNode {
  queueNodeData data;
  queueNode *nextPtr;
};

struct queueData {
  int queueCount = 0; // current queue length (set to 0 initially)
  int queueuTotal = 0;
  int totalIdleTime = 0; // if queueCount == 0; this is incremented
  float totalOverTime =
      0; // increment if current time > 720 & there are people in line
  int maxQueueLength = 0; // if current queueCount > maxQueueLength, reset
  int currItems = 0;      // update as customers are added/removed from queue
  int totalItems = 0;     // running count of items purchased
  vector<int> cartList;   // running list of carts helped
};

class Queue {
private:
  queueNode *front;
  queueNode *rear;
  int count;
  int totalCount;
  int idleTime;
  queueData queueStats;

public:
  Queue();
  queueNode* getFront();
  void enQueue(queueNodeData);
  queueNodeData deQueue();
  queueNodeData peek();
  bool queueEmpty();
  void printQueue();
  int getCount();
  int getTotal();
  int getIdleTime();
  float getOverTime();
  void addOverTime(float time);
  void addIdleTime();
  float getAvgWaitTime();
  float getAvgNumItems();
  queueData getQueueStats();
  void setQueueStats(queueData stats);
  void enQueueStats(int totalItems, int itemCount);
  void enQueueCartList(int itemCount);
};