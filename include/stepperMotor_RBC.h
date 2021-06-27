/*
  stepperMotor - Library for driving the 28BYJ-48 stepper with ULN2003 driver board.
  Created by RedBaseCap, 19. Nov, 2018.
  GPL-3.0 by redbasecap/28BYJ-48_Stepper_with_ULN2003_Driver_Libary 

  finalized for ESP-IDF by Leonsoft, 2021
  */

#ifndef STEPPER_MOTOR_H
#define STEPPER_MOTOR_H

#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

class StepperMotor

{
public:
	StepperMotor(gpio_num_t in1, gpio_num_t in2, gpio_num_t in3, gpio_num_t in4, int timedel);
	~StepperMotor()
	{
		clearInputs();
	};

	void waveDrive(int);
	void fullStep(int);
	void halfStep(int);
	void clearInputs();

	void direction(int dir);

private:
	int pause = 10;
	int direct = 1;
	gpio_num_t inPin[4] = { GPIO_NUM_26,
							GPIO_NUM_26,
							GPIO_NUM_26,
							GPIO_NUM_26};
};

#endif
