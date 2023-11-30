
#include <SFML/Graphics.hpp>
#include <iostream>

//using namespace pong;

int main()
{
    using namespace sf;
    using namespace std;

    // Init de ventana
    const int windowWidth = 640;
    const int windowHeight = 480;
    RenderWindow window(VideoMode(windowWidth, windowHeight), "Ejemplo de SFML");

    Clock clock;

    // Init de objetos

    const int circleRadius = 50;
    CircleShape shape(circleRadius);
    shape.setPosition(windowWidth * 0.5f - circleRadius,
        windowHeight * 0.5f - circleRadius);
    shape.setFillColor(Color::Green);
    float speed = 100.0f;

    Texture texture;
    if (!texture.loadFromFile("res/image.png"))
    {
        cout << "Hubo un error cargando la textura image.png" << endl;
    }

    Mouse mouse;
    mouse.getPosition();
    

    Sprite sprite;
    sprite.setTexture(texture);
    sprite.setPosition(20.0f, 20.0f);

    // Main loop
    while (window.isOpen())
    {
        Time dt = clock.restart();

        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }

        float horizontalAxis = 0.0f;
        float verticalAxis = 0.0f;

        if (Keyboard::isKeyPressed(Keyboard::Right))
        {
            horizontalAxis = 1.0f;
        }

        if (Keyboard::isKeyPressed(Keyboard::Left))
        {
            horizontalAxis = -1.0f;
        }

        if (Keyboard::isKeyPressed(Keyboard::Up))
        {
            verticalAxis = -1.0f;
        }

        if (Keyboard::isKeyPressed(Keyboard::Down))
        {
            verticalAxis = 1.0f;
        }

        shape.move(horizontalAxis * speed * dt.asSeconds(),
            verticalAxis * speed * dt.asSeconds());

        if (shape.getGlobalBounds().intersects(sprite.getGlobalBounds()))
        {
            shape.setFillColor(Color::Red);
        }
        else
        {
            shape.setFillColor(Color::Green);
        }

        // Dibujado

        window.clear(Color::Black);

        window.draw(sprite);
        window.draw(shape);

        window.display();
    }

    return 0;
}
