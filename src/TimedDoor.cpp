// Copyright Dobryaev 2021
#include<time.h>
#include<string>
#include "TimedDoor.h"

TimedDoor::TimedDoor(int time)
  :iTimeout(time), opened(false), adapter(new DoorTimerAdapter(*this)) {}

bool TimedDoor::isDoorOpened() { return this->opened; }

void TimedDoor::unlock() {
  this->opened = false;
  adapter->Timeout();
}

void TimedDoor::lock() { opened = false; }

void TimedDoor::DoorTimeOut() const { throw std::string("please close the door!"); }

void TimedDoor::throwState() {
  if (this->opened)
    throw std::string("the door is opened!");
  else
    throw std::string("the door is closed!");
}

int TimedDoor::getTime() const { return this->iTimeout; }

DoorTimerAdapter::DoorTimerAdapter(const TimedDoor& _door): door(_door) {}

void Timer::sleep(int ti) {
  time_t tic = clock();
  while (clock() < tic + ti * CLOCKS_PER_SEC) {}
}

void Timer::tregister(int time, TimerClient* timer) {
  sleep(time);
}

void DoorTimerAdapter::Timeout() {
  Timer t;
  t.tregister(door.getTime(), this);
  door.DoorTimeOut();
}
