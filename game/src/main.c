#include "body.h"
#include "world.h"
#include "mathf.h"
#include "raylib.h"
#include "raymath.h"

#include <stdlib.h>
#include <assert.h>

#define MAX_BODIES 10000

int main(void)
{
	InitWindow(800, 450, "Physics");
	SetTargetFPS(60);

	// game loop
	while (!WindowShouldClose())
	{
		// update
		float dt = GetFrameTime();
		float fps = (float)GetFPS();

		Vector2 position = GetMousePosition();
		if (IsMouseButtonDown(0)) 
		{
			Body* body = CreateBody();
			body->position = position;
			body->velocity = CreateVector2(GetRandomFloatValue(-5, 5), GetRandomFloatValue(-5, 5));
			body->force = CreateVector2(GetRandomFloatValue(-1, 1), GetRandomFloatValue(-1, 1));
		}

		// render
		BeginDrawing();
		ClearBackground(BLACK);
		// stats
		DrawText(TextFormat("FPS: %.2f (%.2f ms)", fps, 1000/fps), 10, 10, 20, LIME);
		DrawText(TextFormat("FRAME: %.4f", dt), 10, 30, 20, LIME);

		DrawCircle((int)position.x, (int)position.y, 10, GREEN);
		// update bodies
		Body* body = bodies;
		while (body != NULL) // do while we have a valid pointer, will be NULL at the end of the list
		{
			// update body position
			body->velocity = Vector2Add(body->velocity, body->force, dt);
			body->position = Vector2Add(body->position, body->velocity, dt);
			// draw body
			DrawCircle((int)body->position.x, (int)body->position.y, 10, PURPLE);

			body = body->next; // get next body
		}

		EndDrawing();
	}
	CloseWindow();

	free(bodies);

	return 0;
}