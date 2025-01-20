#ifndef RENDERER_H
#define RENDERER_H

class Renderer {
public:
    Renderer();
    ~Renderer();

    bool initialize();  // Initialize GLAD and OpenGL settings
    void render();      // Handle rendering logic
    void clear();       // Clear the screen

private:
    void setupOpenGL(); // Internal function for OpenGL setup
};

#endif // RENDERER_H
