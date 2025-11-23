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
int counter = 0;
void update_subsystems() {
	while(pros::competition::is_autonomous()){
		Intake::update_intake();
		ColourSort::update_colour_sort();
		pros::delay(5);
		counter++;
	}
}

void autonomous() {
  ColourSort::set_colour(get_colour());
  int routine = get_routine();
	pros::Task screen_task(screen);
	pros::Task subsystems_task(update_subsystems);
	if(routine == LEFT_SIDE_QUALS){
		chassis.setPose(0, 0, 0);
		// ColourSort::set_colour(-1)\;
		//move forward to blocks
    chassis.moveToPoint(0, 23, 800);
		Intake::toggle();
		chassis.waitUntilDone();
		//intake blocks more
		chassis.moveToPoint(-6, 31, 500, {.maxSpeed=40});
		chassis.waitUntilDone();
		//keep intaking
		chassis.moveToPoint(-16, 43, 1500, {.maxSpeed=40});
		chassis.waitUntilDone();
		//go to middle goal
		chassis.moveToPose(6, 49, -130, 2000, {.forwards=false, .maxSpeed=60});
		chassis.waitUntilDone();
		Intake::set_intake(FWD); //set the intake to cycle blocks foward
		Intake::set_exit(REV); //set the exit to outtake
		pros::delay(1500);
		//move forward idk to in front of the long goal
		chassis.moveToPoint(-32, 10, 1500, {.maxSpeed=100});
		chassis.waitUntilDone();
		//turn to matchloader
		chassis.turnToHeading(180, 1000, {.maxSpeed=60});
		chassis.waitUntilDone();
		Matchloader::toggle();
		Intake::set_intake(FWD);
		pros::delay(300);
		//move foward
		chassis.moveToPoint(-33, -5, 1000, {.maxSpeed=40});
		chassis.waitUntilDone();
		chassis.moveToPoint(-33, -99, 2000, {.maxSpeed=80});
		chassis.waitUntilDone();
		chassis.setPose(-33, -5, 180);
		Intake::set_exit(REV);
		//move back to the thing
		chassis.moveToPose(-34, 30, 180, 1000, {.forwards=false, .maxSpeed=80});
		pros::delay(400);
		Intake::set_exit(FWD);
		chassis.waitUntilDone();
		Blocker::set(EXTENDED); //retract the blocker
		// ColourSort::set_colour(get_colour()); //reset colour sort target
  }
  if(routine == RIGHT_SIDE_QUALS){
		chassis.setPose(0, 0, 0);
		// ColourSort::set_colour(-1);
		//move forward to blocks
    chassis.moveToPoint(-2, 19, 800);
		Intake::set_preroller(FWD);
		chassis.waitUntilDone();
		chassis.moveToPoint(6, 28, 1000, {.maxSpeed=60});
		chassis.waitUntilDone();
		chassis.moveToPoint(16, 35, 1000, {.maxSpeed=80});
		chassis.waitUntilDone();
		chassis.moveToPoint(12, 25, 1000, {.forwards=false, .maxSpeed=60});
		chassis.waitUntilDone();
		chassis.turnToHeading(-45, 1000, {.maxSpeed=80});

		chassis.waitUntilDone();
		chassis.moveToPoint(-9, 47, 750, {.maxSpeed=80});
		chassis.waitUntilDone();
		Intake::set_intake(REV);
		pros::delay(2000);
		Intake::set_intake(FWD);
		chassis.moveToPoint(25, 15, 1000, {.forwards=false, .maxSpeed=150});
		chassis.waitUntilDone();
		chassis.turnToHeading(180, 750, {.maxSpeed=60});
		chassis.waitUntilDone();
		Matchloader::toggle();
		chassis.moveToPoint(27, -6, 1000, {.maxSpeed=80});
		chassis.waitUntilDone();
		pros::delay(50);
		chassis.moveToPoint(27, -200, 100);
		chassis.waitUntilDone();
		pros::delay(800);
		chassis.setPose(25, -6, 180);
		chassis.moveToPoint(25, 22, 1000, {.forwards=false, .maxSpeed=80});
		chassis.waitUntilDone();
		Blocker::set(EXTENDED); //retract the blocker`
  }else if(routine == RIGHT_SIDE_ELIMS){
		chassis.setPose(0, 0, 0);
		ColourSort::set_colour(-1);
		//move forward to blocks
    chassis.moveToPoint(-2, 19, 800);
		Intake::set_intake(FWD);
		chassis.waitUntilDone();
		chassis.moveToPoint(6, 28, 1000, {.maxSpeed=60});
		chassis.waitUntilDone();
		chassis.moveToPoint(16, 35, 1000, {.maxSpeed=60});
		chassis.waitUntilDone();
		chassis.moveToPoint(12, 25, 1000, {.forwards=false, .maxSpeed=60});
		chassis.waitUntilDone();
		chassis.moveToPoint(30, 15, 1000, {.forwards=false, .maxSpeed=100});
		chassis.waitUntilDone();
		chassis.turnToHeading(180, 750, {.maxSpeed=60});
		chassis.waitUntilDone();
		Matchloader::toggle();
		chassis.moveToPoint(30, -6, 1000, {.maxSpeed=80});
		chassis.waitUntilDone();
		pros::delay(50);
		chassis.moveToPoint(30, -200, 100);
		chassis.waitUntilDone();
		pros::delay(800);
		chassis.setPose(25, -6, 180);
		chassis.moveToPoint(25, 22, 1000, {.forwards=false, .maxSpeed=80});
		chassis.waitUntilDone();
		Blocker::set(EXTENDED); //retract the blocker
		Intake::set_intake(FWD);
	
	}else if(routine == SKILLS){
		chassis.setPose(0, 0, 90);
		ColourSort::set_colour(-1);
		//move forward to blocks
    chassis.moveToPoint(40, 0, 2000, {.maxSpeed=80});
		Intake::toggle();
		chassis.waitUntilDone();
		Matchloader::toggle();
		chassis.turnToHeading(180, 1000, {.maxSpeed=80});
		chassis.waitUntilDone();
		chassis.moveToPoint(42, -12, 1000, {.maxSpeed=80});
		chassis.waitUntilDone();
		chassis.moveToPoint(42, -200, 6000, {.maxSpeed=80});
		chassis.waitUntilDone();
		chassis.setPose(42, -12, 180);
		chassis.moveToPoint(42, 0, 1000, {.forwards=false, .maxSpeed=80});
		chassis.waitUntilDone();
		chassis.turnToHeading(270, 1000, {.maxSpeed=80});
		chassis.waitUntilDone();
		chassis.moveToPoint(57, 0, 1500, {.forwards=false, .maxSpeed=80});
		chassis.waitUntilDone();
		chassis.turnToHeading(180, 1000, {.maxSpeed=80});
		chassis.moveToPoint(59, 80, 3000, {.forwards=false, .maxSpeed=80});
		chassis.waitUntilDone();
		chassis.turnToHeading(270, 1000, {.maxSpeed=80});
		chassis.waitUntilDone();
		chassis.moveToPoint(47, 80, 1500, {.maxSpeed=80});
		chassis.waitUntilDone();
		chassis.turnToHeading(0, 1000, {.maxSpeed=80});
		chassis.waitUntilDone();
		chassis.moveToPoint(45, 65, 1000, {.forwards=false, .maxSpeed=80});
		Intake::toggle();
		chassis.waitUntilDone();
		pros::delay(100);
		Blocker::set(EXTENDED); //retract the blocker
		Intake::set_intake(FWD);
		pros::delay(2000);
		chassis.setPose(45, 65, 0);
		Intake::toggle();
		pros::delay(500);
		chassis.moveToPoint(43, 85, 1000, {.maxSpeed=80});
		chassis.waitUntilDone();
		Blocker::set(RETRACTED);
		Intake::toggle();
		chassis.moveToPoint(43, 200, 10000, {.maxSpeed=80});
		chassis.waitUntilDone();
		chassis.setPose(45, 85, 0);
		chassis.moveToPoint(43, 55, 1000, {.forwards=false, .maxSpeed=80});
		chassis.waitUntilDone();
		Intake::set_intake(REV);
		pros::delay(100);
		Intake::set_intake(FWD);
		Blocker::set(EXTENDED);
		pros::delay(5000);
		chassis.setPose(45, 60, 0);
		chassis.moveToPoint(45, 70, 1000, {.maxSpeed=80});
		chassis.waitUntilDone();
		Intake::toggle();
		chassis.turnToHeading(270, 1000, {.maxSpeed=80});
		chassis.waitUntilDone();
		chassis.moveToPoint(30, 70, 1000, {.maxSpeed=80});
		chassis.waitUntilDone();
		chassis.turnToHeading(180, 1000, {.maxSpeed=80});
		chassis.waitUntilDone();
		Matchloader::toggle();
		chassis.moveToPoint(30, -30, 4000, {.maxSpeed=80});
		chassis.waitUntilDone();
		chassis.moveToPoint(30, -35, 3000, {.maxSpeed=40});
		chassis.waitUntilDone();
		chassis.turnToHeading(270, 1000, {.maxSpeed=80});
		chassis.waitUntilDone();
		chassis.moveToPoint(-5, -35, 2000, {.maxSpeed=80});
	}
}