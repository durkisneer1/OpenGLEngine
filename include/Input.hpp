#pragma once

#include <vector>
#include <glm/glm.hpp>

#include "Constants.hpp"

namespace kn
{
namespace input
{

glm::vec2 getMousePos();

glm::vec2 getMouseRel();

int getMouseButtonPressed();

const Uint8* getKeysPressed();

void setRelativeMode(bool state);

bool getRelativeMode();

glm::vec2 getVector(
    const std::vector<KEYS>& up = {}, const std::vector<KEYS>& right = {},
    const std::vector<KEYS>& down = {}, const std::vector<KEYS>& left = {}
);

}  // namespace input
}  // namespace kn
