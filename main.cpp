#include <KrakenEngine.hpp>

#include <vector>
#include <iostream>

int main()
{
    kn::window::init(800, 600, "DurkGL");
    kn::input::setRelativeMode(true);
    kn::time::Clock clock;

    auto shaderPtr = kn::shader::get("default");
    shaderPtr->use();
    shaderPtr->setVec3("light.position", { 0.0f, 0.0f, 0.0f });
    shaderPtr->setVec3("light.ambient", { 0.2f, 0.2f, 0.2f });
    shaderPtr->setVec3("light.diffuse", { 0.5f, 0.5f, 0.5f });
    shaderPtr->setVec3("light.specular", { 1.0f, 1.0f, 1.0f });

    kn::Camera camera({ 3.0f, 3.0f, 6.0f }, 75.0f);
    camera.yaw = 270.0f;
    camera.pitch = -35.0f;

    auto catFace = kn::texture::load("cat face", "../assets/close_cat.jpg");
    // auto catGrip = kn::texture::load("cat grip", "../assets/cat_grip.jpg");

    kn::Cube whiteCube(catFace);
    whiteCube.pos = { -2.0f, -0.5f, 2.0f };

    kn::Cube purpleCube;
    purpleCube.color = { 1.0f, 0.0f, 1.0f };
    purpleCube.pos = { 3.0f, 0.0f, 2.0f };
    purpleCube.scale = { 2.0f, 0.5f, 1.0f };

    kn::Cube yellowCube;
    yellowCube.color = { 1.0f, 1.0f, 0.0f };
    yellowCube.rot = { 15.0f, -30.0f, -10.0f };
    yellowCube.pos = { -3.0f, 2.0f, -1.0f };
    yellowCube.scale = { 0.5f, 1.2f, 4.0f };

    std::vector<kn::KEYS> forward = { kn::S_w, kn::S_UP };
    std::vector<kn::KEYS> right = { kn::S_d, kn::S_RIGHT };
    std::vector<kn::KEYS> backward = { kn::S_s, kn::S_DOWN };
    std::vector<kn::KEYS> left = { kn::S_a, kn::S_LEFT };

    while (kn::window::isRunning())
    {
        double deltaTime = clock.tick(240);
        glm::vec2 inputDir = kn::input::getVector(forward, right, backward, left);
        camera.update(deltaTime, inputDir);

        for (const kn::Event& e : kn::window::getEvents())
            if (e.type == kn::KEYDOWN)
            {
                if (e.key.keysym.sym == kn::K_ESCAPE)
                    kn::window::quit();
                else if (e.key.keysym.sym == kn::K_r)
                    kn::input::setRelativeMode(!kn::input::getRelativeMode());
            }

        kn::window::cls();

        whiteCube.render();
        purpleCube.render();
        yellowCube.render();

        kn::window::flip();
    }
    
    return EXIT_SUCCESS;
}
