/*
 * CSCE 4600
 * Program 2 : Isaias Delgado , Juan Moreira
 * Due: May 3, 2016
 * FILE: functions.cpp
 */

#include "defs.h"
#include "process_gen.h"

/*  CLASS CONSTRUCTOR   */
Process::Process()
{
    id = 0;
    arrive = 0;
    memory = 0;
}

/*  OVERLOAD CONSTRUCTOR TO ASSIGN THE DATA INTO THE CLASS  */
Process::Process(int pro_id, int pro_arrive, float pro_mem)
{
    id = pro_id;
    arrive = pro_arrive;
    memory = pro_mem;
}

/*  RETURNS THE OBJECT ID VALUE    */
int Process::getID()
{
    return id;
}

/*  RETURNS THE ARRIVAL TIME VALUE    */
int Process::getAr()
{
    return arrive;
}

/*	RETURNS THE MEMORY FOR EACH PROCESS	*/
float Process::getMem()
{
	return memory;
}

/*	SETS THE NEW MEMORY SIZE	*/
float Process::setMem(float pro_mem)
{
	memory = pro_mem;
}