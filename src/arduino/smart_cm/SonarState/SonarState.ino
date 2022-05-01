#include "Sonar.h"
#include "Scheduler.h"
#include "DetectDrinkTakenTask.h"

Scheduler sched;

void setup() {
  Serial.begin(9600);
  sched.init(10);

  Task* sonarTask = new DetectDrinkTakenTask();
  sonarTask->init(10);
  sonarTask->setActive(true);
  sched.addTask(sonarTask);
}

void loop() {
  sched.schedule();
  
  //-----
  //Serial.println(proximitySensor->isDrinkTaken());    
  //Serial.println(String("dist: ") + d+ "|");
  //timeTimeout();
}
