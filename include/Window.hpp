#pragma once

#include <string>
#include <vector>

#include <SDL.h>

#include "Constants.hpp"


namespace kn
{
namespace window
{

void init(int screenWidth, int screenHeight, const std::string &windowTitle = "Kraken Window");

void toggleWireframe();

int getWidth();

int getHeight();

void quit();

const std::vector<SDL_Event>& getEvents();

void cls(Color color = { 20, 20, 20, 255 });

void flip();

void setTitle(const std::string& newTitle);

std::string getTitle();

}
}
