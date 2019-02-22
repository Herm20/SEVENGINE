#ifndef APPLICATION_H_
#define APPLICATION_H_

class Application
{
public:
	Application();
	~Application();

	// Initialize core engine systems and resources
	void Init();

	// Start the engine
	void Run();

	// Cleanup for program exit
	void Exit();
};

#endif