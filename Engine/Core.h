#pragma once

class Game;

class Core final
{
public:
	explicit Core(const Window& window);
	Core& operator=(const Core& rhs) = delete;
	Core& operator=(Core&& rhs) = delete;
	Core(const Core& rhs) = delete;
	Core(Core&& rhs) = delete;
	~Core();

	void Run(Game* game);
	void ClearBackground( );

private:
	// DATA MEMBERS
	// The window properties
	const Window m_Window;
	// The window we render to
	SDL_Window* m_pWindow;
	// OpenGL context
	SDL_GLContext m_pContext;
	// Init info
	bool m_Initialized;
	// Prevent timing jumps when debugging
	const float m_MaxElapsedSeconds;
	
	// FUNCTIONS
	void Initialize( );
	void Cleanup( );
};
