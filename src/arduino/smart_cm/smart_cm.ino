#include "Scheduler.h"
#include "Task.h"
#include "DetectPresenceTask.h"
#include "DetectDrinkTakenTask.h"
#include "TemperatureTask.h"

// test istruction rate
long lastMillis = 0;
long loops = 0;
Scheduler sched;

void setup() {
  Serial.begin(9600); 
  sched.init(10);

  Task* pirTask = new DetectPresenceTask();
  pirTask->init(200);
  sched.addTask(pirTask);

  Task* sonarTask = new DetectDrinkTakenTask();
  sonarTask->init(300);
  sched.addTask(sonarTask);

  Task* checkTemperatureTask = new TemperatureTask();
  checkTemperatureTask->init(500);
  sched.addTask(checkTemperatureTask);
}

void loop() {  
  sched.schedule();
}
