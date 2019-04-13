#include <SFML/Graphics.hpp>
#include <iostream>
#include "util/filesystem.h"

#include "tree/BinaryTree.hpp"
#include "tree/operations.hpp"
#include "graphics/GfxBinTree.hpp"


int main(const int, const char* argv[])
{
    /**
     * Window
     */
    sf::RenderWindow window {sf::VideoMode{1024, 768}, "SFML_App", sf::Style::Default};
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
     * Program specifics
     */
    gfxTrees::setFont(font);

    BinaryTree<int> bt{1000};
    bt.insert(500);
    bt.insert(1500);
    bt.insert(1200);
    bt.insert(1400);
    bt.insert(400);
    bt.insert(450);
    bt.insert(800);
    bt.insert(900);

    std::cout << bt.value() << "\n"
        << "left child : " << bt.leftChild().value() << "\n"
        << "right child : " << bt.rightChild().value() << "\n";

    const auto nodesPointers = breadthFirstTraversal(bt);

    for (const auto* pointer : nodesPointers)
        std::cout << pointer->value() << ", ";

    std::cout << "\n";

    GfxBinaryTree gt{bt};



    /**
     * Loop
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
                        case sf::Keyboard::Enter:
                        case sf::Keyboard::Escape:
                        case sf::Keyboard::Space:
                            window.close();
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
            winView.move(750 * -frameTime.asSeconds(), 0);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            winView.move(750 * frameTime.asSeconds(), 0);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            winView.move(0, 750 * -frameTime.asSeconds());
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            winView.move(0, 750 *  frameTime.asSeconds());
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
