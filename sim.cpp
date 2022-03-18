#include "sim.h"
#include<iostream>
#include <stdlib.h>

const int Sim::numParticles = 10;

Sim::Sim() : options(Options()), container(Container(0.2f, 0, 0.0000001f)) {
    this->win.create(sf::VideoMode(SIZE * SCALE, SIZE * SCALE),
                     "Euler fluid simulation - Github: https://github.com/driema/euler-fluid-cpp",
                     sf::Style::Titlebar | sf::Style::Close);
}

Sim::~Sim() {}

void Sim::Setup() {}

void Sim::Run() {
    this->Setup();
    sf::Vector2i previousMouse = sf::Mouse::getPosition(this->win);
    sf::Vector2i currentMouse = sf::Mouse::getPosition(this->win);

    while (this->win.isOpen()) {
        sf::Event e;
        while (this->win.pollEvent(e)) {
            switch (e.type) {
                case sf::Event::Closed:
                    this->win.close();
                    break;
                case sf::Event::KeyReleased:
                    if (e.key.code == sf::Keyboard::Key::C) {
                        Color c = (this->options.GetColor() == Color::Default) ?
                                  Color::Hsb : (this->options.GetColor() == Color::Hsb) ?
                                               Color::Velocity : Color::Default;

                        this->options.SetColor(c);
                    }
                    break;
                default:
                    break;
            }
        }

        this->container.AddDensity(500. / SCALE, 300. / SCALE, 200);

//        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
//            this->container.AddDensity(currentMouse.y / SCALE, currentMouse.x / SCALE, 200);
//
//        currentMouse = sf::Mouse::getPosition(this->win);
//
//        float amountX = currentMouse.x - previousMouse.x;
//        float amountY = currentMouse.y - previousMouse.y;
//		this->container.AddVelocity(currentMouse.y/SCALE, currentMouse.x/SCALE, amountY / 10, amountX / 10);

        float wind = 1 + 0.1 * (float(rand()) / RAND_MAX);;
//        this->container.AddVelocity((500 - 200.) / SCALE, 100. / SCALE, 0. / 10, 0.4 * wind / 100); // smoke in wind
//        this->container.AddVelocity((500 - 180.) / SCALE, 100. / SCALE, 0. / 10, 0.6 * wind / 100); // smoke in wind
//        this->container.AddVelocity((500 - 160.) / SCALE, 100. / SCALE, 0. / 10, 0.8 * wind / 100); // smoke in wind
//        this->container.AddVelocity((500 - 140.) / SCALE, 100. / SCALE, 0. / 10, 1.0 * wind / 100); // smoke in wind
//        this->container.AddVelocity((500 - 120.) / SCALE, 100. / SCALE, 0. / 10, 1.2 * wind / 100); // smoke in wind
//        this->container.AddVelocity((500 - 100.) / SCALE, 100. / SCALE, 0. / 10, 1.0 * wind / 100); // smoke in wind
//        this->container.AddVelocity((500 - 80.) / SCALE, 100. / SCALE, 0. / 10, 0.8 * wind / 100); // smoke in wind
//        this->container.AddVelocity((500 - 60.) / SCALE, 100. / SCALE, 0. / 10, 0.6 * wind / 100); // smoke in wind
//        this->container.AddVelocity((500 - 40.) / SCALE, 100. / SCALE, 0. / 10, 0.4 * wind / 100); // smoke in wind
//        this->container.AddVelocity((500 - 20.) / SCALE, 100. / SCALE, 0. / 10, 0.2 * wind / 100); // smoke in wind

        this->container.AddVelocity(200. / SCALE, 300. / SCALE, 0. / 10, 0.2); // naive wind

        float px = -0.4 * (1. + float(rand()) / RAND_MAX);
        float py = 0.2 * (float(rand()) / RAND_MAX);

//        float px = -0.4;
//        float py = 0.0 ;

        this->container.AddVelocity(500. / SCALE, 300. / SCALE, px / 10, py / 10); // smoke raise

        previousMouse = currentMouse;

        this->container.Step();
        this->container.Render(this->win, this->options.GetColor());
        this->container.FadeDensity(SIZE * SIZE, 0.01);

        this->win.display();
    }
}

