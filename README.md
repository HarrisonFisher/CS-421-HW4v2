This is to replace the assignment for creating the lottery scheduler for the Linux kernel. If you did manage to complete that already, you do not have to do this one. If you submit both assignments, I will assume you want me to replace the other one with this one.

- - - -

Use the Pthreads library to manage a shared list of integers, with mutex(es) used to handle synchronization. The details:

* This is a C program for a Linux/MacOS environment. You can do this on a web IDE like repl.it. While there is a "PThreads for Windows" project, I haven't had time to try it out, and the online IDE option seems to make it unnecessary for an assignment like this.
* Define a struct for a simple array-based list. 
* Declare a global variable of this type. You will share this list between threads. 
* Write two functions to work with the list:
  * add_to_list() will add a value to the end of the array if it fits. To help check whether execution is synchronized properly, add output statements
  * print_list() will display the values separated by spaces on a line
* Write a 3rd function work_on_list that follows the required prototype like thread_function() in the sample code linked to below
  * it has to take a void* as a parameter type. It will actually be the number of operations each thread will do on the list
  * Randomly choose to either add a value or print the list -- you can weight this so that it's more likely to add values than to print the list -- you will probably want to #include the stdlib.h file to be able to use the rand() function.
  * If you add a value, pick a random nonnegative integer to add (you can thus set the list to be all negative values initially to indicate which values are valid, but this is just an option)
  * Output the thread ID before the output from the add/print functions so you can see which thread did what
* Your main() should:
  * initialize anything you need to in the shared list struct
  * prompt for the number of operations for each thread to do
  * then create at least two threads with work_on_list and the number of operations as the argument (the last parameter) (a pointer to the number of operations is fine, too)
  * then join to each of the threads -- this way, we don't have to wait for an arbitrary period of time to make sure the threads complete 
