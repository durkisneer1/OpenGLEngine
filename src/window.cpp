#include "Window.hpp"
#include "Shader.hpp"
#include "BufferObject.hpp"
#include "VertexArray.hpp"
#include "Texture.hpp"

#include <glad/glad.h>
#include <stb/stb_image.h>

#include <iostream>


namespace kn {
namespace window {

static SDL_Window* _window;
static SDL_GLContext _ctx;
static bool _wireframeMode = false;
static bool _running = true;
static Event _event;
static std::vector<SDL_Event> _events;


void init(int screenWidth, int screenHeight, const std::string &windowTitle)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
        std::cout << "Error initializing SDL: " << SDL_GetError() << std::endl;
    
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 16);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);

    _window = SDL_CreateWindow(
        windowTitle.c_str(),
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        screenWidth, screenHeight,
        SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE
    );
    if (_window == nullptr)
    {
        std::cout << "Error creating window: " << SDL_GetError() << std::endl;
        SDL_Quit();
    }

    _ctx = SDL_GL_CreateContext(_window);
    if (_ctx == nullptr)
    {
        std::cout << "Error creating OpenGL context: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(_window);
    }
    SDL_GL_MakeCurrent(_window, _ctx);

    if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress))
        std::cout << "Failed to initialized GLAD" << std::endl;

    glEnable(GL_DEPTH_TEST);
    glViewport(0, 0, screenWidth, screenHeight);

    stbi_set_flip_vertically_on_load(true);

    auto shaderPtr = shader::load("../shaders/", "default");

    SDL_AddEventWatch(updateWindowCallback, nullptr);
}

const std::vector<SDL_Event>& getEvents()
{
    if (_window == nullptr)
        std::cout << "Cannot get events before initializing the window" << std::endl;

    _events.clear();
    while (SDL_PollEvent(&_event))
        _events.push_back(_event);

    return _events;
}

void toggleWireframe()
{
    _wireframeMode = !(_wireframeMode);
    if (_wireframeMode)
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    else
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

int getWidth()
{
    int w;
    SDL_GetWindowSize(_window, &w, nullptr);
    return w;
}

int getHeight()
{
    int h;
    SDL_GetWindowSize(_window, nullptr, &h);
    return h;
}

void quit()
{
    _running = false;

    if (_ctx != nullptr)
        SDL_GL_DeleteContext(_ctx);
    if (_window != nullptr)
        SDL_DestroyWindow(_window);

    _events.clear();
    kn::shader::releaseAll();
    kn::vao::releaseAll();
    kn::buffer::releaseAll();
    kn::texture::releaseAll();

    if (SDL_WasInit(SDL_INIT_EVERYTHING) & SDL_INIT_EVERYTHING)
        SDL_Quit();
}

void cls(Color color)
{
    glClearColor(
        color.r / 255.0f,
        color.g / 255.0f,
        color.b / 255.0f,
        color.a / 255.0f
    );
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void flip()
{
    SDL_GL_SwapWindow(_window);
}

void setTitle(const std::string& newTitle)
{
    if (_window == nullptr)
        std::cout << "Cannot set title before creating the window" << std::endl;

    if (newTitle.empty())
    {
        std::cout << "Cannot set title to empty string" << std::endl;
        return;
    }

    if (newTitle.size() > 255)
    {
        std::cout << "Cannot set title to string longer than 255 characters" << std::endl;
        return;
    }

    SDL_SetWindowTitle(_window, newTitle.c_str());
}

std::string getTitle()
{
    if (_window == nullptr)
        std::cout << "Cannot get title before creating the window" << std::endl;

    return std::string(SDL_GetWindowTitle(_window));
}

bool isRunning()
{
    return _running;
}

int updateWindowCallback(void* data, Event* e)
{
    if (e->type == WINDOWEVENT)
    {
        if (e->window.event == SDL_WINDOWEVENT_RESIZED)
            glViewport(0, 0, e->window.data1, e->window.data2);
    }
    else if (e->type == QUIT)
    {
        quit();
    }
        
    return 0;
}

}  // window namespace
}  // kn namespace
