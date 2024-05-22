#include <KrakenEngine.hpp>

#include <vector>
#include <iostream>

int main(int argc, char **argv)
{
    kn::window::init(1200, 800, "DurkGL");
    kn::input::setRelativeMode(true);
    kn::time::Clock clock;

    auto shaderPtr = kn::shader::get("default");
    shaderPtr->use();

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
        std::string baseName = "pointLights[" + std::to_string(i) + "].";
        shaderPtr->setVec3(baseName + "position", pointLightPositions[i]);
        shaderPtr->setFloat(baseName + "constant", 1.0f);
        shaderPtr->setFloat(baseName + "linear", 0.09f);
        shaderPtr->setFloat(baseName + "quadratic", 0.032f);
        shaderPtr->setVec3(baseName + "ambient", { 0.05f, 0.05f, 0.05f });
        shaderPtr->setVec3(baseName + "diffuse", { 0.8f, 0.8f, 0.8f });
        shaderPtr->setVec3(baseName + "specular", { 1.0f, 1.0f, 1.0f });
    }

    kn::DirectionalLight sun;
    sun.direction = { -0.3, -1.0, -0.2};
    sun.update();

    shaderPtr->setVec3("spotLight.ambient", { 0.0f, 0.0f, 0.0f });
    shaderPtr->setVec3("spotLight.diffuse", { 1.0f, 1.0f, 1.0f });
    shaderPtr->setVec3("spotLight.specular", { 1.0f, 1.0f, 1.0f });
    shaderPtr->setFloat("spotLight.constant", 1.0f);
    shaderPtr->setFloat("spotLight.linear", 0.09f);
    shaderPtr->setFloat("spotLight.quadratic", 0.032f);
    shaderPtr->setFloat("spotLight.cutOff", glm::cos(glm::radians(30.0f)));
    shaderPtr->setFloat("spotLight.outerCutOff", glm::cos(glm::radians(35.0f)));

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
        shaderPtr->setVec3("spotLight.position", camera.pos);
        shaderPtr->setVec3("spotLight.direction", camera.front);

        for (int z = -5; z < 6; z++)
        {
            for (int x = -5; x < 5; x++)
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
