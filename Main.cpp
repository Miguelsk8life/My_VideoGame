#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "Hero.h"
#include "Enemy.h"
#include "Platform.h"
#include "Banana.h"

sf::Texture backgroundTexture;
sf::Sprite backgroundSprite;
sf::Vector2f viewSize(1200, 675);
sf::VideoMode vm(viewSize.x, viewSize.y);
sf::RenderWindow window(vm, "Hello Game SFML !!!", sf::Style::Default);
sf::View gameView;
sf::FloatRect worldBounds(0, 0, 3600, 675);
std::vector<Platform> platforms;
sf::RectangleShape collectible;
Banana firstBanana;
Banana secondBanana;
Banana thirdBanana;
Banana fourthBanana;
Banana fifthBanana;
Banana sixthBanana;
int countBananas = 0;

bool firstBananaVisible = true;
bool secondBananaVisible = true;
bool thirdBananaVisible = true;
bool fourthBananaVisible = true;
bool fifthBananaVisible = true;
bool sixthBananaVisible = true;
bool allBananasCollected = false;
bool playerMovingUp = false;
bool playerMovingDown = false;
bool playerMovingLeft = false;
bool playerMovingRight = false;
bool playerStandingLeft = false;
bool playerStandingRight = false;
sf::Clock enemyMovementClock;
float enemyMoveDuration = 4.0f;
bool enemy1MovingRight = false;
bool enemy2MovingRight = false;
bool enemy3MovingRight = false;
bool enemy4MovingRight = false;
bool enemy5MovingRight = false;
bool enemy6MovingRight = false;
bool gameOver = false;
bool gameWon = false;
sf::Font font;
sf::Text gameOverText;
sf::Text gameWonText;
Hero hero;
Enemy enemy1;
Enemy enemy2;
Enemy enemy3;
Enemy enemy4;
Enemy enemy5;
Enemy enemy6;
float groundLevel = 675 * 0.90f;

void initGameOverText() {
    if (!font.loadFromFile("Assets/fonts/Roboto-VariableFont_wdth,wght.ttf")) {
        std::cerr << "Error al cargar la fuente!" << std::endl;
    }

    gameOverText.setFont(font);
    gameOverText.setString("¡GAME OVER!");
    gameOverText.setCharacterSize(100);
    gameOverText.setFillColor(sf::Color::Red);
}

void initGameWonText() {
    if (!font.loadFromFile("Assets/fonts/Roboto-VariableFont_wdth,wght.ttf")) {
        std::cerr << "Error al cargar la fuente!" << std::endl;
    }

    gameWonText.setFont(font);
    gameWonText.setString("¡YOU WON!");
    gameWonText.setCharacterSize(100);
    gameWonText.setFillColor(sf::Color::Blue);
}

void init() {
    gameView.setSize(viewSize);
    gameView.setCenter(viewSize.x / 2, viewSize.y / 2);
    initGameOverText();
    initGameWonText();
    hero.init(sf::Vector2f(viewSize.x * 0.25f, groundLevel + 10), 200);

    
    enemy1.init(sf::Vector2f(2000, groundLevel + 20), "Assets/graphics/dinosaurioRed_walkingleft", "Assets/graphics/dinosaurioRed_walkingright", 6.0f, 6.0f);
    enemy2.init(sf::Vector2f(3000, groundLevel - 300), "Assets/graphics/bat_flyingleft", "Assets/graphics/bat_flyingright", 4.0f, 4.0f);
    enemy3.init(sf::Vector2f(2500, groundLevel + 20), "Assets/graphics/dinosaurioRed_walkingleft", "Assets/graphics/dinosaurioRed_walkingright", 5.0f, 5.0f);
    enemy4.init(sf::Vector2f(3500, groundLevel + 20), "Assets/graphics/dinosaurioRed_walkingleft", "Assets/graphics/dinosaurioRed_walkingright", 7.0f, 7.0f);
    enemy5.init(sf::Vector2f(1800, groundLevel - 200), "Assets/graphics/bat_flyingleft", "Assets/graphics/bat_flyingright", 3.0f, 3.0f);
    enemy6.init(sf::Vector2f(2800, groundLevel - 400), "Assets/graphics/bat_flyingleft", "Assets/graphics/bat_flyingright", 5.0f, 5.0f);

    if (!backgroundTexture.loadFromFile("Assets/graphics/background7merge.jpg")) {
        std::cerr << "Error al cargar la imagen de fondo!" << std::endl;
    }

    backgroundSprite.setTexture(backgroundTexture);
    backgroundSprite.setScale(
        worldBounds.width / backgroundTexture.getSize().x,
        worldBounds.height / backgroundTexture.getSize().y
    );
    backgroundSprite.setPosition(worldBounds.left, worldBounds.top);

    
    platforms.push_back(Platform(sf::Vector2f(200, 30), sf::Vector2f(1100, 400)));
    platforms.push_back(Platform(sf::Vector2f(200, 30), sf::Vector2f(600, 400)));
    platforms.push_back(Platform(sf::Vector2f(200, 30), sf::Vector2f(2000, 400)));

    platforms.push_back(Platform(sf::Vector2f(200, 30), sf::Vector2f(2500, 400)));
    platforms.push_back(Platform(sf::Vector2f(200, 30), sf::Vector2f(3000, 400)));
    platforms.push_back(Platform(sf::Vector2f(200, 30), sf::Vector2f(3500, 400)));
    platforms.push_back(Platform(sf::Vector2f(200, 30), sf::Vector2f(4000, 400)));
    platforms.push_back(Platform(sf::Vector2f(200, 30), sf::Vector2f(4500, 400)));
    platforms.push_back(Platform(sf::Vector2f(300, 30), sf::Vector2f(1500, 300)));
    platforms.push_back(Platform(sf::Vector2f(150, 30), sf::Vector2f(500, 200)));

   
    firstBanana.init(sf::Vector2f(700, 380));
    secondBanana.init(sf::Vector2f(1200, 380));
    thirdBanana.init(sf::Vector2f(2100, 380));

   
    fourthBanana.init(sf::Vector2f(2600, 380));
    fifthBanana.init(sf::Vector2f(3100, 380));
}

