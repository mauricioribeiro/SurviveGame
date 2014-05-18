#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <time.h>

// Variaveis "globais"
// variaveis primitivas
int WINDOW_W = 800, WINDOW_H = 600, PLAYER_COLOR [3] = {255,255,255}, SCORE = 0, SECONDS = 0;
float PLAYER_SPEED = 5, PLAYER_SIZE = 10.0;
// matriz da velocidade que os inimigos irao correr por frame (coluna = numero de inimigos / linha = velocidade dos eixos X e Y)
const int ALL_ENEMIES = 12;
int enemy_run[ALL_ENEMIES][2];
int enemy_start[ALL_ENEMIES][2] = {0,0, 0,0, 0,0};

// variaveis nativas do SFML
sf::RenderWindow window(sf::VideoMode(WINDOW_W, WINDOW_H), "Survive - The Game");
sf::View display(sf::FloatRect(200, 200, 300, 200));
sf::Vector2f PLAYER_POS;
sf::CircleShape player(PLAYER_SIZE);
sf::CircleShape enemies[ALL_ENEMIES];
sf::String pscore;


// Funcoes do Jogo devem estar antes do main (Funcoes do jogo sempre comecam com "s_"
// movePlayer - move o player (obvio nao haha)
void s_movePlayer(){
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && PLAYER_POS.x < WINDOW_W-player.getLocalBounds().width) player.move(PLAYER_SPEED,0);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && PLAYER_POS.x > 0.0) player.move(-PLAYER_SPEED,0);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && PLAYER_POS.y < WINDOW_H-player.getLocalBounds().height) player.move(0,PLAYER_SPEED);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && PLAYER_POS.y > 0.0) player.move(0,-PLAYER_SPEED);
}

// moveEnemy - funcao responsavel por mover o inimigo de forma aleatoriamente (com colisao na parede e calculo para movimento contrario)
// Parametros: A forma e o numero do inimigo
void s_moveEnemy(sf::CircleShape e,int n_enemy){
	if(e.getPosition().x > WINDOW_W-e.getLocalBounds().width || e.getPosition().x < 0.0) enemy_run[n_enemy][0]*=-1;
	if(e.getPosition().y > WINDOW_H-e.getLocalBounds().height || e.getPosition().y < 0.0) enemy_run[n_enemy][1]*=-1;
}

bool s_verificarMorte(int n_enemy){
	int colisao_eixos = 0;
	if((int)PLAYER_POS.x >= (int)enemies[n_enemy].getPosition().x && (int)PLAYER_POS.x <= (int)enemies[n_enemy].getLocalBounds().width+enemies[n_enemy].getPosition().x) colisao_eixos += 1;
	if((int)PLAYER_POS.y >= (int)enemies[n_enemy].getPosition().y && (int)PLAYER_POS.y <= (int)enemies[n_enemy].getLocalBounds().height+enemies[n_enemy].getPosition().y) colisao_eixos += 1;
	if(colisao_eixos==2)
		return true;
	else
		return false;
}

int main()
{
	srand (time(NULL));
	// Criando e Configurando os objetos, texturas, entidades, etc...
	sf::Font font;
	if(!font.loadFromFile("fonts/arial.ttf")) return -1;

	sf::Text txt_welcome("Welcome to Survive. Press ESC to exit or ENTER to Play",font,16);
	sf::Text txt_credits("Survive BETA - FATEC Game Project | 2SEM - 2014",font,12);
	sf::Text txt_score("SCORE: "+(char)SCORE,font,14);

	player.setFillColor(sf::Color(PLAYER_COLOR[0],PLAYER_COLOR[1],PLAYER_COLOR[2]));
	player.setPosition((WINDOW_W-player.getLocalBounds().width)/2,WINDOW_H/2+player.getLocalBounds().height);

	for (int i =0; i<ALL_ENEMIES; i++){
	enemy_run[i][0]=rand()%10 + 1;
	enemy_run[i][1]=rand()%10 + 1;
	}

	window.setFramerateLimit(60);

	// molda os inimigos
	for(int i_enemy = 0; i_enemy < ALL_ENEMIES;i_enemy++){
		enemies[i_enemy].setRadius(PLAYER_SIZE);
		enemies[i_enemy].setFillColor(sf::Color((rand() % 155)+100,(rand() % 155)+100,(rand() % 155)+100)); //Random colors!!!
		enemies[i_enemy].setPosition(rand() % WINDOW_W,rand() % WINDOW_H); //Random positions!!!
	}

	txt_welcome.setColor(sf::Color::White);
	txt_welcome.setStyle(sf::Text::Bold);
	txt_welcome.setPosition((WINDOW_W-txt_welcome.getLocalBounds().width)/2,WINDOW_H/2+100);

	txt_credits.setColor(sf::Color::White);
	txt_credits.setPosition((WINDOW_W-txt_credits.getLocalBounds().width)/2,WINDOW_H/2+150);

	txt_score.setColor(sf::Color::White);
	txt_score.setStyle(sf::Text::Bold);
	txt_score.setPosition(20,WINDOW_H-20);	

	// Variavel responsavel pela execucao do jogo
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

			std::string pscore;
			std::stringstream out;
			out << SCORE;
			pscore = out.str();

			if(!DEAD){
				//Cria o score por segundos
				SECONDS++;
				if(SECONDS%260==0) SCORE++;

				// Chamando as funcoes criadas	
				s_movePlayer();

				for(int i_enemy = 0; i_enemy < ALL_ENEMIES; i_enemy++){
					s_moveEnemy(enemies[i_enemy],i_enemy);
					enemies[i_enemy].move(enemy_run[i_enemy][0],enemy_run[i_enemy][1]);
					window.draw(enemies[i_enemy]);
					if(DEAD==false) DEAD = s_verificarMorte(i_enemy);
				}

				txt_score.setString("SCORE: "+pscore);

				window.draw(player);
				window.draw(txt_score);

			} else {
				txt_welcome.setString("YOU ARE DEAD... your score is "+pscore+"\nPress ENTER to play again or ESC to exit");
				txt_welcome.setPosition((WINDOW_W-txt_welcome.getLocalBounds().width)/2,WINDOW_H/2+100);
				window.draw(txt_welcome);
				//reseta o jogo
 				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return)){
 					RUN = false; DEAD = false; SCORE = 0;
 				}
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

    return 0;
}
