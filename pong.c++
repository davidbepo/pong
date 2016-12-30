#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

int main(){
RenderWindow ventana(VideoMode(600,400), "pong");

RectangleShape barrai(Vector2f(20,100)); barrai.setFillColor(Color::Cyan);
RectangleShape barrad(Vector2f(20,100)); barrad.setFillColor(Color::Cyan);
int barraiy = 140, barrady = 140;

CircleShape bola(10); bola.setFillColor(Color::Cyan);
int bolax = 280, bolay = 180;

Font ubuntu; ubuntu.loadFromFile("Ubuntu-M.ttf");
Text ganai; ganai.setFont(ubuntu); ganai.setString("gana la \nbarra \nizkierda");
ganai.setCharacterSize(111); ganai.setFillColor(Color::Black);
Text ganad; ganad.setFont(ubuntu); ganad.setString("gana la \nbarra \nderecha");
ganad.setCharacterSize(111); ganad.setFillColor(Color::Black);

Text uj; uj.setFont(ubuntu); uj.setString("1 jugador");
uj.setCharacterSize(96); uj.setFillColor(Color::Black); uj.setPosition(64,52);

Text dj; dj.setFont(ubuntu); dj.setString("2 jugadores");
dj.setCharacterSize(96); dj.setFillColor(Color::Black); dj.setPosition(64,196);

Texture tcyan; tcyan.loadFromFile("tcyan.png");
Sprite flecha; flecha.setTexture(tcyan); flecha.setPosition(5,73);

int puntosi = 0, puntosd = 0;
char direccionx = 'd';
int angulo = -1;
int vbola = 4, vbarra = 3;
int pvictoria = 10;
int tipo = 0, jugadores = 1;

while (ventana.isOpen()){
	Event evento;
	while (ventana.pollEvent(evento)){
		if (evento.type == Event::Closed)
			ventana.close();
	}
	if (tipo == 0){
		if (Keyboard::isKeyPressed(Keyboard::Up)){
			flecha.setPosition(5,73);
			jugadores = 1;
		}
		if (Keyboard::isKeyPressed(Keyboard::Down)){
			flecha.setPosition(5,222);
			jugadores = 2;
		}
		if (Keyboard::isKeyPressed(Keyboard::Return)){
			tipo = jugadores;
		}
		ventana.clear(Color::White);
		ventana.draw(uj);
		ventana.draw(dj);
		ventana.draw(flecha);
		ventana.display();
		sleep(milliseconds(20));
	}
	
	if (tipo == 1){
		if (barraiy+50 > bolay and barraiy > 0)
			barraiy -= vbarra;
		if (barraiy+50 < bolay and barraiy < 300)
			barraiy += vbarra;
	}
	if (tipo == 2){
		if (Keyboard::isKeyPressed(Keyboard::W)and barraiy > 0)
			barraiy -= vbarra;
		if (Keyboard::isKeyPressed(Keyboard::S) and barraiy < 300)
			barraiy += vbarra;
	}
	if (tipo > 0){
		if (Keyboard::isKeyPressed(Keyboard::Up) and barrady > 0)
			barrady -= vbarra;
		if (Keyboard::isKeyPressed(Keyboard::Down) and barrady < 300)
			barrady += vbarra;
			
		int retraso = 0;
		int limited = 580, limitei = 0;
		if  (bolay-100 < barrady and barrady < bolay+10)
			limited = 560;
		if  (bolay-100 < barraiy and barraiy < bolay+10)
			limitei = 20;
		
		if (puntosi > 3 or puntosd > 3)
			vbola = 5;
		if (puntosi > 7 or puntosd > 7){
			vbola = 6;
			vbarra = 4;
		}
		
		if (direccionx == 'd')
			bolax += vbola;
		else
			bolax -= vbola;
		
		if (bolax > limited and limited == 560){
			direccionx = 'i';
			angulo += 2-(100+(barrady-bolay))/25;
		}
		if (bolax < limitei and limitei == 20){
			direccionx = 'd';
			angulo += 2-(100+(barraiy-bolay))/25;
		}
		
		if (bolay < 0 or bolay > 380)
			angulo = -angulo;
		
		bolay+=angulo;
		
		if (bolax >= 580){
			puntosi += 1;
			direccionx = 'i';
		}
		if (bolax <= 0){
			puntosd += 1;
			direccionx = 'd';
		}
		if (bolax >= 580 or bolax <= 0){
			bolax = 280;
			bolay = 180;
			angulo = -1;
			retraso = 500;
			barrady = 140;
			barraiy = 140;
		}
		
		barrai.setPosition(0,barraiy);
		barrad.setPosition(580,barrady);
		bola.setPosition(bolax,bolay);
	
		ventana.clear(Color::White);
		ventana.draw(barrai);
		ventana.draw(barrad);
		ventana.draw(bola);
		if (puntosi >= pvictoria){
			ventana.clear(Color::White);
			ventana.draw(ganai);
			ventana.setTitle("pong: gana la barra izkierda");
		}else if (puntosd >= pvictoria){
			ventana.clear(Color::White);
			ventana.draw(ganad);
			ventana.setTitle("pong: gana la barra derecha");
		}else
			ventana.setTitle("pong: " + to_string(puntosi) + " - " + to_string(puntosd));
		
		ventana.display();
	
		sleep(milliseconds(10+retraso));//limita a 100 fps + el retraso del sake
	}
}
}
