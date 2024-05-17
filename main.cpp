#include "raylib.h"
#include "raymath.h"

const int WIN_WIDTH = 1920;
const int WIN_HEIGHT = 1080;

struct AnimData
{
	Rectangle rec;
	Vector2 pos;
	int frame;
	float updateTime;
	float runningTime;
};

int main()
{
	InitWindow(WIN_WIDTH, WIN_HEIGHT, "The Adventure of Dervin");

	// check if in air
	bool isInAir = false;

	Texture2D bg = LoadTexture("C:\\VisualCodeProjects\\The-Adventure-of-Dervin\\Textures\\Background.png");
	float bgX = 0;

	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(WHITE);

		const float dT = GetFrameTime();

		if (IsKeyDown(KEY_A))
		{
			bgX += 300 * dT;
			if (bgX >= bg.width * 3.35 - 25)
			{
				bgX = 0;
			}
		}
		if (IsKeyDown(KEY_D))
		{
			bgX -= 300 * dT;
			if (bgX <= -bg.width * 3.35 + 25)
			{
				bgX = 0;
			}
		}

		// draw background
		Vector2 bg1Pos{ bgX, 0.0 };
		DrawTextureEx(bg, bg1Pos, 0.0, 3.35, WHITE);

		// draw the right background
		Vector2 bg2Pos{ bgX + bg.width * 3.35, 0.0 };
		DrawTextureEx(bg, bg2Pos, 0.0, 3.35, WHITE);

		// draw the left side background
		Vector2 bg3Pos{ bgX - WIN_WIDTH, 0.0 };
		DrawTextureEx(bg, bg3Pos, 0.0, 3.35, WHITE);


		EndDrawing();
	}
	UnloadTexture(bg);
	CloseWindow();

}