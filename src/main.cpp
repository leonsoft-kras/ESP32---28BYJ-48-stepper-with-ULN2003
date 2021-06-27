#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#pragma GCC diagnostic ignored "-Wunused-variable"
 
#include <math.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/param.h>

#include "nvs_flash.h"

#include "stepperMotor_RBC.h"



//--------------------------------------------------------------------------------
//
extern "C" 
void app_main()
{
	//Initialize NVS
	esp_err_t ret = nvs_flash_init();
	if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) 
	{
	   ESP_ERROR_CHECK(nvs_flash_erase());
	   ret = nvs_flash_init();
	}
	ESP_ERROR_CHECK(ret);	

	// gpio_num_t  pins[] = {GPIO_NUM_26, GPIO_NUM_27, GPIO_NUM_14, GPIO_NUM_12, };	    // IN1..IN4 (ULN2003) == GPIO (ESP32)
	// gpio_num_t inPin[] = {pins[2], pins[3], pins[0], pins[1]};	                    // pin order for unmodified stepper (to allow rotation in both directions) 


    StepperMotor motor (GPIO_NUM_26, GPIO_NUM_27, GPIO_NUM_14, GPIO_NUM_12, 10);        // IN1..IN4 (the order will change in the class)

    motor.direction ( 1);
    motor.waveDrive (512);
    motor.direction (-1);
    motor.waveDrive (512);

    motor.direction ( 1);
    motor.fullStep (512);
    motor.direction (-1);
    motor.fullStep (512);

    motor.direction ( 1);
    motor.halfStep (512);
    motor.direction (-1);
    motor.halfStep (512);

}
