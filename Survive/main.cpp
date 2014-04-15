#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Survive - The Game");
    sf::CircleShape player(50.f);

	//sf::Font font;
	//font.loadFromFile("arial.ttf");

	//sf::Text text("Welcome to Survive. Press ESC to exit, or ENTER to Play",font);
	//text.setCharacterSize(30);
	//text.setColor(sf::Color::Red);

	int color = 1;
	int run = 0;

    while (window.isOpen())
    {
		window.clear();

		sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return)){	
			run = 1;
		}
		
		if(run==1){
			sf::Vector2f player_position = player.getPosition();

			if(color==1){
				player.setFillColor(sf::Color::Red);
			} else {
				player.setFillColor(sf::Color::Green);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)){
				color = 1;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::G)){
				color = 0;
			}

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
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){	
				window.close();
			}

			window.draw(player);

		//} else {
			//window.draw(text);
		}

        window.display();
    }

    return 0;
}