#include "spring.h"
#include "body.h"
#include <stdlib.h>
#include <assert.h>
#include <string.h>

ncSpring_t* ncSprings = NULL;

ncSpring_t* CreateSpring(struct ncBody* body1, struct ncBody* body2, float restLength, float k) 
{
	ncSpring_t* s = (ncSpring_t*)malloc(sizeof(ncSpring_t));
	assert(s);

	memset(s, 0, sizeof(ncSpring_t));
	s->body1 = body1;
	s->body2 = body2;
	s->restLength = restLength;
	s->k = k;

	return s;
}

void AddSpring(ncSpring_t* s) 
{
	assert(s);

	s->prev = NULL;
	s->next = ncSprings;

	if (ncSprings) {
		ncSprings->prev = s;
	}
	ncSprings = s;
}

void DestroySpring(ncSpring_t* s) 
{
	assert(s);

	if (s->prev) s->prev->next = s->next;
	if (s->next) s->next->prev = s->prev;

	if (s == ncSprings) ncSprings = s->next;

	free(s);
}

void DestroyAllSprings() 
{
	//
}

void ApplySpringForce(ncSpring_t* springs) 
{
	for (ncSpring_t* spring = springs; spring; spring = spring->next) 
	{
		Vector2 direction = Vector2Subtract(spring->body1->position, spring->body2->position);
		if (direction.x == 0 && direction.y == 0) continue;

		float length = Vector2Length(direction);
		float x = length - spring->restLength;
		float force = -spring->k * x; // f = -kx <- hooke's law

		Vector2 ndirection = Vector2Normalize(direction);

		ApplyForce(spring->body1, Vector2Scale(ndirection, force), FM_FORCE);
		ApplyForce(spring->body2, Vector2Scale(Vector2Negate(ndirection), force), FM_FORCE); //could also use -force instead
	}
}