void checkCollisions() {
    sf::FloatRect heroBounds = hero.getSprite().getGlobalBounds();
    heroBounds.top += 10;
    heroBounds.height -= 20;
    heroBounds.left += 10;
    heroBounds.width -= 20;

    bool wasOnPlatform = hero.getIsOnPlatform();
    hero.setOnPlatform(false);

    for (auto& platform : platforms) {
        sf::FloatRect platformBounds = platform.getBounds();

        if (heroBounds.intersects(platformBounds)) {
            if (hero.getPosition().y + heroBounds.height / 2 < platformBounds.top + 10 &&
                hero.getPosition().y < platformBounds.top) {
                hero.move(0, platformBounds.top - (hero.getPosition().y + heroBounds.height / 2));
                hero.setForce(0);
                hero.setOnPlatform(true);

                if (!hero.getIsJumping() || hero.getForce() >= 0) {
                    hero.setIsJumping(false);
                }
            }
            else if (hero.getPosition().y - heroBounds.height / 2 > platformBounds.top + platformBounds.height - 10) {
                hero.move(0, (platformBounds.top + platformBounds.height) - (hero.getPosition().y - heroBounds.height / 2));
                hero.setForce(0);
            }
            else if (hero.getPosition().x + heroBounds.width / 2 < platformBounds.left + 10) {
                hero.move(platformBounds.left - (hero.getPosition().x + heroBounds.width / 2), 0);
            }
            else if (hero.getPosition().x - heroBounds.width / 2 > platformBounds.left + platformBounds.width - 10) {
                hero.move((platformBounds.left + platformBounds.width) - (hero.getPosition().x - heroBounds.width / 2), 0);
            }
        }
    }

    sf::FloatRect enemy1Bounds = enemy1.getSprite().getGlobalBounds();
    sf::FloatRect enemy2Bounds = enemy2.getSprite().getGlobalBounds();
    sf::FloatRect enemy3Bounds = enemy3.getSprite().getGlobalBounds();
    sf::FloatRect enemy4Bounds = enemy4.getSprite().getGlobalBounds();
    sf::FloatRect enemy5Bounds = enemy5.getSprite().getGlobalBounds();
    sf::FloatRect enemy6Bounds = enemy6.getSprite().getGlobalBounds();

    sf::FloatRect firstBananaBounds = firstBanana.getSprite().getGlobalBounds();
    sf::FloatRect secondBananaBounds = secondBanana.getSprite().getGlobalBounds();
    sf::FloatRect thirdBananaBounds = thirdBanana.getSprite().getGlobalBounds();
    sf::FloatRect fourthBananaBounds = fourthBanana.getSprite().getGlobalBounds();
    sf::FloatRect fifthBananaBounds = fifthBanana.getSprite().getGlobalBounds();
    

  
    float bananasCollisionMargin = 80.0f;
    firstBananaBounds.left += bananasCollisionMargin;
    firstBananaBounds.width -= bananasCollisionMargin * 2;
    firstBananaBounds.top += bananasCollisionMargin;
    firstBananaBounds.height -= bananasCollisionMargin * 2;

    secondBananaBounds.left += bananasCollisionMargin;
    secondBananaBounds.width -= bananasCollisionMargin * 2;
    secondBananaBounds.top += bananasCollisionMargin;
    secondBananaBounds.height -= bananasCollisionMargin * 2;

    thirdBananaBounds.left += bananasCollisionMargin;
    thirdBananaBounds.width -= bananasCollisionMargin * 2;
    thirdBananaBounds.top += bananasCollisionMargin;
    thirdBananaBounds.height -= bananasCollisionMargin * 2;

    fourthBananaBounds.left += bananasCollisionMargin;
    fourthBananaBounds.width -= bananasCollisionMargin * 2;
    fourthBananaBounds.top += bananasCollisionMargin;
    fourthBananaBounds.height -= bananasCollisionMargin * 2;

    fifthBananaBounds.left += bananasCollisionMargin;
    fifthBananaBounds.width -= bananasCollisionMargin * 2;
    fifthBananaBounds.top += bananasCollisionMargin;
    fifthBananaBounds.height -= bananasCollisionMargin * 2;

  

    float enemyCollisionMargin = 150.0f;
    enemy1Bounds.left += enemyCollisionMargin;
    enemy1Bounds.width -= enemyCollisionMargin * 2;
    enemy1Bounds.top += enemyCollisionMargin;
    enemy1Bounds.height -= enemyCollisionMargin * 2;

    enemy2Bounds.left += enemyCollisionMargin;
    enemy2Bounds.width -= enemyCollisionMargin * 2;
    enemy2Bounds.top += enemyCollisionMargin;
    enemy2Bounds.height -= enemyCollisionMargin * 2;

    enemy3Bounds.left += enemyCollisionMargin;
    enemy3Bounds.width -= enemyCollisionMargin * 2;
    enemy3Bounds.top += enemyCollisionMargin;
    enemy3Bounds.height -= enemyCollisionMargin * 2;

    enemy4Bounds.left += enemyCollisionMargin;
    enemy4Bounds.width -= enemyCollisionMargin * 2;
    enemy4Bounds.top += enemyCollisionMargin;
    enemy4Bounds.height -= enemyCollisionMargin * 2;

    enemy5Bounds.left += enemyCollisionMargin;
    enemy5Bounds.width -= enemyCollisionMargin * 2;
    enemy5Bounds.top += enemyCollisionMargin;
    enemy5Bounds.height -= enemyCollisionMargin * 2;

    enemy6Bounds.left += enemyCollisionMargin;
    enemy6Bounds.width -= enemyCollisionMargin * 2;
    enemy6Bounds.top += enemyCollisionMargin;
    enemy6Bounds.height -= enemyCollisionMargin * 2;

    if (heroBounds.intersects(enemy1Bounds) || heroBounds.intersects(enemy2Bounds) ||
        heroBounds.intersects(enemy3Bounds) || heroBounds.intersects(enemy4Bounds) ||
        heroBounds.intersects(enemy5Bounds) || heroBounds.intersects(enemy6Bounds)) {
        gameOver = true;
    }


    if (firstBananaVisible && heroBounds.intersects(firstBananaBounds)) {
        countBananas++;
        firstBananaVisible = false;
    }

    if (secondBananaVisible && heroBounds.intersects(secondBananaBounds)) {
        countBananas++;
        secondBananaVisible = false;
    }

    if (thirdBananaVisible && heroBounds.intersects(thirdBananaBounds)) {
        countBananas++;
        thirdBananaVisible = false;
    }

    if (fourthBananaVisible && heroBounds.intersects(fourthBananaBounds)) {
        countBananas++;
        fourthBananaVisible = false;
    }

    if (fifthBananaVisible && heroBounds.intersects(fifthBananaBounds)) {
        countBananas++;
        fifthBananaVisible = false;
    }


    if (wasOnPlatform && !hero.getIsOnPlatform() && !hero.getIsJumping()) {
        hero.setIsJumping(true);
    }
}

