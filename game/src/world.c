#include "world.h"
#include <stdlib.h>
#include <assert.h>

Body* bodies = NULL;
int bodyCount = 0;

Body* CreateBody()
{
	// Allocate memory for new Body
	Body* body = (Body*)malloc(sizeof(Body));
	// Check if allocation is successful
	assert(body);
	// Initialize 'prev' to NULL and 'next' to the head of the list
	body->prev = NULL;
	body->next = bodies;
	// If list is not empty, update 'prev' of existing head
	if (bodies != NULL) {
		bodies->prev = body;
	}
	// Update head of the list to new Body
	bodies = body;
	// Increment body count
	bodyCount++;
	// Return new Body
	return body;
}

void DestroyBody(Body* body)
{
	// Assert if provided Body is not NULL
	assert(body);
	// If 'prev' is not NULL, set 'prev->next' to 'body->next'
	if (body->prev != NULL) 
	{
		body->prev->next = body->next;
	}
	// If 'next' is not NULL, set 'next->prev' to 'body->prev'
	if (body->next != NULL) 
	{
		body->next->prev = body->next;
	}
	// If body is the head, update head to 'body->next'
	if (body == bodies)
	{
		bodies = body->next;
	}
	// Decrement body count
	bodyCount--;
	// Free the body
	free(body);
}