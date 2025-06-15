# KITT_UI

## Summary

A UI that emulates a KITT dashboard using elements from the classic show, Knight Rider. 

## Components

### Button

A square button using a scholer scheme inspired from Knight Rider. Buttons have 4 types:
- Trivial Momentary
- Trivial Toggle
- Severe Momentary
- Severe Toggle

They are semantically colored as green, yellow, orange, and respectively. Toggle buttons have a darker variant when de-activated. Sever buttons take one second to press, fade to white while being held, and then revert to the proper color when successfully activated. 

The Cruise Mode buttons follow a slightly different implementation, where PURSUIT is blue, and only one button can be active at a time from the list of 3 (AUTO CRUISE and NORMAL CRUISE being the others).

Buttons have validators and callbacks. Validators confirm that all requirements are met in order for the button to be activated. Callbacks are what happens when the button is successfully activated. 

### Gauge

A 10-bar horizontal gauge that take a normalized input. The first 4 rectangles are green, the next 3 yellow, and the last 3 red. The label for the guage is place flush right and above the gauge. Each rectangle is colored in a darker variant until "lit."

### Indicator

A basic light lamp with 2-3 characters as it's label. 

### Pop up

Used for showing when a button validation has not been met, or to mask the screen when going into blackout mode so tapping the screen does not result in another UI element triggering. When used to display a failed button validation, there is an OK button to close the window. 

### Seven Segment

A 3-digit seven-segment display to show a speedometer or other numerical data

### Voice Visualizer

The heart of KITT, these bars update on a normalized input to light up more or fewer bars and look like KITT from the show. 
