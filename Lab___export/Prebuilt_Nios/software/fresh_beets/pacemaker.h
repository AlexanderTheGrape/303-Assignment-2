/*
 * pacemaker.h
 *
 *  Created on: 23/09/2019
 *      Author: amon838
 */

#ifndef PACEMAKER_H_
#define PACEMAKER_H_

// Functions
void reset();
void tick();

// Inputs
extern char ASense;
extern char VSense;
extern char APace;
extern char VPace;

extern char LRITO;
extern char VRPTO;
extern char URITO;
extern char AEITO;
extern char PVARPTO;
extern char AVITO;

extern char AVI_stop;
extern char AVI_start;

//extern char Buttons;

// Outputs
extern char O;



#endif /* PACEMAKER_H_ */
