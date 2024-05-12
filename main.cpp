#include <KrakenEngine.hpp>

#include <vector>

int main()
{
    kn::window::init(800, 600, "DurkGL");
    kn::input::setRelativeMode(true);
    kn::time::Clock clock;
    kn::Camera camera({ -2.0f, 1.5f, -2.0f }, 75.0f);
    camera.yaw = 45.0f;
    camera.pitch = -30.0f;
    kn::Cube cube;
    kn::Cube otherCube(
        { 3.0f, 0.0f, 2.0f },
        { 15.0f, 15.0f, 30.0f },
        { 2.0f, 1.0f, 1.0f },
        { 255, 0, 0 }
    );

    std::vector<kn::KEYS> forward = { kn::S_w, kn::S_UP };
    std::vector<kn::KEYS> right = { kn::S_d, kn::S_RIGHT };
    std::vector<kn::KEYS> backward = { kn::S_s, kn::S_DOWN };
    std::vector<kn::KEYS> left = { kn::S_a, kn::S_LEFT };

    bool done = false;
    while (!done)
    {
        double deltaTime = clock.tick(240);
        glm::vec2 inputDir = kn::input::getVector(forward, right, backward, left);

        for (const kn::Event& event : kn::window::getEvents())
        {
            if (event.type == kn::QUIT)
                done = true;
            else if (event.type == kn::KEYDOWN)
                if (event.key.keysym.sym == kn::K_ESCAPE)
                    done = true;
        }

        kn::window::cls();

        camera.update(deltaTime, inputDir);
        cube.render();
        otherCube.render();

        kn::window::flip();
    }
    
    kn::window::quit();
    return EXIT_SUCCESS;
}
