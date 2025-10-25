#include "main.h"
#include "globals.h"
#include "initialize.h"
#include "lemlib/api.hpp"
#include "devices.h"
#include "autonomous.h"
#include "./subsystems/intake.h"
#include "./subsystems/matchloader.h"
#include "./subsystems/blocker.h"
#include "./subsystems/colourSort.h"

void screen() {
	// loop forever
	while (true) {
    lemlib::Pose pose = chassis.getPose();
    pros::lcd::print(1, "X: %f, Y: %f, Theta: %f\n", pose.x, pose.y, pose.theta);
    pros::delay(50);
	}
}
void update_subsystems() {
	while(pros::competition::is_autonomous()){
		Intake::update_intake();
		ColourSort::update_colour_sort();
		pros::delay(5);
	}
}

void autonomous() {
  ColourSort::set_colour(get_colour());
  int routine = get_routine();
	pros::Task screen_task(screen);
	pros::Task subsystems_task(update_subsystems);
	if(routine == LEFT_SIDE){
		chassis.setPose(-3, 0, 0);
		ColourSort::set_colour(-1);
		//move forward to blocks
    chassis.moveToPoint(0, 23, 800);
		Intake::toggle();
		chassis.waitUntilDone();
		//intake blocks more
		chassis.moveToPoint(-6, 32, 500, {.maxSpeed=40});
		chassis.waitUntilDone();
		//keep intaking
		chassis.moveToPoint(-16, 43, 1500, {.maxSpeed=40});
		chassis.waitUntilDone();
		//go to middle goal
		chassis.moveToPose(6, 50, -128, 2000, {.forwards=false, .maxSpeed=60});
		chassis.waitUntilDone();
		// Blocker::set(EXTENDED); //retract the blocker
		Intake::set_intake(FWD); //set the intake to cycle blocks foward
		Intake::set_exit(REV); //set the exit to outtake
		pros::delay(1500);
		Intake::set_intake(OFF);
		// Blocker::set(RETRACTED); //retract the blocker
		pros::delay(500);
		//move forward idk to in front of the long goal
		chassis.moveToPoint(-31.5, 20, 1000, {.maxSpeed=300});
		chassis.waitUntilDone();
		//turn to matchloader
		chassis.turnToHeading(180, 1000, {.maxSpeed=60});
		chassis.waitUntilDone();
		Matchloader::toggle();
		pros::delay(300);
		//move foward
		chassis.moveToPoint(-31.5, -5, 1000, {.maxSpeed=40});
		Intake::toggle();
		chassis.waitUntilDone();
		chassis.moveToPoint(-33.5, -10, 200, {.minSpeed=300});
		pros::delay(2000);
		Intake::set_exit(REV);
		//move back to the thing
		chassis.moveToPoint(-32.5, 30, 1000, {.forwards=false, .maxSpeed=80});
		pros::delay(400);
		Intake::set_exit(FWD);
		chassis.waitUntilDone();
		Blocker::set(EXTENDED); //retract the blocker
		ColourSort::set_colour(get_colour()); //reset colour sort target
  }
  if(routine == RIGHT_SIDE){
		chassis.setPose(0, 0, 0);
		ColourSort::set_colour(-1);
		//move forward to blocks
    chassis.moveToPoint(-2, 19, 800);
		Intake::set_preroller(FWD);
		chassis.waitUntilDone();
		chassis.moveToPoint(6, 28, 1500, {.maxSpeed=40});
		chassis.waitUntilDone();
		chassis.moveToPoint(16, 35, 1000, {.maxSpeed=40});
		chassis.waitUntilDone();
		chassis.moveToPoint(12, 25, 1000, {.forwards=false, .maxSpeed=60});
		chassis.waitUntilDone();
		chassis.turnToHeading(-45, 1000, {.maxSpeed=60});

		chassis.waitUntilDone();
		chassis.moveToPoint(-7, 47, 2000, {.maxSpeed=60});
		chassis.waitUntilDone();
		Intake::set_intake(REV);
		pros::delay(2000);
		Intake::set_intake(OFF);
		pros::delay(500);
		Intake::set_intake(FWD);
		chassis.moveToPoint(12, 25, 750, {.forwards=false});
		chassis.waitUntilDone();
		chassis.moveToPoint(30, 10, 1000,{.maxSpeed=100});
		chassis.waitUntilDone();

  }
}