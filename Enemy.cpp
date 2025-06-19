#include "Enemy.h"
#include <iostream>

Enemy::Enemy() {
}


void Enemy::init(sf::Vector2f position, std::string routeImage1 , std::string routeImage2, float scaleX, float scaleY){
    m_position = position;
   
    for (int j = 0; j < FrameCountWalkingRight; j++) {
        if (!m_texture.loadFromFile(routeImage2 + std::to_string(j + 1) + ".png")) {
            std::cerr << "Error al cargar la textura!" << std::endl;
        }
        framesWalkingRight.push_back(m_texture);
    }

    for (int j = 0; j < FrameCountWalkingLeft; j++) {
        if (!m_texture.loadFromFile(routeImage1 + std::to_string(j + 1) + ".png")) {
            std::cerr << "Error al cargar la textura!" << std::endl;
        }
        framesWalkingLeft.push_back(m_texture);
    }

   
    m_sprite.setTexture(framesWalkingLeft[0]);
    m_sprite.setScale(scaleX, scaleY);
    m_sprite.setPosition(m_position);
    m_sprite.setOrigin(m_texture.getSize().x / 2, m_texture.getSize().y / 2);

    lastUpdate = std::chrono::steady_clock::now();
    update();
}

void Enemy::update() {
    auto now = std::chrono::steady_clock::now();
    if (now - lastUpdate >= ANIMATION_DURATION) {
        if (isWalkingRight) {
            updateFrame(FrameCountWalkingRight, framesWalkingRight);
        }
        else if (isWalkingLeft) {
            updateFrame(FrameCountWalkingLeft, framesWalkingLeft);
        }
        lastUpdate = now;
    }
}

void Enemy::updateFrame(int frameCount, const std::vector<sf::Texture>& frames) {
    currentFrame = (currentFrame + 1) % frameCount;
    m_sprite.setTexture(frames[currentFrame]);
}

void Enemy::move(float dx, float dy){
    m_position.x += dx;
    m_position.y += dy;
    m_sprite.setPosition(m_position);
}

sf::Vector2f Enemy::getPosition() {
    return m_sprite.getPosition();
}

sf::Sprite Enemy::getSprite() {
    return m_sprite;
}

void Enemy::startWalkingRightAnimation() {
    isWalkingRight = true; 
    isWalkingLeft = false;

}

void Enemy::startWalkingLeftAnimation() {
    isWalkingLeft = true;
    isWalkingRight = false;
}