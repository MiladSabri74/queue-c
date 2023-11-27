/*
 * Queue.c
 *
 *  Created on: Nov, 2023
 *  Author: m.sabri
 */

/*
 ********* Header Files *********************
 */
#include "Queue.h"

/*
 ********* Definitions **********************
 */
#define IS_PASS						true
#define IS_FAIL						false

/*
 ********* Functions  ***********************
 */

/**
	* @define Create Queue
	*	@params pointer of Queue, at first You should create queue_t structure
						and then pass the pointer of it to handler the functionality
	*	@params len is length of queue
	*	@params size is type of data you want to keepin queue for example (UINT8_t) 
	* @retval None
**/
void QUEUE_Create(Queue_t* queue,uint16_t len,size_t size)
{
	queue->data = malloc(len * sizeof(size));
	queue->capacity = len * (size < 4.0 ? 1 : ceilf(size/4.0));
	queue->quantity = 0;	
	queue->read_pointer = 0;
	queue->write_pointer = 0;
	queue->size = size;
}

/**
	* @define Check the queue is full or not
	*	@params pointer of Queue
	* @retval boolean that determine queue is full or not
**/
bool QUEUE_IsFull(Queue_t* queue)
{
	if(queue->quantity == queue->capacity)
		return IS_PASS;
	return IS_FAIL;
}

/**
	* @define Check the queue is empty or not
	*	@params pointer of Queue
	* @retval boolean that determine queue is empty or not
**/
bool QUEUE_IsEmpty(Queue_t* queue)
{
	if(queue->quantity == 0)
		return IS_PASS;
	return IS_FAIL;
}

/**
	* @define add item to queue
	*	@params pointer of Queue
	*	@params pointer of item you want to add
	* @retval boolean that determine functionality done or not
**/
bool QUEUE_Enqueue(Queue_t* queue,void *item)
{
	if(!QUEUE_IsFull(queue))
	{
		if(queue->write_pointer == queue->capacity-(queue->size < 4.0 ? 1 : ceilf(queue->size/4.0)))
		{
			memcpy(&queue->data[queue->write_pointer],item, queue->size );
			//queue->data[queue->write_pointer] = item;
			queue->write_pointer = 0;
		}
		else
		{
			memcpy(&queue->data[queue->write_pointer],item, queue->size );
			queue->write_pointer += (queue->size < 4.0 ? 1 : ceilf(queue->size/4.0));
			//queue->data[queue->write_pointer++] = item;
		}
		queue->quantity += (queue->size < 4.0 ? 1 : ceilf(queue->size/4.0));
		return IS_PASS;
	}
	return IS_FAIL;	
}

/**
	* @define remove item to queue
	*	@params pointer of Queue
	*	@params pointer of item you want to restore from queue
	* @retval boolean that determine functionality done or not
**/
bool QUEUE_Dequeue(Queue_t* queue, void *item)
{
	if(QUEUE_IsEmpty(queue))
		return IS_FAIL;
	if(queue->read_pointer == queue->capacity-(queue->size < 4.0 ? 1 : ceilf(queue->size/4.0)))
	{
		 memcpy(item,&queue->data[queue->read_pointer], queue->size );
		//item = &queue->data[queue->read_pointer];
		queue->read_pointer = 0;
	}
	else
	{
	 memcpy(item, &queue->data[queue->read_pointer], queue->size );
	 queue->read_pointer += (queue->size < 4.0 ? 1 : ceilf(queue->size/4.0));
		//item = &queue->data[queue->read_pointer++];
	}
	queue->quantity -= (queue->size < 4.0 ? 1 : ceilf(queue->size/4.0));
	return IS_PASS;
}
