#include <stdlib.h>
 
#define WINDOW_W 1920
#define WINDOW_H 1080
 
#ifdef __ANDROID__
    #include <android/log.h>
        #include <GLES/gl.h>
        #define DIR_SEP "/"
        #define DIR_CUR "/sdcard/"
        #define glOrtho(a,b,c,d,e,f) glOrthof(a,b,c,d,e,f) ///FIXME
#else
        #include <stdio.h>
        #include <GL/gl.h>
        #include <GL/glu.h>
        #define DIR_CUR ""
        #define DIR_SEP "/"
#endif
 
#define PATH(filename) DIR_CUR "data" DIR_SEP filename
#define ISPWR2(n) !(n&(n-1))
 
#include "SDL.h"
#include "SDL_image.h"
 
 
static SDL_Window* window;
static SDL_GLContext context;
static GLuint texture;
static SDL_Event event;
static bool running = true;
static int angle;
 
int startup();
int loadTexture(const char* filepath);
void draw();
int shutdown();
 

static void checkGlError(const char* op) {
    for (GLint error = glGetError(); error; error
            = glGetError()) {
__android_log_print(ANDROID_LOG_DEBUG, "CHUUUY", "after %s() glError (0x%x)\n", op, error);
    }
}
 
int main(int argc, char** argv)
{
        // Initialise SDL and OpenGL
        if(!startup())
                return EXIT_FAILURE;
    // Main loop
    while(running)
    {
checkGlError("checking glError");
                // Draw the texture
                draw();
 
                // Wait
                SDL_Delay(50);
 
                // Spin image
                angle = (angle+2) % 360;
 
                // Check for exit
                while (SDL_PollEvent(&event))
                        if(event.type == SDL_QUIT)
                                running = false;
    }
 
    // Clean up
    if(!shutdown())
        return EXIT_FAILURE;
 
    // Success !
    return EXIT_SUCCESS;
}
 
int startup()
{
    // Initialize SDL
        if(SDL_Init(SDL_INIT_VIDEO) < 0)
                return 0;
        // Open the window where we will draw
        window = SDL_CreateWindow("OpenGL Test",
                           SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                           WINDOW_W, WINDOW_H, SDL_WINDOW_OPENGL|SDL_WINDOW_SHOWN);

    // Create the OpenGL context for the window we just opened
    context = SDL_GL_CreateContext(window);
    SDL_GL_MakeCurrent(window, context);
    // Configure SDL for OpenGL or GLES 1.1
    SDL_GL_SetSwapInterval(1); // 1 = use vertical synchronisation (vsync)
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

    // Configure OpenGL propre
    glClearColor(0, 255, 255, 255);
    glEnable(GL_TEXTURE_2D);
    glViewport(0, 0, WINDOW_W, WINDOW_H);
    glMatrixMode(GL_PROJECTION);
    glOrtho(0, WINDOW_W, WINDOW_H, 0, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Load the texture to draw
    if(!loadTexture("image.png"))
        return 0;
    // Success
    return 1;
}
 
int loadTexture(const char* filepath)
{
    // Local variables for extracting properties about the image
    GLuint n_colours = 0;
    GLenum format = (GLenum) NULL;

    // Load the image using SDL_image
        SDL_Surface* surface = IMG_Load("image.png");
        if(!surface)
        return 0;
 
    // Make sure the image length and width are powers of 2
    if (!ISPWR2(surface->w) || !ISPWR2(surface->h))
        return 0;

        //get number of channels in the SDL surface
    n_colours = surface->format->BytesPerPixel;
    switch(n_colours)
    {
        case 3: format = GL_RGB; break;
        case 4: format = GL_RGBA; break;
        default: return 0; break;
    }

    // Request an OpenGL texture handle
    glGenTextures(1, &texture);
 
    // Bind the texture object to the current block
    glBindTexture(GL_TEXTURE_2D, texture);
 
    // Set the texture’s properties
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, format, surface->w, surface->h, 0,
                    format, GL_UNSIGNED_BYTE, surface->pixels);
 
    // The original bitmap is no longer needed
        SDL_FreeSurface(surface);
 
        // Success!
        return 1;
}
 
void draw()
{
    // Clear the entire screen
    glClear(GL_COLOR_BUFFER_BIT);
 
    // Set up position, rotation, colour
    glTranslatef(WINDOW_W/2, WINDOW_H/2, 0.0);
    glRotatef(angle, 0.0, 0.0, 1.0);
 
    // Bind the texture to which subsequent calls refer to
    glBindTexture(GL_TEXTURE_2D, texture);
 
    // Start drawing texture
        glEnableClientState(GL_VERTEX_ARRAY);
        glEnableClientState(GL_TEXTURE_COORD_ARRAY);
        GLfloat size[9], coords[9];
    glVertexPointer(3, GL_FLOAT, 0, size);
        glTexCoordPointer(2, GL_FLOAT, 0, coords);
 
    // Top-left triangle
    // Top-left triangle
		size[0]=-256;
		size[1]=-256;
		size[2]=0;

		size[3]=256;
		size[4]=-256;
		size[5]=0;

		size[6]=256;
		size[7]=256;
		size[8]=0;

        //size = {-16,-16,0, 16,-16,0, 16,16,0}; ///FIXME
		coords[0]=0;
		coords[1]=0;

		coords[2]=1;
		coords[3]=0;

		coords[4]=1;
		coords[5]=1;

        //coords = {0,0, 1,0, 1,1}; ///FIXME
        glDrawArrays(GL_TRIANGLES, 0, 3);
 
    // Bottom-right triangle
		size[0]=-256;
		size[1]=-256;
		size[2]=0;

		size[3]=-256;
		size[4]=256;
		size[5]=0;

		size[6]=256;
		size[7]=256;
		size[8]=0;
        //size = {-16,-16,0, -16,16,0, 16,16,0}; ///FIXME
		coords[0]=0;
		coords[1]=0;

		coords[2]=0;
		coords[3]=1;

		coords[4]=1;
		coords[5]=1;
        //coords = {0,0, 0,1, 1,1}; ///FIXME
        glDrawArrays(GL_TRIANGLES, 0, 3);
 
    // Stop drawing texture
        glDisableClientState(GL_VERTEX_ARRAY);
        glDisableClientState(GL_TEXTURE_COORD_ARRAY);
 
    // Reset back to the origin
    glLoadIdentity();
 
    // Flip the buffers to update the screen
    SDL_GL_SwapWindow(window);
}
 
int shutdown()
{
    // Free ressources
    glDeleteTextures(1, &texture);
 
    // Destory application display and control structures
    SDL_GL_MakeCurrent(NULL, NULL);
    SDL_GL_DeleteContext(context);
        SDL_DestroyWindow(window);
 
        // Shut down SDL
        SDL_Quit();
 
        // Success!
        return EXIT_SUCCESS;
}
