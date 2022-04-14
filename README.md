# Distance-calculator-STM32F429-Discovery-Board
To build a wearable speedometer which can calculate the distance travelled for 20s by measuring angular velocities available from the built-in gyroscope (L3GD20) - without a GPS or accelerometer.

Methodology/ Approach:

Get the readings from the gyroscope, that are angular velocity along x,y and z axes. 
Calculate the resultant angular velocity using the formula: Res = Resultant = (x^2 + y^2 + z^2)^1/2
Convert the resultant angular velocity into linear velocity using the formula: Linear velocity = angular velocity*radius
                                                                               Or, v = wr
The radius taken is 0.1m which is the distance from ankle to floor.
Angular velocity is the Res, which we found out.
Since, the aim is to get the distance travelled in 20 sec, with an interval of 0.5 sec.
We have 40 readings. We took 40 iterations, where after every iteration, we calculated
Distance covered = sum of linear velocities * 0.5
