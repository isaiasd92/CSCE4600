/*
 * CSCE 4600
 * Program 2 : Isaias Delgado , Juan Moreira
 * Due: May 3, 2016
 * FILE: process_gen.cpp
 */
 
#include 	"defs.h"
#include 	"process_gen.h"

#define 	MAX 64          //max number of processes
#define 	LIMIT 20		//memory size limit

using namespace std;

float * block_ptr;			//pointer for the block that will hold the data in the makeMem() function
float * myBlock_ptr;		//pointer for the block that will hold the data in the my_malloc() function
float * full_buffer;		//pointer for the block that will hold the data that will not fit in the other buckets
float total_block_size;		//stores the current size of the bucket

/*  fills the process vector with data    */
void fillVector(vector<Process>& newProVector)
{
    int pro_id;
    int pro_arrive;
    float pro_mem;
    
    for(int i = 1; i <= MAX; i++)
    {
        pro_id = i;                 //creates the process id
        pro_arrive = i * 50;		//creates the arrival time
        pro_mem = i / 105.5;		//creates the memory size
                   
        Process newProcess(pro_id,pro_arrive,pro_mem);    	//assigns the new data into the constructor
        newProVector.push_back(newProcess);                 //pushes the data into the vector
    }
	
	cout << "+-----------------------+\n";
	cout << "|     ID        ARRIVAL |\n";
	cout << "+-----------------------+\n";
    for(int i = 0; i < MAX; i++)        					//loops to fill the table with data
        cout << "| Process[" << newProVector[i].getID() << "]\t" << newProVector[i].getAr() <<  endl; 
	cout << "+------------------------\n";
}

/*	prints the memory block	*/
void printMem_Malloc()
{
	cout << "+---------------------------+\n";
	cout << "| ID		MEMORY_SIZE |\n";
	cout << "+---------------------------+\n";	
	for(int i = 1; i <= MAX; i++)
		cout << "| Process[" << i << "]\t" << setprecision(3) << block_ptr[i] << " MB\n";
	cout << "+---------------------------\n";
	cout << "\n**[ Total Allocated Space: " << total_block_size << " MB ]**\n";	
}

/*	creates the memory block	*/
void makeMem(vector<Process>& newProVector)
{
	block_ptr = (float*) malloc(MAX * sizeof(float));		//uses the malloc function to create a bucket to hold data
	
	if(block_ptr == NULL)									//checks to see if the bucket is empty
		cout << "\n**[ Insufficient Memory ]**\n\n";
	else
	{
		cout << "\n************************\n";
		cout << "*       makeMem()      *\n";
		cout << "*......................*\n";
		cout << "*. Memory Block of " << MAX << " .* \n";
		cout << "*. Integers Allocated .*\n";
		cout << "*......................*\n";
		cout << "************************\n\n";

	}	
	for(int i = 1; i <= MAX; i++)
	{
		block_ptr[i] = newProVector[i-1].getMem();			//fills in the bucket with data from the vector
		total_block_size += block_ptr[i];					//increments the total bucket size to use later
	}
	busyWait();
}

/*	frees the memory block	*/
void makeFree()
{
	if(block_ptr)
	{
		free(block_ptr);								//uses the free function to clear the block pointer
		block_ptr = NULL;								//sets the block pointer to NULL to delete the remaining data
		total_block_size = 0.0;							//resets the total block size
		cout << "\n**[ Memory Block Freed ]**\n\n";
	}
	else
		cout << "\n**[ Memory Block Does Not Exist! ]**\n\n";
}

/*	prints my memory block	*/
void printMem_My(int i)
{
	cout << "+---------------------------+\n";
	cout << "| ID		MEMORY_SIZE |\n";
	cout << "+---------------------------+\n";	
	cout << "| Process[" << (i+1) << "]\t" << setprecision(3) << myBlock_ptr[i] << " MB\n";
}

