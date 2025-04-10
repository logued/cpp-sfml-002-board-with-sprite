#include <SFML/Graphics.hpp>    // April 2025
#include <vector>
#include <iostream>

// Note that SFML configuration in CMakeLists.txt must be correct and correspond
// to actual location of SFML folders on your laptop drive.

/**
 * Draws a 10x10 board with alternating black and white squares
 * Creates a Sprite (image) that can be moved around the board
 * using arrow keys.
 *
 */
using namespace sf;
using namespace std;
int main()
{
    RenderWindow window(VideoMode(600, 600), "My Bug Project");  // window width and height in Pixels

    /// Prepare the Board
    ///
    vector<RectangleShape> squares; // to store squares that make up the board (are rectangles with equal width and height)

    bool colourWhite=true;    // first square to be white (otherwise set as black)

    // create 10x10 squares representing the board
    for (int x = 0; x < 10; x++) {
        for (int y = 0; y < 10; y++) {
            // create one square for the board (a 60*60 pixel sized square)
            // - it's a rectangle with equal width and height
            RectangleShape square(Vector2f(60, 60)); // create a 2D vector of floats - 60 * 60 elements (pixels)

            square.setFillColor( colourWhite?Color::White:Color::Black ); // squares alternate between white and black
            colourWhite=!colourWhite;   // negate the colour

            square.setPosition(Vector2f(x*60, y*60 ));  // top left hand corner of square
            squares.push_back(square);  // add the square to the vector
        }
        colourWhite=!colourWhite;   // negate the colour - extra one needed here so that second row begins with black
    }

    /// Set up the Sprite that shows a Bug that can be moved around the board
    ///
    Sprite sprite;  // sprite is an independently moveable image (creates a Sprite object)
    sprite.setScale(0.23, 0.3);  // scale the bug sprite image down from its original pixel size
    Texture imageTexture;
    imageTexture.loadFromFile("bug_image.jpg");
    sprite.setTexture(imageTexture);    // applies the image to the sprite

    window.setFramerateLimit(60);
    bool reactToMouseClicks=false;
    int shape_x;
    int shape_y;

    // Loop around listening for keyboard or mouse events
    // Capture matching events and react to them.
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))   // check for event (poll) and if one has occurred, put event details into the event object
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == Event::MouseButtonPressed)
            {
                  if (event.mouseButton.x > sprite.getPosition().x &&
                      event.mouseButton.x < sprite.getPosition().x+60
                      && event.mouseButton.y > sprite.getPosition().y &&
                      event.mouseButton.y < sprite.getPosition().y+60 ) {
                      reactToMouseClicks=true;
                      shape_x = event.mouseButton.x - sprite.getPosition().x;
                      shape_y = event.mouseButton.y - sprite.getPosition().y;
                  }
            }
            if (event.type == Event::MouseMoved) {
                if (reactToMouseClicks) {
                    sprite.setPosition(Vector2f(event.mouseMove.x-shape_x, event.mouseMove.y-shape_y));
                }
            }
            if (event.type == Event::MouseButtonReleased) {
                if (reactToMouseClicks) {
                   // cout << event.mouseButton.button;
                    int mx = (event.mouseButton.x/60)*60;
                    int my = (event.mouseButton.y/60)*60;
                    cout << mx <<" "  << event.mouseButton.x << endl;
                    sprite.setPosition(Vector2f(mx, my));
                    reactToMouseClicks=false;
                }
            }
            if (event.type == Event::KeyPressed) {
                if (event.key.code == Keyboard::Key::Up) {
                    // if top left corner of sprite is further down the y-axis than 60 (i.e. y>60), then
                    // it is not on the top row of squares, and thus can be moved up by one square (i.e. 60 pixels)
                    if (sprite.getPosition().y >=60) {
                        sprite.setPosition(sprite.getPosition().x,sprite.getPosition().y-60);  // move sprite up by one square
                    }
                }
                if (event.key.code == Keyboard::Key::Down) {
                    if (sprite.getPosition().y <=535) {
                        sprite.setPosition(sprite.getPosition().x,sprite.getPosition().y+60);
                    }
                }
                if (event.key.code == Keyboard::Key::Left) {
                    if (sprite.getPosition().x >=60 ) {
                        sprite.setPosition(sprite.getPosition().x-60,sprite.getPosition().y);
                    }
                }
                if (event.key.code == Keyboard::Key::Right) {
                    if (sprite.getPosition().x <=535) {
                        sprite.setPosition(sprite.getPosition().x+60,sprite.getPosition().y);
                    }
                }
                // if (event.key.code == Keyboard::Key::Space) {
                //    if (shape.getFillColor()== Color::Green)
                //        shape.setFillColor(Color::Red);
                //     else
                //         shape.setFillColor(Color::Green);
                // }
            }
        }

        window.clear();

        // Draw the window contents by drawing each square contained in the squares vector.
        // They are alternatively white and black (when drawn as a 10x10 board)
        for (RectangleShape &square: squares) {
            window.draw(square);
        }
        window.draw(sprite);
        window.display();
    }

    return 0;
}