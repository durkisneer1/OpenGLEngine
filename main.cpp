#include <KrakenEngine.hpp>

#include <vector>

int main()
{
    kn::window::init(800, 600, "DurkGL");
    kn::input::setRelativeMode(true);
    kn::time::Clock clock;

    kn::Camera camera({ 3.0f, 3.0f, 6.0f }, 75.0f);
    camera.yaw = 270.0f;
    camera.pitch = -35.0f;

    auto texture = kn::texture::load("cat", "../assets/close_cat.jpg");

    kn::Cube whiteCube(texture);

    kn::Cube purpleCube(texture);
    purpleCube.color = { 1.0f, 0.0f, 1.0f };
    purpleCube.pos = { 3.0f, 0.0f, 2.0f };
    purpleCube.scale = { 2.0f, 0.5f, 1.0f };

    kn::Cube yellowCube(texture);
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
