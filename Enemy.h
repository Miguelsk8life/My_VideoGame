#include <SFML/Graphics.hpp>
#include <vector>
#include <chrono>

class Enemy {
public:
	Enemy();
	void init(sf::Vector2f position, std::string routeImage1, std::string routeImage2, float scaleX, float scaleY);
	void updateFrame(int frameCount, const std::vector<sf::Texture>& frames);
	void startWalkingRightAnimation();
	void startWalkingLeftAnimation();
	void move(float dx, float dy);
	void update();
	sf::Sprite getSprite();
	sf::Vector2f getPosition();

private:
	sf::Sprite m_sprite;
	sf::Vector2f m_position;
	float m_mass;
	sf::Texture m_texture;
	static const int FrameCountWalkingRight = 2;
	static const int FrameCountWalkingLeft = 2;
	std::vector<sf::Texture> framesWalkingRight;
	std::vector<sf::Texture> framesWalkingLeft;
	int currentFrame = 0;
	std::chrono::steady_clock::time_point lastUpdate;
	bool isWalkingRight = false;
	bool isWalkingLeft = false;
	const std::chrono::nanoseconds ANIMATION_DURATION = std::chrono::milliseconds(200);
};