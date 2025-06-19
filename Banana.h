	#include <SFML/Graphics.hpp>
	#include <vector>

	class Banana {
	public:
		sf::Sprite m_sprite;
		sf::Vector2f m_position;
		sf::Texture m_texture;
		Banana(){
		}

		const sf::Sprite& getSprite() const {
			return m_sprite;
		}

		void init(sf::Vector2f position){
			m_position = position;
			if (!m_texture.loadFromFile("Assets/graphics/banana.png")) {
				std::cerr << "Error al cargar la textura de banana!" << std::endl;
			}
			m_sprite.setTexture(m_texture);
			m_sprite.setScale(150.0f / m_texture.getSize().x, 150.0f / m_texture.getSize().y);
			m_sprite.setOrigin(m_texture.getSize().x / 2, m_texture.getSize().y / 2);
			m_sprite.setPosition(m_position);
		}
	};