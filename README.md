#Simulation of simple gravity pendulum

#Physics
The program for each frame solves the differential equation for the motion of a pendulum using finite difference method.
The eqation is: $\frac{d^2\theta}{dt^2}+\frac{g}{l}\sin\theta$
using finite difference method after simple transformations of the equation we get: $\theta(t+2dt) = 2\theta(t+dt)-\theta(t)-\frac{gdt^2}{l}\sin\theta(t)$
using this formula we can compute value of theta for each frame, given the initial conditions.
The initial conditions in this case are: $\theta(0) = \theta_0$ and $\omega(0) = 0$

#Visuals
I use SDL2 for rendering pendulums and graph of x(t).

#How to use
Run file main.exe, you will be asked to input number of pendulums, you want to simulate. Next you have to input the angle amplitude(in degrees) and length of the cord in this order, for each pendulum.
First three pendulums on the list will be marked by colors: red(1st), blue(2nd) and green(3rd). Every next pendulum will be black.
You can also see the graph of displacement of pendulums in time.
