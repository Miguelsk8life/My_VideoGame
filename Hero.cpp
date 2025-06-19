#include "Hero.h"
#include <iostream>

Hero::Hero() {
}

Hero::~Hero() {
}

void Hero::init(sf::Vector2f position, float mass) {
    m_position = position;
    m_mass = mass;
    for (int j = 0; j < FrameCountStandingRight; j++) {
        m_texture.loadFromFile("Assets/graphics/monkey_basic_moveRight_orange" + std::to_string(j + 1) + ".png");
        framesStandingRight.push_back(m_texture);
    }

    for (int j = 0; j < FrameCountWalkingRight; j++) {
        m_texture.loadFromFile("Assets/graphics/monkey_basic_walkingRight_orange" + std::to_string(j + 1) + ".png");
        framesWalkingRight.push_back(m_texture);
    }

    for (int j = 0; j < FrameCountWalkingLeft; j++) {
        m_texture.loadFromFile("Assets/graphics/monkey_basic_walkingLeft_orange" + std::to_string(j + 1) + ".png");
        framesWalkingLeft.push_back(m_texture);
    }

    for (int j = 0; j < FrameCountStandingLeft; j++) {
        m_texture.loadFromFile("Assets/graphics/monkey_basic_moveLeft_orange" + std::to_string(j + 1) + ".png");
        framesStandingLeft.push_back(m_texture);
    }
    m_sprite.setTexture(framesStandingRight[0]);
    m_sprite.setScale(150.0f / framesStandingRight[0].getSize().x, 150.0f / framesStandingRight[0].getSize().y);

    m_sprite.setPosition(m_position);
    m_sprite.setOrigin(m_texture.getSize().x / 2, m_texture.getSize().y / 2);

    lastUpdate = std::chrono::steady_clock::now();
    update();
}

void Hero::update() {
    auto now = std::chrono::steady_clock::now();
    if (now - lastUpdate >= ANIMATION_DURATION) {
        if (isWalkingRight) {
            updateFrame(FrameCountWalkingRight, framesWalkingRight);
        }
        else if (isWalkingLeft) {
            updateFrame(FrameCountWalkingLeft, framesWalkingLeft);
        }
        else if (isStandingLeft) {
            updateFrame(FrameCountStandingLeft, framesStandingLeft);
        }
        else if (isStandingRight) {
            updateFrame(FrameCountStandingRight, framesStandingRight);
        }
        lastUpdate = now;
    }
}

void Hero::updateFrame(int frameCount, const std::vector<sf::Texture>& frames) {
    currentFrame = (currentFrame + 1) % frameCount;
    m_sprite.setTexture(frames[currentFrame]);
}

void Hero::updateJumpPosition(float dt) {
    if (isJumping) {
        m_force -= m_mass * m_gravity * dt;
        m_position.y -= m_force * dt;
        m_sprite.setPosition(m_position);

         if (m_position.y >= 675 * 0.90f + 10) {
            m_position.y = 675 * 0.90f + 10;
            m_force = 0;
            isJumping = false;
        }
    }

}



void Hero::setIsJumping(bool jumping) {
    isJumping = jumping;
}

void Hero::falling(float dt) {
    if (!isJumping) {
        float m_force = -1200.0f;
        m_force -= m_mass * m_gravity * dt;
        m_position.y -= m_force * dt;
        m_sprite.setPosition(m_position);

        if (m_position.y >= 675 * 0.90f + 10) {
            m_position.y = 675 * 0.90f + 10;
            m_force = 0;
            isJumping = false;
        }
    }

}

void Hero::jump(float velocity) {
    if (!isJumping) {
        m_force = velocity;
        isJumping = true;
        isWalkingRight = false;
        isStandingRight = false;
        isWalkingLeft = false;
        isStandingLeft = false;
    }
}

void Hero::move(float dx, float dy) {
    m_position.x += dx;
    m_position.y += dy;
    m_sprite.setPosition(m_position);
}

sf::Vector2f Hero::getPosition() {
    return m_sprite.getPosition();
}

sf::Sprite Hero::getSprite() {
    return m_sprite;
}

void Hero::startWalkingRightAnimation() {
    isWalkingRight = true;
    isStandingRight = false;
    isWalkingLeft = false;
    isStandingLeft = false;
}

void Hero::startWalkingLeftAnimation() {
    isWalkingLeft = true;
    isStandingLeft = false;
    isWalkingRight = false;
    isStandingRight = false;
}

void Hero::startStandingRightAnimation() {
    isStandingRight = true;
    isWalkingRight = false;
    isWalkingLeft = false;
    isStandingLeft = false;
}

void Hero::startStandingLeftAnimation() {
    isStandingLeft = true;
    isWalkingRight = false;
    isWalkingLeft = false;
    isStandingRight = false;
}