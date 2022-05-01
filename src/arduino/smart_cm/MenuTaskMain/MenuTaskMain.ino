#include "Scheduler.h"
#include "Task.h"
#include "DetectPresenceTask.h"

Scheduler sched;

void setup() {
  Serial.begin(9600);
  sched.init(10);

  Task* pirTask = new DetectPresenceTask();
  pirTask->init(50);
  sched.addTask(pirTask);
}

void loop() {
  sched.schedule();
}
