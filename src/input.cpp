#include "Input.hpp"
#include <algorithm>
#include <iostream>

namespace kn
{
namespace input
{

glm::vec2 getMousePos()
{
    int x, y;
    SDL_GetMouseState(&x, &y);
    return {(float)x, (float)y};
}

glm::vec2 getMouseRel()
{
    int x, y;
	SDL_GetRelativeMouseState(&x, &y);
    return {(float)x, (float)y};
}

const int getMouseButtonPressed()
{
    return SDL_GetMouseState(nullptr, nullptr);
}

const Uint8* getKeysPressed()
{
    return SDL_GetKeyboardState(nullptr);
}

void setRelativeMode(bool state)
{
    SDL_SetRelativeMouseMode(state ? SDL_TRUE : SDL_FALSE);
}

bool getRelativeMode()
{
    return SDL_GetRelativeMouseMode();
}

glm::vec2 getVector(const std::vector<KEYS>& up, const std::vector<KEYS>& right,
                    const std::vector<KEYS>& down, const std::vector<KEYS>& left)
{
    const Uint8* keys = getKeysPressed();
    glm::vec2 vector = glm::vec2(0.0f);

    if (std::any_of(up.begin(), up.end(), [&](auto scancode) { return keys[scancode]; }))
        vector.y += 1.0f;
    if (std::any_of(right.begin(), right.end(), [&](auto scancode) { return keys[scancode]; }))
        vector.x += 1.0f;
    if (std::any_of(down.begin(), down.end(), [&](auto scancode) { return keys[scancode]; }))
        vector.y -= 1.0f;
    if (std::any_of(left.begin(), left.end(), [&](auto scancode) { return keys[scancode]; }))
        vector.x -= 1.0f;

    if (glm::length(vector) > 1.0f)
        vector = glm::normalize(vector);

    return vector;
}

}  // namespace input
}  // namespace kn
