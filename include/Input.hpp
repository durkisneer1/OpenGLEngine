#pragma once

#include <vector>
#include <glm/glm.hpp>

#include "Constants.hpp"

namespace kn {
namespace mouse {

glm::vec2 getPos();

glm::vec2 getRel();

int getPressed();

void setRelativeMode(bool state);

bool getRelativeMode();

}  // namespace mouse

namespace key {

const Uint8* getPressed();

}  // namespace key

namespace input {

glm::vec2 getVector(
    const std::vector<KEYS>& up = {}, const std::vector<KEYS>& right = {},
    const std::vector<KEYS>& down = {}, const std::vector<KEYS>& left = {}
);

}  // namespace input
}  // namespace kn
