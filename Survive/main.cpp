#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <stdlib.h>

// Variaveis "globais"
// variaveis primitivas
int WINDOW_W = 800, WINDOW_H = 600, PLAYER_COLOR [3] = {255,255,255}, ENEMY_COLOR [3] = {200,2,7}, SCORE = 150;
float PLAYER_SPEED = 0.5,  PLAYER_SIZE = 10.0, ENEMY_SPEED = 0.2;
// matriz da velocidade que os inimigos ir�o correr por frame (coluna = numero de inimigos / linha = velocidade dos eixos X e Y)
const int ALL_ENEMIES = 3;
double enemy_run[ALL_ENEMIES][2] = {0.3,0.5, 0.8,0.5, 0.2,0.7};

// variaveis nativas do SFML
sf::RenderWindow window(sf::VideoMode(WINDOW_W, WINDOW_H), "Survive - The Game");
sf::View display(sf::FloatRect(200, 200, 300, 200));
sf::Vector2f PLAYER_POS;
sf::CircleShape player(PLAYER_SIZE), enemy_1(PLAYER_SIZE),enemy_2(PLAYER_SIZE),enemy_3(PLAYER_SIZE);

// Fun��es do Jogo devem estar antes do main (Fun��es do jogo sempre come�am com "s_"
// movePlayer - move o player (obvio n�o haha)
void s_movePlayer(){
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && PLAYER_POS.x < WINDOW_W-player.getLocalBounds().width) player.move(PLAYER_SPEED,0);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && PLAYER_POS.x > 0.0) player.move(-PLAYER_SPEED,0);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && PLAYER_POS.y < WINDOW_H-player.getLocalBounds().height) player.move(0,PLAYER_SPEED);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && PLAYER_POS.y > 0.0) player.move(0,-PLAYER_SPEED);
}

// moveEnemy - fun��o responsavel por mover o inimigo de forma aleatoriamente (com colis�o na parede e calculo para movimento contrario)
// Parametros: A forma e o numero do inimigo
void s_moveEnemy(sf::CircleShape e,int n_enemy){
	if(e.getPosition().x > WINDOW_W-e.getLocalBounds().width || e.getPosition().x < 0.0) enemy_run[n_enemy][0]*=-1;
	if(e.getPosition().y > WINDOW_H-e.getLocalBounds().height || e.getPosition().y < 0.0) enemy_run[n_enemy][1]*=-1;
}

bool s_verificarMorte(){
	int colisao_eixos = 0;
	if(PLAYER_POS.x >= enemy_1.getPosition().x || PLAYER_POS.x <= enemy_1.getLocalBounds().width+enemy_1.getPosition().x) colisao_eixos = 1;
	if(PLAYER_POS.y >= enemy_1.getPosition().y || PLAYER_POS.y <= enemy_1.getLocalBounds().height+enemy_1.getPosition().y) colisao_eixos += 1;
	if(colisao_eixos==2)
		return true;
	else
		return false;
}

int main()
{
	// Criando e Configurando os objetos, texturas, entidades, etc...
	sf::Font font;
	if(!font.loadFromFile("fonts/arial.ttf")) return -1;

	sf::Text txt_welcome("Welcome to Survive. Press ESC to exit or ENTER to Play",font,16);
	sf::Text txt_credits("Survive BETA - FATEC Game Project | 2SEM - 2014",font,12);
	sf::Text txt_score("SCORE: "+(char)SCORE,font,14);

	player.setFillColor(sf::Color(PLAYER_COLOR[0],PLAYER_COLOR[1],PLAYER_COLOR[2]));
	player.move((WINDOW_W-player.getLocalBounds().width)/2,WINDOW_H/2+player.getLocalBounds().height);
	enemy_1.setFillColor(sf::Color(ENEMY_COLOR[0],150,ENEMY_COLOR[2]));
	enemy_2.setFillColor(sf::Color(ENEMY_COLOR[0],ENEMY_COLOR[1],ENEMY_COLOR[2]));
	enemy_3.setFillColor(sf::Color(ENEMY_COLOR[0],ENEMY_COLOR[1],ENEMY_COLOR[2]));

	txt_welcome.setColor(sf::Color::White);
	txt_welcome.setStyle(sf::Text::Bold);
	txt_welcome.setPosition((WINDOW_W-txt_welcome.getLocalBounds().width)/2,WINDOW_H/2+100);

	txt_credits.setColor(sf::Color::White);
	txt_credits.setPosition((WINDOW_W-txt_credits.getLocalBounds().width)/2,WINDOW_H/2+150);

	txt_score.setColor(sf::Color::White);
	txt_score.setStyle(sf::Text::Bold);
	txt_score.setPosition(20,WINDOW_H-20);	

	// Variavel responsavel pela execu��o do jogo
	bool RUN = false, DEAD = false;

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

			// O JOGO!
			PLAYER_POS = player.getPosition();

			if(!DEAD){

				// Chamando as fun��es criadas	
				s_movePlayer();
				/**
				for(int i_enemy = 0; i_enemy < ALL_ENEMIES; i_enemy++){
					s_moveEnemy(enemy,i_enemy);
					enemy.move(enemy_run[i_enemy][0],enemy_run[i_enemy][1]);
					window.draw(enemy);
				}
				**/
				s_moveEnemy(enemy_1,0);
				s_moveEnemy(enemy_2,1);
				s_moveEnemy(enemy_3,2);

				enemy_1.move(enemy_run[0][0],enemy_run[0][1]);
				enemy_2.move(enemy_run[1][0],enemy_run[1][1]);
				enemy_3.move(enemy_run[2][0],enemy_run[2][1]);

				txt_score.setString("SCORE: ");//+SCORE);

				window.draw(player);
				window.draw(enemy_1);
				window.draw(enemy_2);
				window.draw(enemy_3);
				window.draw(txt_score);

				//DEAD = s_verificarMorte();

			} else {
				txt_welcome.setString("YOU ARE DEAD... your score is #SCORE");
				txt_welcome.setPosition((WINDOW_W-txt_welcome.getLocalBounds().width)/2,WINDOW_H/2+100);
				window.draw(txt_welcome);
			}

		} else {
			// O MENU!
			sf::Texture texture_bg;
			if(!texture_bg.loadFromFile("img/survive.jpg")) return -1;

			sf::Sprite sprite_bg(texture_bg);
			texture_bg.create(WINDOW_W, WINDOW_H);
			
			window.draw(sprite_bg);
			window.draw(txt_welcome);
			window.draw(txt_credits);
		}
		
        window.display();
    }
    printf("Carlos Viado");
    printf("Mauricio viadão");

    return 0;
}
