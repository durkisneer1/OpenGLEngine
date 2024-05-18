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

    shaderPtr->setVec3("light.position", { 2.0f, 2.0f, 2.0f });
    shaderPtr->setVec3("light.ambient", { 0.2f, 0.2f, 0.2f });
    shaderPtr->setVec3("light.diffuse", { 0.5f, 0.5f, 0.5f });
    shaderPtr->setVec3("light.specular", { 1.0f, 1.0f, 1.0f });

    kn::Camera camera({ 3.0f, 3.0f, 6.0f }, 75.0f);
    camera.yaw = 270.0f;
    camera.pitch = -35.0f;

    auto boxDiffuse = kn::texture::load("box diffuse", "../assets/container_diffuse.png");
    auto boxSpecular = kn::texture::load("box specular", "../assets/container_specular.png");

    kn::Cube box;
    box.diffuse = boxDiffuse;
    box.specular = boxSpecular;

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

        for (int z = 0; z < 10; z++)
        {
            for (int x = 0; x < 10; x++)
            {
                box.pos.x = x * 2;
                box.pos.z = z * 2;
                box.render();
            }
        }

        kn::window::flip();
    }
    
    return EXIT_SUCCESS;
}
