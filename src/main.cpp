#include <SFML/Graphics.hpp>
#include <iostream>
#include "util/filesystem.h"

#include "tree/BinaryTree.hpp"
#include "tree/operations.hpp"
#include "graphics/BinaryTree.hpp"
#include "graphics/font.hpp"


int main(const int, const char* argv[])
{
    /**
     * Settings
     */
    static struct {
        struct {
            const float moveSpeed       = 450;
            const float moveSpeedPlus   = 800;
        } view;
    } settings;


    struct {
        struct {
            float moveSpeed             = settings.view.moveSpeed;
        } view;
    } props;


    /**
     * Window
     */
    sf::RenderWindow window {sf::VideoMode{1024, 768}, "Binary Tree viewer", sf::Style::Default};
    sf::View winView {window.getView()};
    window.setVerticalSyncEnabled(true);


    /**
     * Inputs
     */
    sf::Clock clock;


    /**
     * Resources
     */
    auto resourcePath = fs::canonical(argv[0]).remove_filename().parent_path() / "resource";
    auto fontPath = resourcePath / "font";

    sf::Font font;
    font.loadFromFile(sf::String{fontPath / "MoskNormal.ttf"});


    /**
     * Binary tree
     */
    gfx::setFont(font);

    // The tree is constructed with these values
    BinaryTree<int> bt{20};
    bt.insert(15);
    bt.insert(10);
    bt.insert(8);
    bt.insert(9);
    bt.insert(7);
    bt.insert(12);
    bt.insert(24);
    bt.insert(25);
    bt.insert(16);
    bt.insert(22);

    // Graphic representation of the tree
    gfx::BinaryTree gt{bt};


    // View correction
    winView.setSize({window.getSize().x * 1.5f, window.getSize().y * 1.5f});
    winView.setCenter(gt.getPosition().x, winView.getCenter().y + 156.f);   // fully handpicked values


    /**
     * Program loop
     */
    while (window.isOpen())
    {
        /**
         * Event handling
         */
        sf::Event event;
        while (window.pollEvent(event)) {
            switch (event.type)
            {
                case sf::Event::KeyPressed: {
                    switch (event.key.code) {
                        case sf::Keyboard::LShift:
                            props.view.moveSpeed = settings.view.moveSpeedPlus;
                        break;

                        case sf::Keyboard::Enter:
                        case sf::Keyboard::Escape:
                        case sf::Keyboard::Space:
                            window.close();
                        default:
                        break;
                    }
                }
                break;

                case sf::Event::KeyReleased: {
                    switch (event.key.code) {
                        case sf::Keyboard::LShift:
                            props.view.moveSpeed = settings.view.moveSpeed;
                        default:
                        break;
                    }
                }
                break;

                case sf::Event::Resized: {
                    // Preserve aspect ratio and left-top coordinates.
                    const sf::Vector2f size {
                        static_cast<float>(event.size.width),
                        static_cast<float>(event.size.height)
                    };
                    const auto coords = window.mapPixelToCoords({0, 0}, winView);
                    winView.setSize(size);
                    winView.setCenter(coords.x + size.x/2, coords.y + size.y/2);
                }
                break;

                case sf::Event::Closed: {
                    window.close();
                }
                default:
                break;
            }
        }


        /**
         * Inputs
         */
        const auto frameTime = clock.restart();

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            winView.move(props.view.moveSpeed * -frameTime.asSeconds(), 0);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            winView.move(props.view.moveSpeed * frameTime.asSeconds(), 0);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            winView.move(0, props.view.moveSpeed * -frameTime.asSeconds());
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            winView.move(0, props.view.moveSpeed * frameTime.asSeconds());
        }


        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Add)) {
            winView.zoom(.9f);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Subtract)) {
            winView.zoom(1.1f);
        }


        /**
         * Display
         */
        window.clear({112, 112, 255});
        window.setView(winView);

        window.draw(gt);

        window.display();

    }

}
