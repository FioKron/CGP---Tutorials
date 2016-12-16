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

	// Initilise the window:
	M_Window = SDL_CreateWindow(
		"Monster Rampage", // Title
		250, // Initial x position
		50, // Initial y position
		1920, // Width, in pixels
		1080, // Height, in pixels
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
	//M_MonsterWithTransparencyThatHasKey = new Bitmap(M_Renderer, "assets/monsterTrans.bmp", 300, 100, true);
	
	// Set up the monster collection:
	Monster* FirstMonster = new Monster(M_Renderer, 100, 100);
	Monster* SecondMonster = new Monster(M_Renderer, 1000, 1000);
	//GameEntity* Hero = new GameEntity(M_Renderer, 500, 500,)

	MonsterCollection.push_back(FirstMonster);
	MonsterCollection.push_back(SecondMonster);
}

// Clean up:
Game::~Game()
{
	// Keep in mind that one calls the respective destroy functions
	// in the reverse order of initialisation:

	// Initilise Bitmap destruction:
	/**if (M_MonsterWithTransparencyThatHasKey) // '04-01'
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
	*/

	// For cleaning up all Monsters in MonsterCollection:
	for each (Monster* ThisMonster in MonsterCollection)
	{
		if (ThisMonster)
		{
			delete ThisMonster;
			ThisMonster = nullptr;
		}
	}

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
void Game::Update()
{
	CheckEvents();

	// Clear the display (using the currently set colour):
	SDL_RenderClear(M_Renderer);

	// Display the game's bitmaps:

	// Drawing each monster:
	for each (Monster* MonsterToUpdate in MonsterCollection)
	{
		if (MonsterToUpdate)
		{
			MonsterToUpdate->Draw(MonsterToUpdate->GetEntityXPosition(), MonsterToUpdate->GetEntityYPosition());
		}		
	}

	// Present this:
	PresentRenderer();

	// To pause for approximately 1/60th of a second:
	Delay(16);
}