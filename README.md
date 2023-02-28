# Philosopher
This project was made in C.
this program need some information like number of philosopher, time to eat, time to sleep, time to die.
Every philosopher need to eat then sleep, and if they werent able to eat before the time to die has passed, the program would stop. in other situation it could simply run to infinite.

The idea is to create thread for every philosopher, they all have one fork and they need two fork to eat, so when one have to eat he would lock his fork and burrow the one of the other philosopher next to him so they can't eat at the same time.

Usage : You should type "make" so everything will compile creating the executable ./philo

Then you could run the executable with "./philo #number of philosopher# #time to die# #time to eat# #time to sleep#"

You can't launch this program with more than 200 philosopher. Depending of the setting, the programm can run in infinite, you can shut it down by pressing CTRL + d.
