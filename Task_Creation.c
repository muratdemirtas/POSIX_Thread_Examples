/**
* @file Task_Creation.c
* @author Murat Demirtas <muratdemirtastr@gmail.com>
* @brief  POSIX Thread Task Creation Example For Desktop and Embedded Linux
* @license GNU General Public License (version 2)
*/

#include "pthread.h"    /**<Called for POSIX Thread Library*/
#include "stdio.h"      /**<Called for Standart IO(printf) function */
#include "unistd.h"     /**<Called for Sleep() function*/

#define MAX_THREAD_SIZE 5   /**<Maximum Thread Size for This Demo Application */
#define TASK_DELAY_TIME 1   /**<Task's block time's in second unit*/

/** @brief Thread Entry Point Function, Function pointer
 *  Created Threads will jump here when they are created by Main Function
 *  @param Thread_Arguments : Thread Creation Parameter
 *  @return none
 */
void *Task_Function_Handler(void *Thread_Arguments)
{
    /*get task id in long type*/
    long Thread_ID = (long)Thread_Arguments;

    /*thread forever loop*/
    for(;;)
    {
        /*print every message when threads are ready
         *because threads will block with sleep function
         */
        printf("Task: %ld working\n",Thread_ID );
        sleep(TASK_DELAY_TIME);
    }

}

/** @brief Main Function Entry Point
 *  Program will jump here, when this program started
 *  @param none
 *  @return none
 */
int main()

{
    /*create POSIX standart thread array*/
    pthread_t Thread_List[MAX_THREAD_SIZE];
    /*create return value for task_create function return*/
    int  Thread_Status = 0;

    /*notify user on terminal*/
    printf("Program Start With %d Thread\n",(int)MAX_THREAD_SIZE);

    /*create tasks. This task's are independent*/
    for(long int Counter = 0 ; Counter < MAX_THREAD_SIZE ; Counter++)
    {
        /*create task's end, notify user*/
        printf("Creating Thread %ld\n",Counter);
        Thread_Status = pthread_create(&Thread_List[Counter],NULL,Task_Function_Handler,(void *)Counter);

        /*check if thread created succesfully, if any error occurred then notiy user*/
    if(Thread_Status)
        printf("Thread %ld, Can't Start, Return Code %d",Counter, Thread_Status);

    }

    /*main() function are not required at here, because main function also like a thread,
     * and we no longer use this function, must be exit and destroy*/
    pthread_exit(NULL);

}
