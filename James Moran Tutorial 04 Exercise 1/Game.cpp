// From bespoke header file(s):
#include "Game.h"
#include "Bitmap.h" // '04-01'

// Perform SDL initialisation:
Game::Game()
{
	// To make sure these pointers are null:
	M_Window = nullptr;
	M_Renderer = nullptr;

	// Initial initialisation:
	SDL_Init(SDL_INIT_VIDEO);
	TTF_Init(); // '04-02'

	// Initilise the window:
	M_Window = SDL_CreateWindow(
		"First SDL Window", // Title
		250, // Initial x position
		50, // Initial y position
		640, // Width, in pixels
		480, // Height, in pixels
		0 // Windows behavior flags go here (when required) 
		);

	if (!M_Window)
	{
		printf("Window initialisation failed: %s\n", SDL_GetError());
		printf("Press any key to continue...\n");
		getchar();
		return;
	}

	// Initilise the renderer:
	M_Renderer = SDL_CreateRenderer(
		M_Window, // The custom window (as delcared in game.h)
		-1, // The specific rendering driver to use (-1 to the first index
		// that supports the specified flags
		0 // Renderer behavior flags
		);

	if (!M_Renderer)
	{
		printf("Renderer initialisation failed: %s\n", SDL_GetError());
		printf("Press any key to continue...\n");
		getchar();
		return;
	}

	// Initilise the respective bitmaps:
	//M_Monster = new Bitmap(M_Renderer, "assets/monster.bmp", 100, 100); // '04-01'
	//M_MonsterWithTransparency = new Bitmap(M_Renderer, "assets/monsterTrans.bmp", 200, 100); // '04-01'
	M_MonsterWithTransparencyThatHasKey = new Bitmap(M_Renderer, "assets/monsterTrans.bmp", 300, 100, true);

	// Set-up font:
	M_PSmallFont = TTF_OpenFont("assets/DejaVuSans.tff", 15); // '04-02'
	M_PLargeFont = TTF_OpenFont("assets/DejaVuSans.tff", 50); // '04-02'
}

// Clean up:
Game::~Game()
{
	// Keep in mind that one calls the respective destroy functions
	// in the reverse order of initialisation:

	// Initilise Font destruction:
	TTF_CloseFont(M_PLargeFont); // '04-02'
	TTF_CloseFont(M_PSmallFont); // '04-02'

	// Initilise Bitmap destruction:
	if (M_MonsterWithTransparencyThatHasKey) // '04-01'
	{
		delete M_MonsterWithTransparencyThatHasKey;
	}

	if (M_MonsterWithTransparency) // '04-01'
	{
		delete M_MonsterWithTransparency;
	}

	if (M_Monster) // '04-01'
	{
		delete M_Monster;
	}

	// Initilise Renderer and Window destruction:
	if (M_Renderer)
	{
		SDL_DestroyRenderer(M_Renderer);
	}

	if (M_Window)
	{
		SDL_DestroyWindow(M_Window);
	}
}

// Clear and present the renderer:
void Game::ClearRenderer()
{
	SDL_RenderClear(M_Renderer);
}

void Game::PresentRenderer()
{
	SDL_RenderPresent(M_Renderer);
}

// Wait for a certain quantity of time:
void Game::Delay(Uint32 Milliseconds)
{
	SDL_Delay(Milliseconds);
}

void Game::CheckEvents()
{

}

/** For Tutorial 4, Exercise 2: */
void Game::UpdateText(std::string Message, int XPosition, int YPosition, TTF_Font * FontStyle, SDL_Color FontColour)
{
	SDL_Surface* TextSurface = nullptr;
	SDL_Texture* TextTexture = nullptr;

	int TextWidth = 0;
	int TextHeight = 0;

	// Initilise the Surface:
	TextSurface = TTF_RenderText_Solid(FontStyle, Message.c_str(), FontColour);
	// An error occurred:
	if (!TextSurface)
	{
		printf("Font Surface not loaded! \n");
		printf("%s\n", SDL_GetError());
	}
	// TextSurface is valid...
	else
	{
		// Initilise the Texture:
		TextTexture = SDL_CreateTextureFromSurface(M_Renderer, TextSurface);

		// Validation:
		if (!TextTexture)
		{
			printf("Font Texture not loaded!");
			printf("%s\n", SDL_GetError());
		}
		else
		{
			SDL_QueryTexture(TextTexture, NULL, NULL, &TextWidth, &TextHeight);
			SDL_Rect TextRectangle = { XPosition, YPosition, TextWidth, TextHeight };

			SDL_RenderCopy(M_Renderer, TextTexture, NULL, &TextRectangle);
		}
	}

	// Handle cleaning up:
	if (TextTexture)
	{
		SDL_DestroyTexture(TextTexture);
	}

	if (TextSurface)
	{
		SDL_FreeSurface(TextSurface);
	}
}

// Set the display colour as appropriate:
void Game::SetDisplayColour(Uint8 Red, Uint8 Blue, Uint8 Green, Uint8 Alpha)
{
	if (M_Renderer)
	{
		// Set the draw colour to each respective RGBA component (from parameter values):
		int Result = SDL_SetRenderDrawColor(
			M_Renderer,
			Red, // RGB A, for Alpha 
			Green,
			Blue,
			Alpha
			);

		// Clear the window displayed using MRenderer
		// (with its respective draw colour):
		ClearRenderer();

		// Present this to the user:
		PresentRenderer();

		// Allow a 5 second delay for the user to see the result:
		//Delay(5000); // As per Sleep(), parse the time in milliseconds
	}
}

// Blank for now:
void Game::Update(int NewPositionX, int NewPositionY)
{
	CheckEvents();

	// Clear the display (using the currently set colour):
	SDL_RenderClear(M_Renderer);

	// Display the game's bitmaps:
	//M_Monster->Draw();
	//M_MonsterWithTransparency->Draw();
	M_MonsterWithTransparencyThatHasKey->Draw(NewPositionX, NewPositionY);

	// Show Text in the viewport:
	UpdateText("Small Red", 50, 10, M_PSmallFont, { 255, 0, 0 }); // '04-02'
	UpdateText("Small Blue", 50, 40, M_PSmallFont, { 0, 255, 0 }); // '04-02'

	char LargeWhiteCharacterString[] = "Large White";
	UpdateText(LargeWhiteCharacterString, 50, 140, M_PLargeFont, { 255, 255, 255 }); // '04-02'
	
	std::string LargeGreenCharacterString = "Large Green";
	UpdateText(LargeGreenCharacterString, 50, 70, M_PLargeFont, { 0, 255, 0 }); // '04-02'

	int TestNumber = 1234;
	std::string TestNumberLabel = "Text Number: ";
	TestNumberLabel += std::to_string(TestNumber);
	UpdateText(TestNumberLabel, 50, 210, M_PLargeFont, { 255, 255, 255 }); // '04-02'

	// Present this:
	PresentRenderer();

	// To pause for approximately 1/60th of a second:
	Delay(16);
}