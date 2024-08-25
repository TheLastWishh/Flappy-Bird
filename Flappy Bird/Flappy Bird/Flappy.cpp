#include "flappy.hpp"

FlappyBird::FlappyBird() {
    // 1. Init
    window.create(
        sf::VideoMode(1000, 600),
        "FlappyBird (remix)",
        sf::Style::Titlebar | sf::Style::Close
    );
    window.setFramerateLimit(60);
    window.setPosition(sf::Vector2i(0, 0));

    gravity = frame = { 0 };
    space = { 250.f };
    count = { 0 };

    bg.loadFromFile("./resources/img/background.png");
    flappy.loadFromFile("./resources/img/flappy.png");
    pipe.loadFromFile("./resources/img/pipe.png");

    background.setTexture(bg);
    bird.setTexture(flappy);
    pipeBottom.setTexture(pipe);
    pipeTop.setTexture(pipe);

    bird.setPosition(
        500.f - flappy.getSize().x / 2.f,
        300.f - flappy.getSize().y / 2.f
    );
    bird.setScale(2.f, 2.f);
    bird.setTextureRect(sf::IntRect(0, 0, 34, 24));

    pipeBottom.setScale(1.5f, 1.5f);
    pipeTop.setScale(1.5f, -1.5f);

    // TEMP
    /*pipeBottom.setPosition(100, 200);
    pipeTop.setPosition(100, 100);*/

    // 5. Collide with the pipes
    gameover = add = { false };
    // 6. Add text to game over
    score = { 0 };

    font.loadFromFile("./resources/font/flappybird.ttf");
    txt_gameover.setFont(font);
    txt_gameover.setString("Press SPACE to restart");
    txt_gameover.setPosition(200, 300);
    txt_gameover.setCharacterSize(50);
    txt_gameover.setOutlineThickness(3);

    // 7. Add Score
    txt_score.setFont(font);
    txt_score.setString(std::to_string(score));
    txt_score.setPosition(10, 10);
    txt_score.setCharacterSize(50);
    txt_score.setOutlineThickness(3);
}

void FlappyBird::events() {
    // 1. Init
    sf::Event e;
    while (window.pollEvent(e)) {
        if (e.type == sf::Event::Closed) {
            window.close();
        }
    }

    // 6. Add text to game over
    if (gameover && sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        score = 0;
        // 7. Add Score
        txt_score.setString(std::to_string(score));
        pipes.clear();

        bird.setPosition(
            500.f - flappy.getSize().x / 2.f,
            300.f - flappy.getSize().y / 2.f
        );
        gameover = false;
    }
}

void FlappyBird::draw() {
    // 1. Init
    window.clear(sf::Color::Black);
    window.draw(background);

    // 2. Move the pipes
    for (auto& p : pipes) {
        window.draw(p);
    }

    window.draw(bird);
    //window.draw(pipeBottom);
    //window.draw(pipeTop); 

    // 6. Add text to game over
    if (gameover) {
        window.draw(txt_gameover);
    }

    // 7. Add Score
    window.draw(txt_score);

    window.display();
}

void FlappyBird::run() {
    // 1.Init
    while (window.isOpen()) {
        events();
        // 2. Move the pipes
        game();
        draw();

        ++count;
        if (count == 300) {
            count = 0;
        }
    }
}

// 2. Move the pipes
void FlappyBird::movePipes() {
    // 4. Move the flappy bird
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        gravity = -8.f;
        bird.setRotation(-frame - 10.f);
    }
    else {
        bird.setRotation(frame - 10.f);
    }

    if (count % 150 == 0) {
        int pos = std::rand() % 275 + 175;

        pipeBottom.setPosition(1000, pos + space);
        pipeTop.setPosition(1000, pos);

        // Them cac doi tuong pipBottom va pipeTop vao vector pipes
        pipes.push_back(pipeBottom);
        pipes.push_back(pipeTop);
    }

    // Duyet qua vector pipes va di chuyen cac ong
    for (std::size_t i{}; i < pipes.size(); ++i) {

        // 5. Collide with the pipes
        if (pipes[i].getGlobalBounds().intersects(bird.getGlobalBounds())) {
            // 8. Improve
            bird.move(15.f, 0);

            if (pipes[i].getScale().y < 0) {
                bird.move(0, -15.f);
            }
            else {
                bird.move(0, 15.f);
            }

            gameover = true;
        }

        if (pipes[i].getPosition().x < -100) {
            pipes.erase(pipes.begin() + i);
        }

        pipes[i].move(-3, 0); // Di chuyen cac ong sang trai

        // 7. Add Score
        /*if (pipes[i].getPosition().x == 448) {
            txt_score.setString(std::to_string(++score));
        }*/

        if (pipes[i].getPosition().x == 448 && !add) {
            txt_score.setString(std::to_string(++score));
            add = true;
        }
        else {
            add = false;
        }
    }
}

void FlappyBird::game() {
    // 5. Collide with the pipes
    if (!gameover) {
        // 3. Animate the flappy bird
        setAnimeBird();
        // 4. Move the flappy bird
        moveBird();
        movePipes();
    }    
}

// 3. Animate the flappy bird
void FlappyBird::setAnimeBird() {
    frame += 0.15f;

    if (frame > 3) {
        frame -= 3;
    }

    bird.setTextureRect(sf::IntRect(34 * (int)frame, 0, 34, 24));
}

// 4. Move the flappy bird
void FlappyBird::moveBird() {
    bird.move(0, gravity);
    gravity += 0.5f;
}