/*
 * "Hello World" example.
 *
 * This example prints 'Hello from Nios II' to the STDOUT stream. It runs on
 * the Nios II 'standard', 'full_featured', 'fast', and 'low_cost' example
 * designs. It runs with or without the MicroC/OS-II RTOS and requires a STDOUT
 * device in your system's hardware.
 * The memory footprint of this hosted application is ~69 kbytes by default
 * using the standard reference design.
 *
 * For a reduced footprint version of this template, and an explanation of how
 * to reduce the memory footprint for a given application, see the
 * "small_hello_world" template.
 *
 */

#include <stdio.h>
#include "sys/alt_alarm.h"

#define AVI_Value 300
#define AEI_Value 800
#define PVARP_Value 50
#define VRP_Value 150
#define LRI_Value 950
#define URI_Value 900

unsigned int URITO = 0;

alt_u32 URI_timer_ISR(void* context)
{
	URITO = 1;
	printf("URI timed out");
	return 0;
}

int main()
{
	alt_alarm URI_timer;
	void* Timercontext = 0;
	URITO = 0;
	alt_alarm_start(&URI_timer, URI_Value, URI_timer_ISR, Timercontext);

//  printf("Hello from Nios II!\n");

  return 0;
}
