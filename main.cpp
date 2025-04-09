#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

using namespace sf;
using namespace std;
int main()
{
    RenderWindow window(VideoMode(800, 600), "My Bug Project");
    vector<RectangleShape> rectangles;
    //CircleShape shape(30.f);
    Sprite shape;
    shape.setScale(0.2, 0.25);
    Texture texture;
    texture.loadFromFile("download.jpg");
    shape.setTexture(texture);

   // shape.setFillColor(sf::Color::Green);
    window.setFramerateLimit(60);
    bool isSelected=false;
    int shape_x, shape_y;
    int i = 0;
    for (int x = 0; x < 10; x++) {
        for (int y = 0; y < 10; y++) {
            RectangleShape rect(Vector2f(60, 60));
            rect.setFillColor(i%2==0?Color::White:Color::Black);
            i++;
            rect.setPosition(Vector2f(x*60, y*60));
            rectangles.push_back(rect);
        }
        i++;
    }

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == Event::MouseButtonPressed)
            {
                  if (event.mouseButton.x > shape.getPosition().x &&
                      event.mouseButton.x < shape.getPosition().x+60
                      && event.mouseButton.y > shape.getPosition().y &&
                      event.mouseButton.y < shape.getPosition().y+60 ) {
                      isSelected=true;
                      shape_x = event.mouseButton.x - shape.getPosition().x;
                      shape_y = event.mouseButton.y - shape.getPosition().y;
                  }
            }
            if (event.type == Event::MouseMoved) {
                if (isSelected) {
                    shape.setPosition(Vector2f(event.mouseMove.x-shape_x, event.mouseMove.y-shape_y));
                }
            }
            if (event.type == Event::MouseButtonReleased) {
                if (isSelected) {
                   // cout << event.mouseButton.button;
                    int mx = (event.mouseButton.x/60)*60;
                    int my = (event.mouseButton.y/60)*60;
                    cout << mx <<" "  << event.mouseButton.x << endl;
                    shape.setPosition(Vector2f(mx, my));
                    isSelected=false;
                }
            }
            if (event.type == Event::KeyPressed) {
                if (event.key.code == Keyboard::Key::Up) {
                    if (shape.getPosition().y >=60) {
                        shape.setPosition(shape.getPosition().x,shape.getPosition().y-60);
                    }
                }
                if (event.key.code == Keyboard::Key::Down) {
                    if (shape.getPosition().y <=535) {
                        shape.setPosition(shape.getPosition().x,shape.getPosition().y+60);
                    }
                }
                if (event.key.code == Keyboard::Key::Left) {
                    if (shape.getPosition().x >=60 ) {
                        shape.setPosition(shape.getPosition().x-60,shape.getPosition().y);
                    }
                }
                if (event.key.code == Keyboard::Key::Right) {
                    if (shape.getPosition().x <=535) {
                        shape.setPosition(shape.getPosition().x+60,shape.getPosition().y);
                    }
                }
                if (event.key.code == Keyboard::Key::Space) {
                   /*if (shape.getFillColor()== Color::Green)
                       shape.setFillColor(Color::Red);
                    else
                        shape.setFillColor(Color::Green);*/
                }
            }
        }


        window.clear();
        for (RectangleShape &rect: rectangles) {
            window.draw(rect);
        }
        window.draw(shape);
        window.display();
    }

    return 0;
}