void draw() {
    window.clear();

    window.setView(gameView);

    window.draw(backgroundSprite);
    window.draw(hero.getSprite());
    window.draw(enemy1.getSprite());
    window.draw(enemy2.getSprite());
    window.draw(enemy3.getSprite());
    window.draw(enemy4.getSprite());
    window.draw(enemy5.getSprite());

    for (auto& plataforma : platforms) {
        window.draw(plataforma.shape);
    }

    if (firstBananaVisible) window.draw(firstBanana.getSprite());
    if (secondBananaVisible) window.draw(secondBanana.getSprite());
    if (thirdBananaVisible) window.draw(thirdBanana.getSprite());
    if (fourthBananaVisible) window.draw(fourthBanana.getSprite());
    if (fifthBananaVisible) window.draw(fifthBanana.getSprite());

    if (gameOver) {
        sf::View currentView = window.getView();
        window.setView(window.getDefaultView());
        window.draw(gameOverText);
        window.setView(currentView);
    }

    if (gameWon) {
        sf::View currentView = window.getView();
        window.setView(window.getDefaultView());
        window.draw(gameWonText);
        window.setView(currentView);
    }

    window.display();
}

void updateCamera() {
    const float followSpeed = 5.0f;
    const float horizontalMargin = 50.0f;

    sf::Vector2f target = gameView.getCenter();
    sf::Vector2f playerPos = hero.getPosition();

    if (playerPos.x > gameView.getCenter().x + horizontalMargin) {
        target.x = playerPos.x - horizontalMargin;
    }
    else if (playerPos.x < gameView.getCenter().x - horizontalMargin) {
        target.x = playerPos.x + horizontalMargin;
    }

    target.x = std::max(worldBounds.left + gameView.getSize().x / 2, target.x);
    target.x = std::min(worldBounds.left + worldBounds.width - gameView.getSize().x / 2, target.x);

    target.y = viewSize.y / 2;

    gameView.setCenter(target);
}

