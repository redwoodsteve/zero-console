#include <iostream>
#include <fstream>
#include <map>
#include "raylib.h"
#include "raymath.h"
#include "json.hpp"

using json = nlohmann::json;

const Color WHEEL_COLOR_NORMAL = BLUE; // color of text items which are not selected
const Color WHEEL_COLOR_SELECTED = WHITE; // color of selected item
const float WHEEL_FONT_SIZE_BASE_FACTOR = 0.5; // number to multiply font size for text rendered on the wheel

struct Game {
	std::string name;
	std::string path;
};

std::vector<Game> loadGames() { // load games from games.json into a vector, then return it
	std::ifstream f("games.json");
	json data = json::parse(f);
	std::vector<Game> games;

	for (auto& item : data) {
		games.push_back({ // push item to back of vector
			item["name"].get<std::string>(),
			item["path"].get<std::string>()
		});
	}
	return games;
}

float targetAngle = 0; // angle to interpolate to
int selected = 0; // selected game (from the vector)

// render the selector wheel
void renderWheel(float rotation, std::vector<Game> games, int circleX, int circleY, int radius, Font font) { // 0 degrees is right, 90 degrees is down, 180 is left, etc
	float spacing = (2.0f * PI) / games.size(); // calculate rotation spacing between items
	int numberOfGames = games.size();

	for (int i = 0; i < numberOfGames; i++) { // loop through every game
		float myAngle = rotation + (i * spacing) + PI; // get the angle which this text sprite should be rendered
		float x = circleX + radius * cosf(myAngle); // use trig to convert the angle to cartesian coordinates
		float y = circleY + radius * sinf(myAngle);

		float normalizedAngle = atan2f(sinf(myAngle - PI), cosf(myAngle - PI)); // angle between 0 and 360
		float sizeFactor = powf(1.0f - (std::abs(normalizedAngle) / PI), 2.0f); // size factor to multiply text size by

		// center the text
		Vector2 s = MeasureTextEx(font, games[i].name.c_str(), font.baseSize * sizeFactor * WHEEL_FONT_SIZE_BASE_FACTOR, 2);
		Vector2 pos = {x - s.x / 2, y - s.y / 2};

		// calculate the color of the current text
		Color currentColor = ColorLerp(WHEEL_COLOR_NORMAL, WHEEL_COLOR_SELECTED, std::powf(sizeFactor, 4.0f));
		//Color currentColor = {0, 0, (unsigned char)std::round(std::powf(sizeFactor, 4.0f) * 255), 255};

		// draw it :D
		DrawTextEx(font, games[i].name.c_str(), pos, static_cast<float>(font.baseSize) * sizeFactor * WHEEL_FONT_SIZE_BASE_FACTOR, 2, currentColor);
	}
}

// select the next game in the wheel
void selectNext(float& rotation, std::vector<Game> games) {
	float spacing = (2.0f * PI) / games.size();
	rotation += spacing;
	selected++;
	if (selected >= (int)games.size()) selected = 0;
}
// select the previous game in the wheel
void selectPrev(float& rotation, std::vector<Game> games) {
	float spacing = (2.0f * PI) / games.size();
	rotation -= spacing;
	selected--;
	if (selected < 0) selected = games.size() - 1;
}

// map of key bindings
std::map<KeyboardKey, void (*)(float&, std::vector<Game>)> keyBinds = {
	{KEY_UP, selectNext},
	{KEY_DOWN, selectPrev}
};

int main() {
	std::vector<Game> games = loadGames();

	int w = 480;
	int h = 320;
	InitWindow(w, h, "launcher");
	SetTargetFPS(60);

	int canvasW = w / 4;
	int canvasH = h / 4;
	RenderTexture2D canvas = LoadRenderTexture(canvasW, canvasH);

	Font mainFont = LoadFontEx("resources/Qaaxee.ttf", 32, 0, 250);

	Image blank = GenImageColor(canvasW, canvasH, WHITE); // blank texture so that background shader can work
	Texture2D backgroundTex = LoadTextureFromImage(blank);
	UnloadImage(blank);

	Shader backgroundShader = LoadShader(0, "resources/background.fs");

	float currentAngle = 0;

	while (!WindowShouldClose()) {
		currentAngle += (targetAngle - currentAngle) * 5.0f * GetFrameTime();

		for (auto& [key, bind] : keyBinds) {
			if (IsKeyPressed(key)) {
				bind(targetAngle, games);
			}
		}

		BeginTextureMode(canvas);
			ClearBackground(RAYWHITE);
			BeginShaderMode(backgroundShader);
				DrawTexture(backgroundTex, 0, 0, WHITE);
			EndShaderMode();
			
			renderWheel(currentAngle, games, canvasW, canvasH / 2, canvasW / 2, mainFont);
		EndTextureMode();

		BeginDrawing();
			DrawTexturePro(canvas.texture,
				Rectangle{0, 0, (float)canvas.texture.width, -(float)canvas.texture.height},
				Rectangle{0, 0, (float)w, (float)h},
				Vector2{0, 0}, 0.0f, WHITE
			);
		EndDrawing();
	}

	CloseWindow();

	return 0;
}