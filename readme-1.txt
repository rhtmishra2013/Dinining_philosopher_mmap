**********************************************************************************************************

1.>total of five files 
	philosopher.cpp
	philosopher.c,host.c,sem.c,sem.h

2.>2 implementations.

3.>to compile the following

	g++ -o philo philosopher.cpp -lpthread
	g++ -o philosopher philosopher.c -pthread sem.c
	g++ -o host host.c -lpthread sem.c



4.>was getting some linker errors so couldnt write the makefile.

5.> to run the first implementation use

./philo N M


where N is the number of philosophers and M is the repetition.

6.>to run the second implemenation use

./host N M
