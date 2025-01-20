#ifndef APPLICATION_H
#define APPLICATION_H

class WindowManager;
class Renderer; // Forward declare Renderer

class Application {
public:
    Application();
    ~Application();

    void start(); // Start the application
    void run();   // Main loop

private:
    WindowManager* windowManager;
    Renderer* renderer; // Add renderer as a private member
};

#endif // APPLICATION_H