void updateInput() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Space) {
                hero.jump(1200.0f);
            }
            else if (event.key.code == sf::Keyboard::Left) {
                playerMovingLeft = true;
                playerStandingLeft = false;
                playerMovingRight = false;
                playerStandingRight = false;
            }
            else if (event.key.code == sf::Keyboard::Right) {
                playerMovingRight = true;
                playerStandingRight = false;
                playerMovingLeft = false;
                playerStandingLeft = false;
            }
        }
        if (event.type == sf::Event::KeyReleased) {
            if (event.key.code == sf::Keyboard::Left) {
                playerMovingLeft = false;
                playerStandingLeft = true;
            }
            else if (event.key.code == sf::Keyboard::Right) {
                playerMovingRight = false;
                playerStandingRight = true;
            }
        }

        if (event.key.code == sf::Keyboard::Escape || event.type == sf::Event::Closed) {
            window.close();
        }
    }
}

void updateAutomatic(float dt) {
    static float timeInState = 0.0f;
    timeInState += dt;

    if (timeInState >= enemyMoveDuration) {
        timeInState = 0.0f;
        enemy1MovingRight = !enemy1MovingRight;
        enemy2MovingRight = !enemy2MovingRight;
        enemy3MovingRight = !enemy3MovingRight;
        enemy4MovingRight = !enemy4MovingRight;
        enemy5MovingRight = !enemy5MovingRight;
        
    }
}

void update(float dt) {
    if (gameOver || gameWon) return;
    float speed = 600.0f;
    float speedEnemy = 400.0f;
    float speedBat = 100.0f;
    hero.updateJumpPosition(dt);

    if (playerMovingLeft) {
        hero.move(-speed * dt, 0);
        hero.startWalkingLeftAnimation();
    }
    else if (playerMovingRight) {
        hero.move(speed * dt, 0);
        hero.startWalkingRightAnimation();
    }
    else if (playerStandingLeft) {
        hero.startStandingLeftAnimation();
    }
    else if (playerStandingRight) {
        hero.startStandingRightAnimation();
    }
    else {
        hero.startStandingRightAnimation();
    }

    
    if (!enemy1MovingRight) {
        enemy1.move(-speedEnemy * dt, 0);
        enemy1.startWalkingLeftAnimation();
    }
    else {
        enemy1.move(speedEnemy * dt, 0);
        enemy1.startWalkingRightAnimation();
    }

    if (!enemy2MovingRight) {
        enemy2.move(-speedBat * dt, 0);
        enemy2.startWalkingLeftAnimation();
    }
    else {
        enemy2.move(speedBat * dt, 0);
        enemy2.startWalkingRightAnimation();
    }

    if (!enemy3MovingRight) {
        enemy3.move(-speedEnemy * dt, 0);
        enemy3.startWalkingLeftAnimation();
    }
    else {
        enemy3.move(speedEnemy * dt, 0);
        enemy3.startWalkingRightAnimation();
    }

    if (!enemy4MovingRight) {
        enemy4.move(-speedEnemy * dt, 0);
        enemy4.startWalkingLeftAnimation();
    }
    else {
        enemy4.move(speedEnemy * dt, 0);
        enemy4.startWalkingRightAnimation();
    }

    if (!enemy5MovingRight) {
        enemy5.move(-speedBat * dt, 0);
        enemy5.startWalkingLeftAnimation();
    }
    else {
        enemy5.move(speedBat * dt, 0);
        enemy5.startWalkingRightAnimation();
    }

    if (countBananas == 5) {
        gameWon = true;
    }

    checkCollisions();
    enemy1.update();
    enemy2.update();
    enemy3.update();
    enemy4.update();
    enemy5.update();
    enemy6.update();
    hero.update();
    updateCamera();
}

int main() {
    sf::Clock clock;
    init();
    while (window.isOpen()) {
        updateInput();
        sf::Time dt = clock.restart();
        if (!gameOver || !gameWon) {
            update(dt.asSeconds());
            updateAutomatic(dt.asSeconds());
        }
        draw();
    }
    return 0;
}