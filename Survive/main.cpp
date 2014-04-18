#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

int main()
{
	int WINDOW_W = 800, WINDOW_H = 600, PLAYER_SPEED = 1, PLAYER_SIZE = 20.f, PLAYER_COLOR [3] = {133,184,235};

    sf::RenderWindow window(sf::VideoMode(WINDOW_W, WINDOW_H), "Survive - The Game");
	sf::View display(sf::FloatRect(200, 200, 300, 200));
    sf::CircleShape player(PLAYER_SIZE);
	player.setFillColor(sf::Color::Color(PLAYER_COLOR[0],PLAYER_COLOR[1],PLAYER_COLOR[2]));

	sf::Font font;
	if(!font.loadFromFile("fonts/arial.ttf")) return 0;

	sf::Text text("Welcome to Survive. Press ESC to exit, or ENTER to Play",font,14);
	text.setColor(sf::Color::White);
	text.setPosition((WINDOW_W-text.getLocalBounds().width)/2,WINDOW_H/2);

	int RUN = 0;

    while (window.isOpen())
    {
		window.clear();

		sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) RUN = 1;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) window.close();
		
		if(RUN==1){
			sf::Vector2f player_position = player.getPosition();

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){	
				player.setPosition(player_position.x +1, player_position.y);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){	
				player.setPosition(player_position.x -1, player_position.y);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){	
				player.setPosition(player_position.x, player_position.y -1);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){	
				player.setPosition(player_position.x, player_position.y +1);
			}

			window.draw(player);

		} else {
			window.draw(text);
		}
		
        window.display();
    }

    return 0;
}