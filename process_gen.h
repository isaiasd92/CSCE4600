/*
 * CSCE 4600
 * Program 2 : Isaias Delgado , Juan Moreira
 * Due: May 3, 2016
 * FILE: process_gen.h
 */

#include "defs.h"

using namespace std;

class Process                           //will hold the process info
{
    private:
        int id;                         //holds the ID value
        int arrive;                     //holds the arrive time
        float memory;					//holds the memory size
        bool access;                    //process access status
        
    public:
        Process();                      //class constructor
        Process(int,int,float);   		//overload constructor (id,arriveTime,memory)
        int getID();                    //returns the object ID value
        int getAr();                    //returns the process arrival time
        float getMem();					//returns the memory size
		float setMem(float);			//sets the new memory size
}; 

void    fillVector(vector<Process>&);   //fills in the vector

void	makeMem(vector<Process>&);		//malloc function
void	printMem_Malloc();				//prints the allocated values
void	makeFree();						//free function

void	my_malloc(vector<Process>&);	//my memory allocation function
void	printMem_My(int);				//prints my allocated values
void	my_free(vector<Process>&);		//my memory free function

void	printTime(clock_t, clock_t);	//prints the system time duration
void	busyWait();						//loop that does nothing to get some time
void	box();							//box of choices for the user
void	choose();						//handles the choice made by the user