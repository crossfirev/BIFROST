// Bounce.pde
// -*- mode: C++ -*-
//
// Make a single stepper bounce from one limit to another
//
// Copyright (C) 2012 Mike McCauley
// $Id: Random.pde,v 1.1 2011/01/05 01:51:01 mikem Exp mikem $

#include <AccelStepper.h>

// Define a stepper and the pins it will use
AccelStepper stepper(1, 7, 6); // Defaults to AccelStepper::FULL4WIRE (4 pins) on 2, 3, 4, 5

void setup()
{  
   stepper.setMaxSpeed(1000);
   stepper.setSpeed(200);	
}

void loop()
{  
   stepper.runSpeed();
}
