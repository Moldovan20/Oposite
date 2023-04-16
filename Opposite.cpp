#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdlib>

using namespace std;
using namespace sf;

int checkIfClicked(Sprite squares[], Vector2i pos, const int squareSize, const int squaresH, const int squaresV)
{
    for (int k(0); k < squaresH * squaresV; k++)
    {
        if (pos.x >= k % squaresH * squareSize + k % squaresH && pos.x <= k % squaresH * squareSize + k % squaresH + squareSize && pos.y >= k / squaresH * squareSize + k / squaresH && pos.y <= k / squaresH * squareSize + k / squaresH + squareSize)
        {
            return k;
        }

    }
    return -1;
}

int main()
{
    srand(time(NULL));
    const int width(1000), height(1000);
    const int squareSize(50);
    const int squaresH = width / squareSize;
    const int squaresV = height / squareSize;

    sf::RenderWindow window(sf::VideoMode(width, height), "Opposite");

    Texture sadTexture, gladTexture;
    gladTexture.loadFromFile("images/glad2.png");
    sadTexture.loadFromFile("images/sad2.png");


    Sprite sad, glad(gladTexture);

   

    Sprite* squares = new Sprite[squaresH * squaresV];
    Sprite* copySquares = new Sprite[squaresH * squaresV];

    int table[squaresH * squaresV];

    for (int k(0); k < squaresH * squaresV; k++)
    {       
        table[k] = 0;
    }

    for (int k(0); k < squaresH * squaresV; k++)
    {
        squares[k].setScale(0.5, 0.5);
        squares[k].setTexture(sadTexture);
        squares[k].setTextureRect(IntRect(k % squaresH * squareSize, k / squaresH * squareSize, squareSize, squareSize));
     
        if (k % squaresH == 0)squares[k].setPosition(k % squaresH * squareSize+ squareSize / 2, k / squaresH * squareSize+ squareSize / 2), squares[k].setOrigin(squareSize / 2, squareSize / 2);
        if (k % squaresH != 0)squares[k].setPosition(k % squaresH * squareSize + squareSize / 2, k / squaresH * squareSize+ squareSize / 2), squares[k].setOrigin(squareSize / 2, squareSize / 2);
        if (k / squaresH > 0)squares[k].setPosition(k % squaresH * squareSize+ squareSize / 2, k / squaresH * squareSize+ squareSize / 2), squares[k].setOrigin(squareSize / 2, squareSize / 2);
       
    }

    Clock clock;
    float timer = 0, delay = 0.01f;
    Vector2f add;
    add.x = 0;
    add.y = 10;


    while (window.isOpen())
    {
        Vector2i pos = Mouse::getPosition(window);

        int c = checkIfClicked(squares, pos, squareSize, squaresH, squaresV);
        int x = c % squaresH;
        int y = c / squaresH;

        float time = clock.getElapsedTime().asSeconds();
        timer += time;
        clock.restart();

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if (table[c] == 0)
        {
            copySquares[c] = squares[c];
            table[c] = 1;
        }

        for (int k(0); k < squaresH * squaresV; k++)
        {
            if (table[k] == 1)
            {
                
                squares[k].setTexture(gladTexture);
                squares[k].setTextureRect(IntRect(k % squaresH * squareSize, k / squaresH * squareSize, squareSize, squareSize));
                if (k % squaresH == 0)squares[k].setPosition(k % squaresH * squareSize + squareSize / 2, k / squaresH * squareSize + squareSize / 2);
                if (k % squaresH != 0)squares[k].setPosition(k % squaresH * squareSize + squareSize / 2, k / squaresH * squareSize + squareSize / 2);
                if (k / squaresH > 0)squares[k].setPosition(k % squaresH * squareSize + squareSize / 2, k / squaresH * squareSize + squareSize / 2);
                table[k] = 2;
            }

        }

        window.clear();

        if (timer > delay)
        {
            for (int k(0); k < squaresH * squaresV; k++)
            {            
                copySquares[k].setPosition(copySquares[k].getPosition() + add);
                copySquares[k].rotate(rand() % 10 + 1);          
            }
        }

        for (int k(0); k < squaresH * squaresV; k++)
        {
            
            window.draw(squares[k]);         
        }

        for (int k(0); k < squaresH * squaresV; k++)
        {
           
            window.draw(copySquares[k]);
        }

    
        window.display();
    }

    return 0;
}