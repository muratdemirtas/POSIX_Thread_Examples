/**
* @file Task_Get_ID_Syscall.c
* @author Murat Demirtas <muratdemirtastr@gmail.com>
* @brief  Get POSIX Thread ID with syscall
* @license GNU General Public License (version 2)
*/

#include "pthread.h"    /**<Called for POSIX Thread Library*/
#include "stdio.h"      /**<Called for Standart IO(printf) function */
#include <sys/types.h>
#include <sys/syscall.h>

#define MAX_THREAD_SIZE 5  /**<Maximum Thread Size for This Demo Application */


/** @brief Thread Entry Point Function, Function pointer
 *  Created Threads will jump here when they are created by Main Function
 *  @param Thread_Arguments : Thread Creation Parameter
 *  @return none
 */
void *Task_Function_Handler(void *Thread_Arguments)
{
    /*get task id in long type*/
    long User_Thread_ID = (long)Thread_Arguments;

    /*get task id from system with syscall and print them,
     * threads will no longer active after that because this jobs will finish*/
    printf("User Task ID is Defined with %ld\n, but Syscall tell it is %ld\n",
           User_Thread_ID,(long)syscall(__NR_gettid));

    pthread_exit(NULL);

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
