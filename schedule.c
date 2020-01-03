/* Fill in your Name and GNumber in the following two comment fields
 * Name: Neel Prasad Narvankar
 * GNumber: G01210145
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "clock.h"
#include "structs.h"
#include "constants.h"

void adjust(Process **list, Process *temp);  /*This function is used to adjust the linked list after a node is selected for runnnig*/



/* Schedule Count
 * - Return the number of Processes in the list.
 */
int schedule_count(Process *list)
{
    /* Complete this Function */
    
    int count = 0;                    /*initially set count to zero then incerement */
    Process *walker = list;
    
    while(walker != NULL)
    {
    
        count++;                       // keep on incrementing the count until we reach the end of the loop
        walker = walker->next;         // moves walker to the next node
    }
    //printf("the Count is %d\n", count);
    return count;                               // The condition is no longer satisfied which means we have reached end of 
}                                               // the loop, we return the count of the list.

/* Schedule Insert
 * - Insert the Proc5 ess into the List with the Following Constraints
 *   list is a pointer to the list pointer for a singly linked list.
 *   It may begin as NULL
 *   1) Insert in the order of Ascending PIDs
 *   (eg. 1, 13, 14, 20, 32, 55)
 * Remember to set list to the node list if it changes!
 */
void schedule_insert(Process **list, Process *node)
{

    if(*list == NULL)                                   // This condition is used to check if the node is the first node of the list
    {                                                   // if this is the first node then make this node the head of the list
        *list = node;
        return;
    }

    if(((*list)->pid) < node->pid && (*list)->next == NULL)   //This condition is used to check if the node entering the list 
    {                                                         // is the second node of the list, hence we check for next of 
        (*list)->next = node;                                  // list is NULL ,Then point the next of list to the node if pid 
        return;                                                // of new node is greater than current node
    }
    
    else
    {
        if((*list)->pid > node->pid)                           // if node pid is less than the the pid of list make node the head 
        {                                                     // of the list
            node->next = (*list);
            (*list) = node;
            return;
        }
        
        else
        {                                                             // The first two nodes of the list are inserted 
            Process *walker = (*list);                                // insert the new node according to the pid in ascending order 
            
            while(walker->next != NULL && walker->pid < node->pid)      // set a new pointer walker pointing to the the start of the list
            {                                                           // this new pointer will be used as a scanner to scan each node 
                if (walker->next->pid > node->pid)                       // then keep moving walker until the next of walker points to the  
                {                                                        // node before which the new node is to be inserted.
                    node->next = walker->next;
                    walker->next = node;
                    return;
                }
                walker = walker->next;
                
            }
            
            walker->next = node;                                      // this means that we have reached the end of the list 
            return;                                                   // and the new node is to be inserted at the end
        }
    }
}



/* Schedule Terminate
 * - Unallocate the Memory for the given Node
 */
void schedule_terminate(Process *node)
{


    free(node);                                                   // free the node whos time_remaning is zero i.e process
    node = NULL;                                                 // is done with the execution
    return;
}


/* Schedule Generate
 * - Allocate the Memory and Create the Process from the given Variables
 *   Remember to initialize all pidues, including next!
 */
Process *schedule_generate(const char *name, int pid, int time_remaining, int time_last_run)
{

    Process *node = malloc(sizeof(Process));                                        // when a new node is to be made, assign some 
                                                                                    // memory on the heap using the malloc function
    node -> next = NULL;                                                            // set the next pointer of the node to NULL
    strncpy(node->name, name, strlen(name) + 1);                                    // use the strncpy function to set the process name keep the length of string to string +  1 for the NULL character
    node -> pid = pid;                                                             // set the 
    node -> time_remaining = time_remaining;
    node -> time_last_run = time_last_run;
    
    
    //schedule_insert(&list,node);
    
    return node ;
}

/* Schedule Select
 * - Select the next Process to be run using the following conditions:
 *   1) The Process with the lowest time_remaining should run next.
 *   - If there are any ties, select the Process with the lowest PID
 *   2) If there is a Process that has not run in >= TIME_STARVATION, then
 *      select that one instead.
 *      (Use the function clock_get_time() to get the current time)
 *   - If there are any ties, select the Process with the lowest PID
 *   3) If the list is NULL, return NULL
 * - Remove the selected Process from the list
 * - Return the selected Process
 */
Process *schedule_select(Process **list)                      //this function first selects a process to run, the "temp"
{                                                             // variable points to the process which is selected to run
    /*complete this function*/                                // the function then checks for the starvation condition 
                                                          // if a stravation condition exsits point temp to that process instead
    Process *temp = *list;                                 // once we have our temp we call the adjust function to adjust the list 
    Process *walker = *list;                              // and remove the process we want to run
    
    


    if(*list == NULL)                                       // if the list is null the function will return null
    {
        return NULL;
    }
    
    else
    {
    
        while (walker -> next != NULL)
        {
        
            if(walker -> time_remaining < temp -> time_remaining)          // set walker as a scanner and scan all the elments 
            {                                                             // when an node with lesser time_remaning is found point
                temp = walker;                                              // temp to that node
            }                         
            walker = walker -> next;                                    // set walker to walker next and continue scanning
        }
        
        if(walker -> time_remaining < temp -> time_remaining)       // if function reaches here that means we check the conditon for the last node
        {
            temp = walker;
        }
        
    
    /*This part contains the logic for checking the starvation time and selecting that process i.e setting temp to that process */
  
        walker = (*list);                                            //set walker back to start so that we can check each node for starvation
        
        
        
        while(walker->next != NULL)                                     // start incrementing walker to scan all the elements
        {
        
            if ((clock_get_time() - walker->time_last_run) >= TIME_STARVATION)    // use clock_get_time() to check for starvation condition
            {                                                                      // if starvation condition is satisfies set temp to that node
                temp = walker; 
                adjust(list, temp);
                return temp;                                 // if a process is selected it will always be with lesser pid since the list is in ascending order!!
            }
            walker = walker->next;
            
            
        }
        
        if ((clock_get_time() - walker->time_last_run) >= TIME_STARVATION)  // if we are here that means we check the condition for the last node
        {
            temp = walker;
        }
        
        adjust(list, temp);                                         // call the adjust function to remove the selected process to from the list
        return temp;                                // return the node to run
        
        
        
        
        /*-------------------------------------------------------------------------------------*/
        
        
        
        
    }
    
}


void adjust(Process **list, Process *temp)        //function is called when a node is selected to run and the list needs to be adjusted
{

    Process *change = *list;
    
    if(*list == NULL)
    {
        return;
    }
    
    else if((*list) -> pid == temp -> pid)                //this condition checks if the node selected is first node
    {
        *list = temp -> next;
        return;
    }
    
    else
    {
    
        while(change->next != temp)                   // with the help of this condition we reach till one node previous to temp
        {                                              // so that we can adjust the list, we point the next of change to the next of
                                                      // temp and return temp
            change =  change->next;
            
        }
        change->next = temp->next;                          //this checks incase of last node.
        return;
    }
}


