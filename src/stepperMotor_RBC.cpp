#include "stepperMotor_RBC.h"

///---------------------------------------------------------------------------------------
StepperMotor::StepperMotor(gpio_num_t in1, gpio_num_t in2, gpio_num_t in3, gpio_num_t in4, int timedel)
{
	//The Setup and initalisation
	inPin[0] = in3;
	inPin[1] = in4;
	inPin[2] = in1;
	inPin[3] = in2;
	pause	 = (timedel < 10) ?  10: timedel;

	for (int n = 0; n < 4; n++) {
	    gpio_pad_select_gpio (inPin[n]);           
		gpio_set_direction   (inPin[n], GPIO_MODE_OUTPUT);
	}
}

///---------------------------------------------------------------------------------------
/*
   > 0 - rotate +
   < 0 - rotate -
*/
void StepperMotor::direction(int dir)
{
	if (dir == 0) dir = 1;
	direct = dir;
}

///---------------------------------------------------------------------------------------
/*
   This function lets the step motor rotate in 512 steps. Because this 4 OUTPUT combinations
   make 4 times 11.25 degree of the rotor which is geared with a ratio of 64  so 4*11.25 / 64 =~ 1/512 per step
*/
void StepperMotor::waveDrive(int steps)
{
	uint8_t workmas [4][4] = 
	{
		{1,0,0,0},
		{0,1,0,0},
		{0,0,1,0},
		{0,0,0,1},
	};
	uint8_t work_direct1 [4]= {0,1,2,3};
	uint8_t work_direct2 [4]= {3,2,1,0};
	uint8_t* n		 		= (direct > 0) ? work_direct1 : work_direct2;

	for (int i = 0; i < steps; i++)	{
		for (int j = 0; j < 4; j++)   {
			gpio_set_level(inPin[0], workmas[ n[j] ][0]); 
			gpio_set_level(inPin[1], workmas[ n[j] ][1]); 
			gpio_set_level(inPin[2], workmas[ n[j] ][2]); 
			gpio_set_level(inPin[3], workmas[ n[j] ][3]);
			vTaskDelay (pdMS_TO_TICKS(pause));
		}
	}
}

///---------------------------------------------------------------------------------------
/*
   This function lets the step motor rotate in 512 steps. Because this 4 OUTPUT combinations
   make 4 times 11.25 degree of the rotor which is geared with a ratio of 64
   so 4*11.25 / 64 =~ 1/512 per step. Same steps but doubled the torque!
*/
void StepperMotor::fullStep(int steps)
{
	uint8_t workmas [4][4] = 
	{
		{1,1,0,0},
		{0,1,1,0},
		{0,0,1,1},
		{1,0,0,1},
	};
	uint8_t work_direct1 [4]= {0,1,2,3};
	uint8_t work_direct2 [4]= {3,2,1,0};
	uint8_t* n		 		= (direct > 0) ? work_direct1 : work_direct2;

	for (int i = 0; i < steps; i++) {
		for (int j = 0; j < 4; j++) 	{
			gpio_set_level(inPin[0], workmas[ n[j] ][0]); 
			gpio_set_level(inPin[1], workmas[ n[j] ][1]); 
			gpio_set_level(inPin[2], workmas[ n[j] ][2]); 
			gpio_set_level(inPin[3], workmas[ n[j] ][3]);
			vTaskDelay (pdMS_TO_TICKS(pause));
		}
	}
}

///---------------------------------------------------------------------------------------
/*
   This programm lets the step motor rotate in 512 steps. Because this 4 OUTPUT combinations
   make 4 times 11.25 degree of the rotor which is geared with a ratio of 64
   so 4*(11.25/2) / 64 =~ 1/1024 per step. Double step per 360 degrees but a higher precision.
*/
void StepperMotor::halfStep(int steps)
{
	uint8_t workmas [8][4] = 
	{
		{1,0,0,0},
		{1,1,0,0},
		{0,1,0,0},
		{0,1,1,0},

		{0,0,1,0},
		{0,0,1,1},
		{0,0,0,1},
		{1,0,0,1},
	};
	uint8_t work_direct1 [8]= {0,1,2,3,4,5,6,7};
	uint8_t work_direct2 [8]= {7,6,5,4,3,2,1,0};
	uint8_t* n		 		= (direct > 0) ? work_direct1 : work_direct2;

	for (int i = 0; i < steps; i++) {
		for (int j = 0; j < 8; j++) 	{
			gpio_set_level(inPin[0], workmas[ n[j] ][0]); 
			gpio_set_level(inPin[1], workmas[ n[j] ][1]); 
			gpio_set_level(inPin[2], workmas[ n[j] ][2]); 
			gpio_set_level(inPin[3], workmas[ n[j] ][3]);
			vTaskDelay (pdMS_TO_TICKS(pause));
		}
	}
}

//--------------------------------------------
// motor off
void StepperMotor::clearInputs()
{
	gpio_set_level(inPin[0], 0); 
	gpio_set_level(inPin[1], 0); 
	gpio_set_level(inPin[2], 0); 
	gpio_set_level(inPin[3], 0); 
	vTaskDelay (pdMS_TO_TICKS(pause));
}
