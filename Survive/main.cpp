#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

int main()
{
	int WINDOW_W = 800, WINDOW_H = 600, PLAYER_SPEED = 1, PLAYER_SIZE = 20.f, PLAYER_COLOR [3] = {133,184,235};
	sf::Vector2f PLAYER_POS;

    sf::RenderWindow window(sf::VideoMode(WINDOW_W, WINDOW_H), "Survive - The Game");
	sf::View display(sf::FloatRect(200, 200, 300, 200));
    sf::CircleShape player(PLAYER_SIZE);
	player.setFillColor(sf::Color::Color(PLAYER_COLOR[0],PLAYER_COLOR[1],PLAYER_COLOR[2]));

	sf::Font font;
	if(!font.loadFromFile("fonts/arial.ttf")) return -1;

	sf::Text text("Welcome to Survive. Press ESC to exit or ENTER to Play",font,16);
	text.setColor(sf::Color::White);
	text.setStyle(sf::Text::Bold);
	text.setPosition((WINDOW_W-text.getLocalBounds().width)/2,WINDOW_H/2+100);

	sf::Text credits("Survive BETA - FATEC Game Project | 2SEM - 2014",font,12);
	credits.setColor(sf::Color::White);
	credits.setPosition((WINDOW_W-credits.getLocalBounds().width)/2,WINDOW_H/2+150);

	sf::Texture texture_bg;
	texture_bg.create(WINDOW_W, WINDOW_H);
	if(!texture_bg.loadFromFile("img/survive.jpg")) return -1;

	bool RUN = false;

    while (window.isOpen())
    {
		window.clear();

		sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) RUN = true;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) window.close();
		
		if(RUN){

			//move the player!
			PLAYER_POS = player.getPosition();
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) player.setPosition(PLAYER_POS.x +PLAYER_SPEED, PLAYER_POS.y);
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) player.setPosition(PLAYER_POS.x -PLAYER_SPEED, PLAYER_POS.y);
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) player.setPosition(PLAYER_POS.x, PLAYER_POS.y -PLAYER_SPEED);
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) player.setPosition(PLAYER_POS.x, PLAYER_POS.y +PLAYER_SPEED);

			window.draw(player);

		} else {
			sf::Sprite sprite_bg(texture_bg);
			window.draw(sprite_bg);
			window.draw(text);
			window.draw(credits);
		}
		
        window.display();
    }

    return 0;
}