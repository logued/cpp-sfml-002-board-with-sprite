#include <SFML/Graphics.hpp>    // April 2025
#include <vector>
#include <iostream>

// Note the SFML configuration in file CMakeLists.txt must be correct and correspond
// to actual location of SFML folders on your laptop drive.

/**
 * Demonstration of:
 * Draw a 10x10 board with alternating black and white squares
 * Creates a Sprite (image) that can be 'moved' around the board
 * Read Events from the event queue of events such as key presses, mouse clicks ...
 * Based on type of key-press, change location of the sprite and redraw the window.
 */
using namespace sf;
using namespace std;

int main()
{
    // For a 10x10 board, with each square 60pixels wide & high, we need a 600x600 window
    RenderWindow window(VideoMode(600, 600), "My Bug Project");  // window width and height in Pixels

    // vector to store all the squares of the board
    // the first 10 elements represent the first row, the next 10 represent the second row, etc.
    vector<RectangleShape> squares; // to store squares that make up the board (are rectangles with equal width and height)

    bool colourWhite=true;    // first square to be white (otherwise set as black)

    // create 10x10 squares representing the board
    for (int row = 0; row < 10; row++) {
        for (int col = 0; col < 10; col++) {
            // create a square for the board (a 60*60 pixel sized square)
            // Use a RectangleShape with equal width and height
            RectangleShape square(Vector2f(60, 60)); // create a 2D vector of floats - size 60*60 pixels

            square.setFillColor( colourWhite?Color::White:Color::Black ); // squares alternate between white and black
            colourWhite=!colourWhite;   // negate (reverse) the colour

            square.setPosition(Vector2f(static_cast<float>(row)*60, static_cast<float>(col)*60 ));  // top left hand corner of square
            // each iteration of the inner loop moves the col on by one
            // an iteration of the outer loop moves down the rows  (top left square is at (0,0)
            // the static cast converts integer to float

            squares.push_back(square);  // add the square to the vector containing all squares
        }
        colourWhite=!colourWhite;   // negate the colour - extra one needed here so that second row begins with black
    }

    /// Set up the Sprite that shows a Bug that can be moved around the board
    /// A Sprite is a rectanglular object that has a Texture (an image attached)
    Sprite sprite;  // sprite is an independently moveable rectangular image (creates a Sprite object)
    sprite.setScale(0.23, 0.3);  // scale the bug sprite image down from its original pixel size
    Texture imageTexture;  // A Texture is an image, which we map to a 2D entity
    imageTexture.loadFromFile("bug_image.jpg");
    sprite.setTexture(imageTexture);    // applies the image to the sprite

    window.setFramerateLimit(60);  // 60 redraws per second
    bool reactToMouseClicks=false;
    int shape_x;
    int shape_y;

    // Loop around, listening for keyboard or mouse events
    // Capture matching events and react to them.
    while (window.isOpen())
    {
        sf::Event event;    // created an object to store details of one Event

        // Poll the window event queue ( i.e. check for events that happen e.g. keystroke )
        // and if one has occurred, pollEvent will put the event details
        // into the Event object supplied.
        while (window.pollEvent(event))
        {
            if (event.type == Event::KeyPressed)       // Deal with aKEY PRESSED Event
            {
                if (event.key.code == Keyboard::Key::Up) {
                    // if top left corner of sprite is further down the y-axis than 60 (i.e. y>60), then
                    // it is not on the top row of squares, and thus can be moved up by one square (i.e. 60 pixels)
                    // Otherwise, it can not move up, as it is on the top row.
                    if (sprite.getPosition().y >=60) {
                        sprite.setPosition(sprite.getPosition().x,sprite.getPosition().y-60);  // move sprite up by one square
                    }
                }
                if (event.key.code == Keyboard::Key::Down) {
                    if (sprite.getPosition().y <=535) {  // 9x60=540 and a few pixel less to be sure?
                        sprite.setPosition(sprite.getPosition().x,sprite.getPosition().y+60);
                    }
                }
                if (event.key.code == Keyboard::Key::Left) {
                    if (sprite.getPosition().x >=60 ) {   // as long as sprite is not in first column, it can move left
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

            if (event.type == sf::Event::Closed)
                window.close();

            // Code for MOUSE BUTTON Events - is not used in this sample
            // as flag is set to false above
            //
            if (event.type == Event::MouseButtonPressed) {
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
        }

        window.clear(); // Essential to clear previous drawings

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