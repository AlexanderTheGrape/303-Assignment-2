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
#include <altera_avalon_pio_regs.h>
#include <alt_types.h>
#include <system.h>
#include "sys/alt_irq.h"
#include <string.h>


#include "pacemaker.h"
//#include "pacemaker.c"


#define AVI_Value 300
#define AEI_Value 800
#define PVARP_Value 50
#define VRP_Value 150
#define LRI_Value 950
#define URI_Value 900

alt_alarm AVI_timer;
alt_alarm PVARP_timer;
alt_alarm VRP_timer;
alt_alarm AEI_timer;
alt_alarm LRI_timer;
alt_alarm URI_timer;

alt_alarm Atrial_timer;
alt_alarm Ventricular_timer;

unsigned int AVI_timeout = 0;
unsigned int PVARP_timeout = 0;
unsigned int VRP_timeout = 0;
unsigned int AEI_timeout = 0;
unsigned int LRI_timeout = 0;
unsigned int URI_timeout = 0;

unsigned int LEDbits = 0;

unsigned int LED0 = 0;
unsigned int LED1 = 0;

//unsigned int buttonVal = 0;
unsigned int uiButton = 0;
//void * buttonContext = (void*) &uiButtonValue;
unsigned int maskedButton0 = 0;
unsigned int maskedButton1 = 0;
unsigned int button0_pressed = 0;
unsigned int button1_pressed = 0;

alt_u32 Atrial_timer_ISR(void* context)
{
	LED0 = 0;
	return 0;
}

alt_u32 Ventricular_timer_ISR(void* context)
{
	LED1 = 0;
	return 1;
}

alt_u32 AVI_timer_ISR(void* context)
{
	AVITO = 1;
	printf("AVI timed out");

//	alt_alarm_stop(&AVI_timer);
	return 0;
}

alt_u32 PVARP_timer_ISR(void* context)
{
	PVARPTO = 1;
	printf("PVARP timed out");
//	alt_alarm_stop(&PVARP_timer);
	return 0;
}

alt_u32 VRP_timer_ISR(void* context)
{
	VRPTO = 1;
	printf("VRP timed out");
//	alt_alarm_stop(&VRP_timer);
	return 0;
}

alt_u32 AEI_timer_ISR(void* context)
{
	AEITO = 1;
	printf("AEI timed out");

//	alt_alarm_stop(&AEI_timer);
	return 0;
}

alt_u32 LRI_timer_ISR(void* context)
{
	LRITO = 1;
	printf("LRI timed out");

//	alt_alarm_stop(&LRI_timer);
	return 0;
}

alt_u32 URI_timer_ISR(void* context)
{
	URITO = 1;
	printf("URI timed out");
//	alt_alarm_stop(&URI_timer);
	return 0;
}

void pollButtons()
{
	// Poll buttons
	uiButton = IORD_ALTERA_AVALON_PIO_DATA(BUTTONS_BASE);
	IOWR_ALTERA_AVALON_PIO_EDGE_CAP(BUTTONS_BASE, 0);// clear the edge capture register
	int maskedButton0 = uiButton & (1 << 0);
	int maskedButton1 = uiButton & (1 << 1);

	if (maskedButton0 > 0){
		ASense = 0;
	} else {
		ASense = 1;
	}
	if (maskedButton1 > 0){
		VSense = 0;
	} else {
		VSense = 1;
	}

//	printf("button0 is: %d \n", maskedButton0);
//	printf("button1 is: %d \n", maskedButton1);
//	printf("ASense is: %d \n", ASense);
//	printf("VSense is: %d \n", VSense);
}

void heartLEDs()
{

	unsigned int A_LED = ASense || APace;
	unsigned int V_LED = VSense || VPace;

//	printf("A_LED is: %d \n", A_LED);
//	printf("V_LED is: %d \n", V_LED);

	if (A_LED == 1)
	{
		LED0 = 1;
		// Start timer
		alt_alarm_stop(&Atrial_timer);
		alt_alarm_start(&Atrial_timer, 100, Atrial_timer_ISR, NULL);
	}

	if (V_LED == 1)
	{
		LED1 = 1;
		// Start timer
		alt_alarm_stop(&Ventricular_timer);
		alt_alarm_start(&Ventricular_timer, 100, Ventricular_timer_ISR, NULL);
	}

	LEDbits = 0;
	LEDbits = LEDbits | (A_LED << 0);
	LEDbits = LEDbits | (V_LED << 1);

//	unsigned int allON = 0b00001111;

	IOWR_ALTERA_AVALON_PIO_DATA(LEDS_GREEN_BASE, LEDbits);
}

void startTimers()
{
	if (AVI_stop == 1)
	{

		alt_alarm_stop(&PVARP_timer);
		alt_alarm_stop(&VRP_timer);
		alt_alarm_stop(&AEI_timer);
		alt_alarm_stop(&LRI_timer);
		alt_alarm_stop(&URI_timer);

		alt_alarm_start(&PVARP_timer, PVARP_Value, PVARP_timer_ISR, NULL);
		alt_alarm_start(&VRP_timer, VRP_Value, VRP_timer_ISR, NULL);
		alt_alarm_start(&AEI_timer, AEI_Value, AEI_timer_ISR, NULL);
		alt_alarm_start(&LRI_timer, LRI_Value, LRI_timer_ISR, NULL);
		alt_alarm_start(&URI_timer, URI_Value, URI_timer_ISR, NULL);
	}
	if (AVI_start == 1)
	{
		alt_alarm_start(&AVI_timer, AVI_Value, AVI_timer_ISR, NULL);
	}

	AVI_timeout = 0;
	PVARP_timeout = 0;
	VRP_timeout = 0;
	AEI_timeout = 0;
	LRI_timeout = 0;
	URI_timeout = 0;
}

int main()
{
	// Reset the scc
	reset();



	// Start the AVI timer
	AVI_timeout = 0;
	alt_alarm_start(&AVI_timer, AVI_Value, AVI_timer_ISR, NULL);

	while(1) // Main loop
	{
		tick();
		startTimers();
		pollButtons();
		heartLEDs();
	}

//	void* Timercontext = 0;

//	alt_alarm_start(&URI_timer, URI_Value, URI_timer_ISR, Timercontext);

//  printf("Hello from Nios II!\n");

  return 0;
}
