/*
 * SimpleTimerAlarmExample.cpp
 *
 * Based on usage example for Time + TimeAlarm libraries
 *
 * A timer is called every 15 seconds
 * Another timer is called once only after 10 seconds
 * A third timer is called 10 times.
 *
 */

#include "SimpleTimer.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

// There must be one global SimpleTimer object.
// More SimpleTimer objects can be created and run,
// although there is little point in doing so.
SimpleTimer timer;

unsigned long start_millis;

// function to be called repeatedly
void RepeatTask() {
  printf("15 second timer\n");        
}

// function to be called just once
void OnceOnlyTask() {
  printf("This timer only triggers once\n");  
}

// function to be called exactly 10 times
void TenTimesTask() {
  static int k = 0;
  k++;
  printf("called ");
  printf("%d", k);
  printf(" / 10 times.\n");
}
 
// print current arduino "uptime" on the serial port
void DigitalClockDisplay() {
  int h,m;
  int s;
  unsigned long milliseconds = current_time_millis();
  unsigned long elapsed = milliseconds - start_millis;
  printf("millis : %u\n", elapsed);
  s = milliseconds / 1000;
  m = s / 60;
  h = s / 3600;
  s = s - m * 60;
  m = m - h * 60;
  printf("%02d : %02d : %02d\n", h, m, s);
}

void setup() {

  // welcome message
  printf("SimpleTimer Example\n");
  printf("One timer is triggered every 15 seconds\n");
  printf("Another timer is set to trigger only once after 10 seconds\n");
  printf("Another timer is set to trigger 10 times\n");


  // timed actions setup
  timer.setInterval(15000, RepeatTask);
  timer.setTimeout(10000, OnceOnlyTask);
  timer.setInterval(1000, DigitalClockDisplay);
  timer.setTimer(2000, TenTimesTask, 10);
  start_millis = current_time_millis();
}

int main(void) {
  // this is where the "polling" occurs
  setup();
  while (1) {
    timer.run();  
  }
	return(0);
}