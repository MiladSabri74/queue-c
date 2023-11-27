/*
 * Queue.h
 *
 *  Created on: Nov , 2023
 *  Author: m.sabri
 */

/*
 ********* Header Files *********************
 */
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
/*
 ********* Structures ***********************
 */
typedef struct Queue_t
{
	void **data;
	uint16_t quantity;
	uint16_t write_pointer;
	uint16_t read_pointer;
	uint16_t capacity;
	size_t size;
}Queue_t;


/*
 ********* Functions Prototypes *************
 */
void QUEUE_Create(Queue_t* queue,uint16_t len,size_t size);

bool QUEUE_Enqueue(Queue_t* queue, void* item);
bool QUEUE_Dequeue(Queue_t* queue, void* item);

bool QUEUE_IsFull(Queue_t* queue);
bool QUEUE_IsEmpty(Queue_t* queue);
