#include "Scheduler.h"
#include "Task.h"
#include "DetectPresenceTask.h"
#include "DetectDrinkTakenTask.h"

Scheduler sched;

void setup() {
  Serial.begin(9600);
  sched.init(10);

  Task* pirTask = new DetectPresenceTask();
  pirTask->init(50);
  sched.addTask(pirTask);

  Task* sonarTask = new DetectDrinkTakenTask();
  sonarTask->init(60);
  sched.addTask(sonarTask);
}

void loop() {
  sched.schedule();
}
