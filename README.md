# Design_Patterns
task 5 in operating systems

## Project Overview
This project, named st_pipeline, is a C++ multi-threaded application that showcases the concept of a pipeline of tasks using active objects (AOs).

In computing, an active object is an object-oriented program component that encapsulates its own thread of control. In this project, we construct a pipeline where each component, or active object, operates in a separate thread and passes tasks to the next component in the pipeline.

The program features a prime number checker, a thread-safe queue implementation and an active object model. The pipeline comprises four active objects each performing specific tasks and passing along results to the next.

## Getting Started
### Prerequisites
The program requires a C++ compiler that supports C++11 or later, and the make utility installed on your machine.

### Compilation and Execution
To compile the project, navigate to the project's root directory and run the following command in the terminal:
```bash
make all
```
To run the compiled program, use the following command:
```bash
./st_pipeline [N] [seed]
```
  *  [N] is the number of tasks you wish to run through the pipeline. This argument is mandatory.
  *  [seed] is an optional argument used for seeding the random number generator. If not provided, the program will use the current time as a seed.
 
## Detailed Program Explanation

The program consists of four stages:

1. prime.c: 

   Implementation of a prime checking function. This function accepts an unsigned integer and checks if it is a prime number. It will return 0 if the number is not prime or another value if it is prime.

2. queue.c:

   This stage involves the creation of a thread-safe queue, implemented with proper protections to be used in a multi-threaded environment. This queue is designed to hold void pointers and allows a thread to wait for an element in the queue without busy waiting. This is achieved using a condition variable.

3. activeObject.c :

   This stage involves the creation of an active object. This active object supports the following functionalities:
    * CreateActiveObject: This function initializes and starts a thread of an active object. It also sets up a queue for this object and receives a pointer to the function that will be called for each element in the queue.
    * getQueue: This function returns a pointer to the queue of the active object.
    * stop: This function stops the active object and frees all of its memory structures.

4. pipeline.c :

   This stage involves the creation of a pipeline of active objects. The pipeline is constructed as follows:
    * The first AO initializes the random generator with the provided seed, generates N six-digit numbers and sends each one to the next AO with a delay of one millisecond.
    * The second AO prints the number, checks if it is a prime, adds 11 to the number and then sends it to the third AO.
    * The third AO prints the number, checks if it is a prime, subtracts 13 from the number and sends it to the fourth AO.
    * The fourth AO prints the received number, adds 2 to it and prints the final number. If the program operates correctly, the final printed number should be equal to the first generated number.

After performing N tasks and their respective calculations, the program will terminate.

# Cleanup
```bash
make clean
```

