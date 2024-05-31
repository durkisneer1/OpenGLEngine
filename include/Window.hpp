#pragma once

#include <string>
#include <vector>
#include <glm/glm.hpp>

#include "Constants.hpp"

namespace kn {
namespace window {

void init(const glm::vec2& size, const std::string &windowTitle = "Kraken Window");

void toggleWireframe();

int getWidth();

int getHeight();

void quit();

const std::vector<SDL_Event>& getEvents();

void clear(Color color = { 0, 0, 0, 255 });

void flip();

void setTitle(const std::string& newTitle);

std::string getTitle();

bool isOpen();

int updateWindowCallback(void* data, Event* e);

}  // namespace window
}  // namespace kn
