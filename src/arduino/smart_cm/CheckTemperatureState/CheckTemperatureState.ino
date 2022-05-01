#include "Scheduler.h"
#include "Task.h"
#include "TemperatureTask.h"

Scheduler sched;

void setup() {
  Serial.begin(9600);
  sched.init(10);

  Task* checkTemperatureTask = new TemperatureTask();
  checkTemperatureTask->init(50);
  sched.addTask(checkTemperatureTask);

//  Task* sonarTask = new DetectDrinkTakenTask();
//  sonarTask->init(30);
//  sched.addTask(sonarTask);
}

void loop() {
  sched.schedule();
}
