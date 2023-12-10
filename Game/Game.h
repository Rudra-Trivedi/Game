#pragma once

// Gamestate Enum: To signify current GameState
enum class GameState
{
	PLAY,
	EXIT
};



class Game
{
public:

	Game();
	~Game();

	// Calls Init and starts the game loop 
	void Run();
	
private:

	// Handles init stuff 
	void InitGame();
	// Polls for inputs and SDL_Events
	void ProcessInput();
	// Game loop
	void GameLoop();
	// Draw Game
	void DrawGame();

	// Pointer to the SDL_Window being created
	class SDL_Window* window;
	// Gamestate enum object 
	GameState gameState;
	// SDL event for polling inputs 
	

};

