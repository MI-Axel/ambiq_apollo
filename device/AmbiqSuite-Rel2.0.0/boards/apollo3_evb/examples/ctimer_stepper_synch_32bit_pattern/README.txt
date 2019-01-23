This example demonstrates how to create arbitrary patterns on multiple
CTimers.  TMR0 A is used to create base timing for the patterns.  TMR0 B
and TMR1 A/B are configured to trigger on TMR0 with separate counting 
patterns.  All timers are configured to run and then synchronized off of 
the global timer enable.  

The patterns are output as follows:
Pin12 - TMR0 A trigger pulse
Pin13 - TMR0 B pattern1
Pin18 - TMR1 A pattern2
Pin19 - TMR1 B pattern3


