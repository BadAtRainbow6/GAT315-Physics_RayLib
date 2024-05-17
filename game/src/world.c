
#include "world.h"
#include "body.h"
#include <stdlib.h>
#include <assert.h>
#include <string.h>

ncBody* ncBodies = NULL;
int ncbodyCount = 0;
Vector2 ncGravity;

ncBody* CreateBody(Vector2 position, float mass, ncBodyType bodyType) {
	ncBody* b = (ncBody*)malloc(sizeof(ncBody));
	assert(b);

	memset(b, 0, sizeof(ncBody));

	b->position = position;
	b->mass = mass;
	b->inverseMass = (bodyType == BT_DYNAMIC) ? 1 / mass : 0;
	b->type = bodyType;

	return b;
}

void AddBody(ncBody* b) {
	assert(b);

	b->prev = NULL;
	b->next = ncBodies;

	if (ncBodies) {
		ncBodies->prev = b;
	}
	ncBodies = b;

	ncbodyCount++;
}

void DestroyBody(ncBody* body) {
	assert(body);

	if (body->prev != NULL) body->prev->next = body->next;

	if (body->next != NULL) body->next->prev = body->prev;

	if (body == ncBodies) ncBodies = body->next;

	ncbodyCount--;
	free(body);
}

void DestroyAllBodies() {

}