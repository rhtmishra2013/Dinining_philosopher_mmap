# Dinining_philosopher_mmap
Pthreads library to implement a semaphore-­‐based and deadlock-­‐free solution to the Dining Philosophers. In the Dining Philosophers problem there are N philosophers seated on a circular table and there are N forks, which are also placed in a circular fashion so that each philosopher has one on its right and one on its left. A philosopher needs two forks to eat. Your solution should enable synchronization of processes, i.e., each philosopher will run as a separate process. To achieve this, you will use Pthreads library’s PTHREAD_PROCESS_SHARED feature for condition and mutex variables and the mmap/munmap system calls.
