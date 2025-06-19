#include <SFML/Graphics.hpp>
#include <chrono>
#include <vector>

class Hero {
public:
    Hero();
    ~Hero();
    void init(sf::Vector2f position, float mass);
    void updateJumpPosition(float dt);
    void jump(float velocity);
    sf::Sprite getSprite();
    void update();
    void updateFrame(int frameCount, const std::vector<sf::Texture>& frames);
    void startStandingRightAnimation();
    void startWalkingRightAnimation();
    void startWalkingLeftAnimation();
    void startStandingLeftAnimation();
    void move(float dx, float dy);
    sf::Vector2f getPosition();

    float getForce() const { return m_force; }
    void setForce(float force) { m_force = force; }
    bool getIsJumping() const { return isJumping; }
    void setIsJumping(bool jumping);
    void falling(float dt);
    void setOnPlatform(bool inside) { isInsidePlatform = inside;};
    bool getIsOnPlatform() { return isInsidePlatform;}
    sf::Sprite m_sprite;

private:
    bool isInsidePlatform;
    sf::Texture m_texture;
    sf::Vector2f m_position;
    int jumpCount = 0;
    float m_mass;
    const float m_gravity = 9.80f;
    float m_force;
    static const int FrameCountStandingRight = 4;
    static const int FrameCountWalkingRight = 2;
    static const int FrameCountWalkingLeft = 2;
    static const int FrameCountStandingLeft = 4;
    std::vector<sf::Texture> framesStandingRight;
    std::vector<sf::Texture> framesWalkingRight;
    std::vector<sf::Texture> framesWalkingLeft;
    std::vector<sf::Texture> framesStandingLeft;
    int currentFrame = 0;
    std::chrono::steady_clock::time_point lastUpdate;
    bool isWalkingRight = false;
    bool isWalkingLeft = false;
    bool isStandingLeft = false;
    bool isStandingRight = false;
    bool isJumping = false;
    const std::chrono::nanoseconds ANIMATION_DURATION = std::chrono::milliseconds(200);
};

