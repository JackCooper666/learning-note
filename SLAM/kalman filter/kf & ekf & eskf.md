# kalman filter
## predication

$$
x_{k|k - 1} = F_{k - 1}x_{k - 1|k - 1} + 
$$
The $F_{k - 1}$ is the params' matrix. That is because the KF is the linearized. and the $w_{k - 1} =  N(0,Q_{k - 1})$ 

So it cannot be used in the LIO system, and the imu provide the acceleration and angular velocity.
## observation

## update