* The book does cover PThreads, but you might find this link a more direct description: https://www.cs.cmu.edu/afs/cs/academic/class/15492-f07/www/pthreads.htmlLinks to an external site. (I used the join1.c example as a starting point)
* For full credit, use the mutex functions to synchronize the code. To test this, you do need to do enough operations; otherwise, the first thread may easily finish all of its operations before any other thread starts executing.
* Grading:
  * supporting the three required functions and having main() demonstrate that they work 20%
  * incorporating code to run work_on_list() in multiple threads 30%
  * synchronizing the operations properly with the mutex functions 30%
  * style -- simple comments, naming literal constants appropriately (no need to name 0 when it is just used as zero, but if 0 represents a return code that no errors happened, something like #define OK 0 and then using "return OK;" would be appropriate)
* Here is some sample output to show unsynchronized output:
Demo of two threads operating on the same array

```How many operations do you want each thread to do on the list? 40
Thread number 42949805232: Adding 143
Thread number 42949805232: Adding 129
Thread number 42949805232: Adding 108
Thread number 42949805232: Adding 56
Thread number 42949805232: Adding 119
Thread number 42949805232: Adding 151
Thread number 42949805232: Adding 105
Thread number 42949805232: Adding 193
Thread number 42949805232: Adding 166
Thread number 42949805232: Adding 132
Thread number 42949805232: Adding 47
Thread number 42949805232: 143 129 108 56 119 151 105 193 166 132 47
Thread number 42949805232: Adding 180
Thread number 42949805232: Adding 149
Thread number 42949805232: 143 129 108 56 119 151 105 193 166 132 47 180 149
Thread number 42949805232: Adding 169
Thread number 42949805232: Adding 27
Thread number 42949805232: 143 129 108 56 119 151 105 193 166 132 47 180 149 169 27
Thread number 42949805232: Adding 35
Thread number 42949805232: Adding 144
Thread number 42949805232: Adding 62
Thread number 42949805232: 143 129 108 56 119 151 105 193 166 132 47 180 149 169 27 35 144 62
Thread number 42949805232: Adding 101
Thread number 42949805232: Adding 36
Thread number 42949805232: 143 129 108 56 119 Thread number 42949805488: 151 105 193 Adding 143
166 Thread number 42949805488: 132 Adding 129
47 Thread number 42949805488: 180 Adding 108
149 Thread number 42949805488: 169 Adding 56
27 Thread number 42949805488: 35 Adding 119
144 Thread number 42949805488: 62 Adding 151
101 Thread number 42949805488: 36 Adding 105
143 Thread number 42949805488: 129 Adding 193
108 Thread number 42949805488: 56 Adding 166
119 Thread number 42949805488: 151 Adding 132
105 Thread number 42949805488: 193 Adding 47
166 Thread number 42949805488: 132 143 47 129
108 Thread number 42949805232: 56 Adding 129
119 Thread number 42949805232: 151 143 105 129 193 108 166 56 132 119 47 151 180 105 149 193 169 166 27 132 35 47 144 180 62 149 101 169 36 27 143 35 129 144 108 62 56 101 119 36 151 143 105 129 193 108 166 56 132 119 47 151 129 105
193 Thread number 42949805488: 166 Adding 180
132 Thread number 42949805488: 47 Adding 149
129 Thread number 42949805488: 180 143 149 129
108 Thread number 42949805232: 56 143 119 129 151 108 105 56 193 119 166 151 132 105 47 193 180 166 149 132 169 47 27 180 35 149 144 169 62 27 101 35 36 144 143 62 129 101 108 36 56 143 119 129 151 108 105 56 193 119 166 151 132 105 47 193 129 166 180 132 149 47
129 Thread number 42949805488: 180 Adding 169
149 Thread number 42949805488: 169 Adding 27

Thread number 42949805488: Thread number 42949805232: 143 143 129 129 108 108 56 56 119 119 151 151 105 105 193 193 166 166 132 132 47 47 180 180 149 149 169 169 27 27 35 35 144 144 62 62 101 101 36 36 143 143 129 129 108 108 56 56 119 119 151 151 105 105 193 193 166 166 132 132 47 47 129 129 180 180 149 149 169 169 27 27

Thread number 42949805488: Thread number 42949805232: Adding 35
143 Thread number 42949805488: 129 Adding 144
108 Thread number 42949805488: 56 Adding 62
119 Thread number 42949805488: 151 143 105 129 193 108 166 56 132 119 47 151 180 105 149 193 169 166 27 132 35 47 144 180 62 149 101 169 36 27 143 35 129 144 108 62 56 101 119 36 151 143 105 129 193 108 166 56 132 119 47 151 129 105 180 193 149 166 169 132 27 47 35 129 144 180 62 149
169 Thread number 42949805232: 27 Adding 134
35 Thread number 42949805232: 144 Adding 29
62 Thread number 42949805232: 134 Adding 127
29 Thread number 42949805232: 127 Adding 143

Thread number 42949805232: Thread number 42949805488: Adding 104
Adding 101
Thread number 42949805232: Thread number 42949805488: Adding 149
Adding 36
Thread number 42949805232: Thread number 42949805488: Adding 56
143 Thread number 42949805232: 129 Adding 172
108 Thread number 42949805232: 56 Adding 90
119 Thread number 42949805232: 151 List is full
105 193 166 132 47 180 149 169 27 35 144 62 101 36 143 129 108 56 119 151 105 193 166 132 47 129 180 149 169 27 35 144 62 134 29 127 143 104 101 149 36 56 172 90
Thread number 42949805488: List is full
Thread number 42949805488: 143 129 108 56 119 151 105 193 166 132 47 180 149 169 27 35 144 62 101 36 143 129 108 56 119 151 105 193 166 132 47 129 180 149 169 27 35 144 62 134 29 127 143 104 101 149 36 56 172 90
Thread number 42949805488: 143 129 108 56 119 151 105 193 166 132 47 180 149 169 27 35 144 62 101 36 143 129 108 56 119 151 105 193 166 132 47 129 180 149 169 27 35 144 62 134 29 127 143 104 101 149 36 56 172 90
Thread number 42949805488: 143 129 108 56 119 151 105 193 166 132 47 180 149 169 27 35 144 62 101 36 143 129 108 56 119 151 105 193 166 132 47 129 180 149 169 27 35 144 62 134 29 127 143 104 101 149 36 56 172 90
Thread number 42949805488: 143 129 108 56 119 151 105 193 166 132 47 180 149 169 27 35 144 62 101 36 143 129 108 56 119 151 105 193 166 132 47 129 180 149 169 27 35 144 62 134 29 127 143 104 101 149 36 56 172 90
Thread number 42949805488: List is full
Thread number 42949805488: List is full
Thread number 42949805488: List is full
Thread number 42949805488: List is full
Thread number 42949805488: List is full
Thread number 42949805488: List is full
Thread number 42949805488: List is full
Thread number 42949805488: List is full
Thread number 42949805488: List is full
Thread number 42949805488: List is full
The end
```
