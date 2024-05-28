#include <KrakenEngine.hpp>

#include <vector>
#include <iostream>

int main(int argc, char **argv)
{
    kn::window::init(1200, 800, "DurkGL");
    kn::input::setRelativeMode(true);
    kn::time::Clock clock;

    auto shaderPtr = kn::shader::get("default");

    kn::Camera camera({ 3.0f, 3.0f, 6.0f }, 75.0f);
    camera.yaw = 270.0f;
    camera.pitch = -35.0f;

    glm::vec3 pointLightPositions[] = {
        glm::vec3( 0.7f,  2.2f,  2.0f),
        glm::vec3( 2.3f, 3.3f, -4.0f),
        glm::vec3(-4.0f,  2.0f, -12.0f),
        glm::vec3( 0.0f,  1.0f, -3.0f)
    };

    for (int i = 0; i < 4; i++)
    {
        auto pointLight = kn::light::createPointLight();
        pointLight->setPos(pointLightPositions[i]);
    }

    auto flashlight = kn::light::createSpotLight();
    flashlight->setCutOff(30.0f);
    flashlight->setOuterCutOff(35.0f);

    auto boxDiffuse = kn::texture::load("box diffuse", kn::DIFFUSE, "../assets/container_diffuse.png");
    auto boxSpecular = kn::texture::load("box specular", kn::SPECULAR, "../assets/container_specular.png");

    kn::Cube box;
    box.diffuse = boxDiffuse;
    box.specular = boxSpecular;
    box.pos.y = -4.0f;

    kn::Model backpack("../assets/backpack/backpack.obj");

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
        flashlight->setPos(camera.pos);
        flashlight->setDir(camera.front);

        for (int z = -5; z < 6; z++)
        {
            for (int x = -5; x < 5; x++)
            {
                box.pos.x = x * 2;
                box.pos.z = z * 2;
                box.render();
            }
        }
        backpack.render();

        kn::window::flip();
    }

    return EXIT_SUCCESS;
}