/*	allocates my memory depending on the limit size	*/
void my_malloc(vector<Process>& newProVector)
{
	myBlock_ptr = (float*) malloc(MAX * sizeof(float));		//uses the malloc function to create a bucket to hold data
	full_buffer = (float*) malloc(MAX * sizeof(float));		//uses the malloc function to create a bucket to hold data that won't fit
	int j = 0;

	if(myBlock_ptr == NULL)
		cout << "\n**[ Insufficient Memory ]**\n\n";
	else
	{
		cout << "\n************************\n";
		cout << "*       my_malloc()    *\n";
		cout << "*......................*\n";
		cout << "*. Memory Block of " << MAX << " .* \n";
		cout << "*. Integers Allocated .*\n";
		cout << "*......................*\n";
		cout << "************************\n\n";
	}
	for(int i = 0; i < MAX; i++)							//loops through all the processes created
	{
		if((total_block_size + newProVector[i].getMem()) < LIMIT)	//checks to see if the current total bucket size is less than the limit
		{
			myBlock_ptr[i] = newProVector[i].getMem();				//assigns the memory data into the bucket
			printMem_My(i);											//prints out the data
			total_block_size += myBlock_ptr[i];						//increments the total size of the bucket
			cout << "| Current Total: " << total_block_size << " MB\n";
			cout << "+---------------------------\n";
		}
		else														//if the data size is past the limit, it inserts it into a separate buffer
		{
			cout << "\n!!.............................!!\n";
			cout << "!!   Process[" << (i+1) << "] Will Not Fit  !!\n";
			cout << "!!     Storing It In Buffer    !!\n";
			cout << "!!.............................!!\n\n";

			full_buffer[i] = newProVector[i].getMem();				//it fills the full-buffer with the data that will not fit
			j++;
			
			cout << "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX\n";
			cout << "X  Process[" << (i+1) << "]\t" << setprecision(3) << full_buffer[i] << "MB --> Buffer[" << (j) << "]\n";
			cout << "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX\n";
		}
	}
	busyWait();
	cout << "\n**[ Total Allocated Space: " << total_block_size << " MB ]**\n";		
}

/*	frees my allocated memory	*/
void my_free(vector<Process>& newProVector)
{
	for(int i = 0; i < MAX; i++)			//loops through all the processes
		newProVector[i].setMem(0);			//sets the memory data to zero
		
	myBlock_ptr = NULL;						//sets the pointer to NULL
	cout << "\n**[ Memory Block Freed ]**\n\n";
}

/*	prints the system time	*/
void printTime(clock_t time1, clock_t time2)
{
	long double total = (time2 - time1)/(long double)CLOCKS_PER_SEC;						//gets duration of the time supplied by the arguements
	cout << "\n**[ It took " << setprecision(4) << total << " seconds to complete ]**\n";
}

/*	busy wait	*/
void busyWait()
{
	for(int x = 0; x < 10000000; x++) {}	//does nothing
}

/*  prints the choice box    */
void box()
{
    cout << "***************************************\n";
    cout << "* CHOOSE AN OPTION FOR THE FUNCTIONS  *\n";
    cout << "*                                     *\n";
    cout << "*      A  :  MALLOC / FREE            *\n";
    cout << "*      B  :  MY_MALLOC / MY_FREE      *\n";
	cout << "*      X  :  EXIT                     *\n";
    cout << "*                                     *\n";    
    cout << "***************************************\n";
    cout << "Enter Choice : ";
}

/*  handles the choice given by the user    */
void choose()
{
    vector<Process> pro_vector;     //vector of the process class
    char choice = ' ';
	clock_t start, stop;

    box();							//prints the box first
    cin >> choice;					//receives the user choice
    switch(toupper(choice))
    {
        case 'A':
			start = clock();
			fillVector(pro_vector);
            makeMem(pro_vector);
			printMem_Malloc();
			stop = clock();
			printTime(start, stop);
            makeFree();
            break;
        case 'B':
			start = clock();
			fillVector(pro_vector);
            my_malloc(pro_vector);
			stop = clock();
			printTime(start, stop);
            my_free(pro_vector);
            break;
        case 'X':
            cout << "\tGoodbye!!" << endl;      //exits
            return;
            break;
        default:
            cout << "\tERROR: Wrong Command!" << endl;  //error handling
            break;
    }
}