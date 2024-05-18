#include "raylib.h"
#include "raymath.h"
#include <string>
#include <cstring>
#include <iostream>

const int WIN_WIDTH = 1920;
const int WIN_HEIGHT = 1080;
std::string idle = "C:\\VisualCodeProjects\\The-Adventure-of-Dervin\\characters\\IDLE.png";
std::string walk = "C:\\VisualCodeProjects\\The-Adventure-of-Dervin\\characters\\WALK.png";
std::string attack = "C:\\VisualCodeProjects\\The-Adventure-of-Dervin\\characters\\ATTACK.png";

struct AnimData
{
	Rectangle rec;
	Vector2 pos;
	int frame;
	float updateTime;
	float runningTime;
};

bool isOnGround(AnimData data, int winHeight)
{
	return data.pos.y + 100 >= winHeight - data.rec.height;
}
AnimData updateAnimData(AnimData data, float deltaTime, int maxFrame)
{
	// update running time
	data.runningTime += deltaTime;
	if (data.runningTime >= data.updateTime)
	{
		data.runningTime = 0.0;
		//update animation frame
		data.rec.x = data.frame * data.rec.width;
		data.frame++;
		if (data.frame > maxFrame)
		{
			data.frame = 0;
		}
	}
	return data;
}

Texture2D loadTexture(std::string textureFile)
{
	return LoadTexture(textureFile.c_str());
}

int main()
{
	float scale = 3.0;

	InitWindow(WIN_WIDTH, WIN_HEIGHT, "The Adventure of Dervin");

	// --physics--

	//check for jump
	bool isInAir = false;

	// acceleration due to gravity (pixels/frame)/frame
	const int gravity = 1000;
	// jump velocity
	const int jumpVel = -600;

	float velocity = {};

	Texture2D bg = LoadTexture("C:\\VisualCodeProjects\\The-Adventure-of-Dervin\\Textures\\Background.png");
	float bgX = 0;

	Texture2D idleTexture = loadTexture(idle);
	Texture2D walkTexture = loadTexture(walk);
	Texture2D attackTexture = loadTexture(attack);

	// create character
	Texture2D dervin = loadTexture(idle);
	AnimData dervinData;
	dervinData.rec.width = dervin.width / 3;
	dervinData.rec.height = dervin.height;
	dervinData.rec.x = 0;
	dervinData.rec.y = 0;
	dervinData.pos.x = (WIN_WIDTH / 2) - (dervinData.rec.width / 2) - 100;
	dervinData.pos.y = WIN_HEIGHT - dervinData.rec.height * 2;
	dervinData.frame = 0;
	dervinData.updateTime = 1.0 / 12.0;
	dervinData.runningTime = 0.0;

	float rotation = {};

	bool collision = false;
	float rightLeft = 1.0;

	Rectangle destRec = {
			dervinData.pos.x,
			dervinData.pos.y,
			(dervinData.rec.width * scale),
			dervinData.rec.height * scale
	};

	SetTargetFPS(60);
	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(WHITE);

		const float dT = GetFrameTime();

		
		if (IsKeyDown(KEY_D))
		{


			// shift the screen the the left
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

		if (isOnGround(dervinData, WIN_HEIGHT))
		{
			// rect on ground
			velocity = 0;
			isInAir = false;
		}
		else
		{
			// apply gravity
			velocity += gravity * dT;
			isInAir = true;
		}

		if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
		{
			dervin = attackTexture;
			dervinData = updateAnimData(dervinData, dT, 7);
		}

		// jump check
		if (IsKeyPressed(KEY_SPACE) && !isInAir)
		{
			velocity += jumpVel;
		}
		dervinData.pos.y += velocity * dT;

		if (!isInAir)
		{
			if (IsKeyDown(KEY_D))
			{
				dervin = walkTexture;
				dervinData = updateAnimData(dervinData, dT, 8);
			}
			else if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
			{
				dervin = attackTexture;
				dervinData = updateAnimData(dervinData, dT, 7);
			}
			else
			{
				dervin = idleTexture;
				dervinData = updateAnimData(dervinData, dT, 3);
			}
		}

		Rectangle destRec = {
			dervinData.pos.x,
			dervinData.pos.y,
			(dervinData.rec.width * scale),
			dervinData.rec.height * scale
		};
		Vector2 origin = { 0.0, 0.0 };
		DrawTexturePro(dervin, dervinData.rec, destRec, origin, 0.0, WHITE);

		EndDrawing();
	}
	UnloadTexture(dervin);
	UnloadTexture(bg);
	CloseWindow();

}