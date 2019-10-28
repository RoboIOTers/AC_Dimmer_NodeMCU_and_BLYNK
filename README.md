# AC_Dimmer_NodeMCU_and_BLYNK
This repository has code for Dimming the AC appliances using NodeMCU and Blynk IOT platform

The main Idea is to implement Leading edge phase cutting method using a zero voltage cross signal.
For a 50 Hz AC mains supply,  one cylce length equals 1/50 seconds, that is 20 ms. and one half cyle is 10 ms.
we get zero voltage cross signal at every half cycle ( 10ms). 
so if the switch for the AC appliance is open for all the 10ms, the appliance gets 100% or full power. 
if somehow
we limit the switch ON time for the appliance for a fraction of this millisecond, then that appliance gets that fraction of power only.
this is achieved by using a triac.
suppose we want to supply 50% power then we will give signal to triac for only 5 ms between 0 to 10 ms interval.and hence the appliance gets 
only 50% power.
to achieve frequency matching zero voltage cross signal is used.

