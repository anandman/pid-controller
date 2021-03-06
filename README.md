# PID Controller

This code implements a Proportional/Integral/Derivative Controller to maneuver a vehicle around a track. 

---

## PID Controller Background
PID stands for Proportional Integral Derivative, representing the three terms in the equation above. A PID controller is a control loop feedback mechanism that continuously attempts to minimize the difference, _e(t) = SP - PV(t)_, between a process variable (_PV_) and the desired setpoint value (_SP_). The equation below is run repeatedly until the difference is minimized to an acceptable level. In the equation below, _Kp_ is the proportional gain, _Ki_ is the integral gain, and _Kd_ is the derivative gain. These parameters must be tuned (see [below](#pid-coefficient-tuning)).

<p align="center">
<img alt="u(t) = Kp*e(t) + Ki*Σe(τ) + Kd*de(t)/dt" src="images/PID_equation.svg">
</p>

The proportional term is essentially the "now error" and is the primary term contributing to the bulk of the output change, _u(t)_. The proportional term can have a steady state error which must be corrected. It can also create an overshoot of the desired output. The integral term is the sum of the error over time (i.e., "past error") and can be used to both offset the steady state error from the proportional term as well as accelerate the movement towards the setpoint. However, this acceleration can cause the current value to overshoot the setpoint beyond the proportional term. The derivative term controls the rate of change of the error (i.e., "future error"). This can have the effect of dampening the overshoot introduced by the proportional and integral terms.

In general, most industrial applications will use either a PI or a PID controller to ensure any steady state error (SSE) is corrected for. P or PD controllers can't accomplish this. A PID controller is preferable to a PI controller in situations where the dampening affect is also desired but if the priority is on speed of recovery, a PI controller may be more desirable. Here we use all three terms since we want the vehicle to drive smoothly, as well as correctly, for any passengers.

## PID Implementation
The PID controller for this project controls the steering angle to drive a vehicle in a simulator while minimizing the cross-track error (CTE). Note that the PID CTE is a negative value to move the car back towards the desired path. The main PID code is in `PID.cpp` and `PID.h` while the code in `main.cpp` interfaces between the simulator and the PID controller. 

## PID Coefficient Tuning
There are various methods that can be used to tune the three gain coefficients. The simplest is [manual tuning](https://en.wikipedia.org/wiki/PID_controller#Manual_tuning), which I used here. _Kp_ was first set to oscillate during the turns, where error will be high between current value and the desired setpoint, while keeping _Ki=Kd=0_. Then, _Ki_ was increased to accelerate the movement towards the setpoint, especially during turns. Finally, _Kd_ was set to minimize the overshoot from the first two terms.

**NB: because the throttle is essentially fixed in this implementation, even seemingly benign things like printing debug statements will change the timing of how quickly the steering angle can be changed and thus the response can be different. Further tuning will be required if the PID's performance varies relative to the simulator.**   

## Results
Here is the result of running the PID controller on the sample track in the simulator. Click on the preview to see the full video.
<p align="center">
<a href="images/PID_track.mov"><img src="images/PID_track.gif"></a>
</p>

## Dependencies
* [Udacity Self-Driving Car Simulator](https://github.com/udacity/self-driving-car-sim/releases)
* [uWebSocketIO](https://github.com/uWebSockets/uWebSockets)
    * Linux: run the [`install-ubuntu.sh`](install-ubuntu.sh) script in the repository
    * Mac: run the [`install-mac.sh`](install-mac.sh) script in the repository
    * Windows: use either Docker, VMware, or even [Windows 10 Bash on Ubuntu](https://www.howtogeek.com/249966/how-to-install-and-use-the-linux-bash-shell-on-windows-10)
* cmake >= 3.5
    * All OSes: [click here for installation instructions](https://cmake.org/install)
* make >= 4.1 (Linux, Mac), 3.81 (Windows)
    * Linux: make is installed by default on most Linux distros
    * Mac: install [Xcode command line tools](https://developer.apple.com/xcode/features) to get make (type `xcode-select --install` in Terminal)
    * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* gcc/g++ >= 5.4
    * Linux: gcc / g++ is installed by default on most Linux distros
    * Mac: same deal as make - install [Xcode command line tools](https://developer.apple.com/xcode/features)
    * Windows: recommend using [MinGW](http://www.mingw.org)

## Build and Run Instructions

1. Clone this repo
2. Install uWebSocketIO as indicated [above](#dependencies)
3. Make a build directory: `mkdir build && cd build`
4. Compile: `cmake .. && make`
5. Run it: `./pid`
6. Start Udacity simulator application
    1. Select resolution, graphics quality, etc., and press "Play!" 
    2. Select "Project 4: PID Controller"