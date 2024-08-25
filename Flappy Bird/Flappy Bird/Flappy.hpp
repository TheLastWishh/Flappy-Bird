#pragma once
#include <SFML/Graphics.hpp>
#include <memory>

class FlappyBird {
    // 1. Init
    sf::RenderWindow window;
    float gravity, frame, space;
    int count, score;
    sf::Texture bg, flappy, pipe;
    sf::Sprite background, bird, pipeBottom, pipeTop;
    std::vector<sf::Sprite> pipes;
    // 5. Collide with the pipes
    bool gameover, add;
    // 6. Add text to game over
    sf::Font font;
    sf::Text txt_score, txt_gameover;

protected:
    void events();
    void draw();
    void game();
    void movePipes();
    void setAnimeBird();
    void moveBird();

public:
    FlappyBird();
    void run();
};