#include <SFML/Graphics.hpp>
#include <vector>
#include <random>
#include <iostream>
#include <memory>

class GameObject
{
protected:
    sf::RectangleShape shape;
    sf::Vector2f velocity;

public:
    GameObject(float x, float y, float width, float height)
    {
        shape.setPosition(x, y);
        shape.setSize(sf::Vector2f(width, height));
    }
    virtual void update() = 0;
    virtual ~GameObject() {}

    bool intersects(const GameObject &other) const
    {
        return shape.getGlobalBounds().intersects(other.shape.getGlobalBounds());
    }
    void draw(sf::RenderWindow &window) const
    {
        window.draw(shape);
    }
    sf::Vector2f getPosition() const { return shape.getPosition(); }
    void setPosition(sf::Vector2f pos) { shape.setPosition(pos); }
};

class Dinosaur : public GameObject
{
private:
    bool isJumping;
    const float gravity;
    const float jumpForce;
    const float groundY;

public:
    Dinosaur(float groundLevel)
        : GameObject(50, groundLevel - 60, 40, 60),
          gravity(0.8f),
          jumpForce(-15.0f),
          groundY(groundLevel - 60),
          isJumping(false)
    {
        shape.setFillColor(sf::Color::Green);
    }

    void jump()
    {
        if (!isJumping)
        {
            velocity.y = jumpForce;
            isJumping = true;
        }
    }

    void update() override
    {
        if (isJumping)
        {
            velocity.y += gravity;
            shape.move(0, velocity.y);

            if (shape.getPosition().y >= groundY)
            {
                shape.setPosition(shape.getPosition().x, groundY);
                velocity.y = 0;
                isJumping = false;
            }
        }
    }
};

class Cactus : public GameObject
{
private:
    float speed;

public:
    Cactus(float x, float groundLevel)
        : GameObject(x, groundLevel - 40, 20, 40),
          speed(7.0f)
    {
        shape.setFillColor(sf::Color::Red);
    }

    void update() override
    {
        shape.move(-speed, 0);
    }

    bool isOffscreen() const
    {
        return shape.getPosition().x < -shape.getSize().x;
    }
};

class Game
{
private:
    sf::RenderWindow window;
    Dinosaur *dino;
    std::vector<Cactus *> cacti;
    sf::RectangleShape ground;
    sf::Text scoreText;
    sf::Font font;
    int score;
    bool gameOver;
    float spawnTimer;
    const float groundLevel;
    std::random_device rd;
    std::mt19937 gen;
    std::uniform_real_distribution<> spawnDist;

    bool loadGameFont()
    {
        // Try loading system fonts first
        const std::vector<std::string> macFontPaths = {
            "/System/Library/Fonts/Helvetica.ttf",
            "/System/Library/Fonts/SF-Pro-Text-Regular.otf",
            "/System/Library/Fonts/AppleSDGothicNeo.ttc",
            "/Library/Fonts/Arial.ttf" // Added as another fallback
        };

        for (const auto &path : macFontPaths)
        {
            if (font.loadFromFile(path))
            {
                std::cout << "Successfully loaded font: " << path << std::endl;
                return true;
            }
        }

        // If we got here, no system fonts worked
        std::cout << "Failed to load any system fonts" << std::endl;
        return false;
    }

public:
    Game() : window(sf::VideoMode(800, 400), "Dinosaur Game"),
             groundLevel(300),
             score(0),
             gameOver(false),
             spawnTimer(0),
             gen(rd()),
             spawnDist(1.5, 3.0)
    {
        window.setFramerateLimit(60);

        // Initialize dinosaur
        dino = new Dinosaur(groundLevel);

        // Initialize ground
        ground.setSize(sf::Vector2f(800, 2));
        ground.setPosition(0, groundLevel);
        ground.setFillColor(sf::Color::White);

        // Try to load font
        if (!loadGameFont())
        {
            throw std::runtime_error("Could not load any fonts - cannot continue");
        }

        // Setup score text
        scoreText.setFont(font);
        scoreText.setCharacterSize(24);
        scoreText.setFillColor(sf::Color::White);
        scoreText.setPosition(10, 10);
    }

    ~Game()
    {
        delete dino;
        for (Cactus *cactus : cacti)
        {
            delete cactus;
        }
        cacti.clear();
    }

    void run()
    {
        sf::Clock clock;

        while (window.isOpen())
        {
            float dt = clock.restart().asSeconds();
            handleEvents();
            if (!gameOver)
            {
                update(dt);
            }
            render();
        }
    }

private:
    void handleEvents()
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Space)
                {
                    if (!gameOver)
                    {
                        dino->jump();
                    }
                }
                if (event.key.code == sf::Keyboard::R && gameOver)
                {
                    restart();
                }
            }
        }
    }

    void update(float dt)
    {
        dino->update();

        spawnTimer += dt;
        if (spawnTimer >= spawnDist(gen))
        {
            cacti.push_back(new Cactus(800, groundLevel));
            spawnTimer = 0;
            spawnDist = std::uniform_real_distribution<>(1.5 - (score / 500.0), 3.0 - (score / 500.0));
        }

        std::vector<Cactus *> activeCacti;
        for (size_t i = 0; i < cacti.size(); ++i)
        {
            cacti[i]->update();

            if (dino->intersects(*cacti[i]))
            {
                gameOver = true;
                return;
            }

            if (!cacti[i]->isOffscreen())
            {
                activeCacti.push_back(cacti[i]);
            }
            else
            {
                delete cacti[i];
            }
        }

        cacti = activeCacti;
        score++;
        scoreText.setString("Score: " + std::to_string(score));
    }

    void render()
    {
        window.clear(sf::Color::Black);

        window.draw(ground);
        dino->draw(window);

        for (const Cactus *cactus : cacti)
        {
            cactus->draw(window);
        }

        window.draw(scoreText);

        if (gameOver)
        {
            sf::Text gameOverText;
            gameOverText.setFont(font);
            gameOverText.setString("Game Over!\nPress R to restart");
            gameOverText.setCharacterSize(32);
            gameOverText.setFillColor(sf::Color::White);
            gameOverText.setPosition(
                window.getSize().x / 2 - gameOverText.getGlobalBounds().width / 2,
                window.getSize().y / 2 - gameOverText.getGlobalBounds().height / 2);
            window.draw(gameOverText);
        }

        window.display();
    }

    void restart()
    {
        delete dino;
        for (Cactus *cactus : cacti)
        {
            delete cactus;
        }
        cacti.clear();

        score = 0;
        gameOver = false;
        dino = new Dinosaur(groundLevel);
        spawnTimer = 0;
        spawnDist = std::uniform_real_distribution<>(1.5, 3.0);
    }
};

int main()
{
    try
    {
        Game game;
        game.run();
    }
    catch (const std::exception &e)
    {
        std::cout << "Error: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}