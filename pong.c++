#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

int main(){
RenderWindow ventana(VideoMode(600,400), "pong");

RectangleShape barrai(Vector2f(20,100)); barrai.setFillColor(Color::Cyan);
RectangleShape barrad(Vector2f(20,100)); barrad.setFillColor(Color::Cyan);

CircleShape bola(10); bola.setFillColor(Color::Cyan);

Font ubuntu; ubuntu.loadFromFile("Ubuntu-M.ttf");
Text gana; gana.setFont(ubuntu); gana.setCharacterSize(77); gana.setFillColor(Color::Black);

Text uj; uj.setFont(ubuntu); uj.setString("1 jugador");
uj.setCharacterSize(88); uj.setFillColor(Color::Black); uj.setPosition(64,10);
Text dj; dj.setFont(ubuntu); dj.setString("2 jugadores");
dj.setCharacterSize(88); dj.setFillColor(Color::Black); dj.setPosition(64,110);
Text op; op.setFont(ubuntu); op.setString("opciones");
op.setCharacterSize(88); op.setFillColor(Color::Black); op.setPosition(64,210);

Text via; via.setFont(ubuntu); via.setString("vista de la ia");
via.setCharacterSize(48); via.setFillColor(Color::Black); via.setPosition(10,10);
Text nvia; nvia.setFont(ubuntu); nvia.setString("300");
nvia.setCharacterSize(64); nvia.setFillColor(Color::Black); nvia.setPosition(480,10);

Text vel; vel.setFont(ubuntu); vel.setString("velocidad");
vel.setCharacterSize(48); vel.setFillColor(Color::Black); vel.setPosition(10,110);
Text nvel; nvel.setFont(ubuntu); nvel.setString("5");
nvel.setCharacterSize(64); nvel.setFillColor(Color::Black); nvel.setPosition(480,110);

Text delay; delay.setFont(ubuntu); delay.setString("retraso del sake");
delay.setCharacterSize(48); delay.setFillColor(Color::Black); delay.setPosition(10,210);
Text ndelay; ndelay.setFont(ubuntu); ndelay.setString("500");
ndelay.setCharacterSize(64); ndelay.setFillColor(Color::Black); ndelay.setPosition(480,210);

Text aceptar; aceptar.setFont(ubuntu); aceptar.setString("aceptar");
aceptar.setCharacterSize(66); aceptar.setFillColor(Color::Black); aceptar.setPosition(200,310);

Texture tcyan; tcyan.loadFromFile("tcyan.png");
Sprite flecha; flecha.setTexture(tcyan);

unsigned int vbolainicial = 4, vbarra = 3;
unsigned int vistaia = 300, rsake = 500;
inicio:
ventana.setTitle("pong");
flecha.setPosition(5,73);
int barraiy = 140, barrady = 140;
int bolax = 280, bolay = 180;
unsigned int vbola = vbolainicial;
unsigned int puntosi = 0, puntosd = 0;
char direccionx = 'd';
char ganador = ' ';
int angulo = -1;
int pvictoria = 10;
unsigned int modo = 0, seleccion = 1, reiniciar = 1, ajuste = 1;
unsigned int sakeinicial = 1;

while (ventana.isOpen()){
	Event evento;
	bool abajo=false,arriba=false,izkierda=false,derecha=false,enter=false;
	while (ventana.pollEvent(evento)){
		if (evento.type == Event::Closed)
			cerrar:
			ventana.close();
		if (evento.type == Event::KeyReleased){
			if(evento.key.code == Keyboard::Up)
				arriba = true;
			if (evento.key.code == Keyboard::Down)
				abajo = true;
			if (evento.key.code == Keyboard::Left)
				izkierda = true;
			if (evento.key.code == Keyboard::Right)
				derecha = true;
			if (evento.key.code == Keyboard::Return)
				enter = true;
		}
	}
	if (modo == 0){
		int posicion[4] = {0,30,130,230};
		if (arriba){
			if (seleccion > 1)
				seleccion -= 1;
		}
		if (abajo){
			if (seleccion < 3)
				seleccion += 1;
		}
		flecha.setPosition(5,posicion[seleccion]);
		if (enter){
			modo = seleccion;
			if (modo < 3)
				flecha.setPosition(20,280);
			else{
				flecha.setPosition(400,20);
				ajuste = 1;
			}
		}
		ventana.clear(Color::White);
		ventana.draw(uj);
		ventana.draw(dj);
		ventana.draw(op);
		ventana.draw(flecha);
		ventana.display();
		sleep(milliseconds(20));
	}
	
	if (modo == 1){
		if (barraiy+50 > bolay and barraiy > 0 and bolax < vistaia)
			barraiy -= vbarra;
		if (barraiy+50 < bolay and barraiy < 300 and bolax < vistaia)
			barraiy += vbarra;
	}
	if (modo == 2){
		if (Keyboard::isKeyPressed(Keyboard::W) and barraiy > 0)
			barraiy -= vbarra;
		if (Keyboard::isKeyPressed(Keyboard::S) and barraiy < 300)
			barraiy += vbarra;
	}
	if (modo == 1 or modo == 2){
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
			vbola = vbolainicial + 1;
		if (puntosi > 7 or puntosd > 7){
			vbola = vbolainicial + 2;
			vbarra = 4;
		}
		
		if (direccionx == 'd')
			bolax += vbola;
		else
			bolax -= vbola;
		
		if (bolax > limited and limited == 560){
			direccionx = 'i';
			angulo += 2-(100+(barrady-bolay))/20;
		}
		if (bolax < limitei and limitei == 20){
			direccionx = 'd';
			angulo += 2-(100+(barraiy-bolay))/20;
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
		if (bolax >= 580 or bolax <= 0 or sakeinicial == 1){
			sakeinicial = 0;
			bolax = 280;
			bolay = 180;
			angulo = -1;
			retraso = rsake;
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
		if (puntosi >= pvictoria and not(puntosd >= pvictoria)){
			ganador = 'i';
			if (modo == 1){
				gana.setString("gana la IA. \nreiniciar? \n\n      si       no");
				ventana.setTitle("pong: ha ganado la IA");
			}
			if (modo == 2){
				gana.setString("gana la izkierda. \nreiniciar? \n\n      si       no");
				ventana.setTitle("pong: ha ganado la barra izkierda");
			}
		}if (puntosd >= pvictoria and not(puntosi >= pvictoria)){
			ganador = 'd';
			if (modo == 1){
				gana.setString("tu ganas. \nreiniciar? \n\n      si       no");
				ventana.setTitle("pong: has ganado");
			}
			if ( modo == 2){
				gana.setString("gana la derecha. \nreiniciar? \n\n      si       no");
				ventana.setTitle("pong: ha ganado la barra derecha");
			}
		}

		if (ganador != ' '){
			ventana.clear(Color::White);
			ventana.draw(gana);
			if (izkierda){
				flecha.setPosition(20,280);
				reiniciar = 1;
			}
			if (derecha){
				flecha.setPosition(200,280);
				reiniciar = 0;
			}
			if (enter){
				if (reiniciar == 0)
					goto cerrar;
				else
					goto inicio;
			}
			ventana.draw(flecha);
		}else
			ventana.setTitle("pong: " + to_string(puntosi) + " - " + to_string(puntosd));
		
		ventana.display();
		if (puntosi < pvictoria and puntosd < pvictoria)
			sleep(milliseconds(10+retraso));//limita a 100 fps + el retraso del sake
		else
			sleep(milliseconds(10));//limita a 100 fps
	}
	if (modo == 3){
		ventana.clear(Color::White);
		int posicion[5][2] = {{0,400},{20,400},{120,400},{220,400},{320,120}};
		int retraso = 0;
		if (arriba){
			if (ajuste > 1)
				ajuste -= 1;
		}
		if (abajo){
			if (ajuste < 4)
				ajuste += 1;
		}
		if (Keyboard::isKeyPressed(Keyboard::Right)){
			retraso = 130;	
			if (ajuste == 1 and vistaia < 600)
				vistaia += 10;
			if (ajuste == 2 and vbolainicial < 999)
				vbolainicial += 1;
			if (ajuste == 3 and rsake < 950)
				rsake += 50;
		}
		if (Keyboard::isKeyPressed(Keyboard::Left)){
			retraso = 130;	
			if (ajuste == 1 and vistaia > 10)
				vistaia -= 10;
			if (ajuste == 2 and vbolainicial > 1)
				vbolainicial -= 1;
			if (ajuste == 3 and rsake > 50)
				rsake -= 50;
		}
		nvia.setString(to_string(vistaia));
		nvel.setString(to_string(vbolainicial));
		ndelay.setString(to_string(rsake));
		flecha.setPosition(posicion[ajuste][1],posicion[ajuste][0]);
		if (enter and ajuste == 4){
			vbola = vbolainicial;
			seleccion = 1;
			modo = 0;
			flecha.setPosition(5,30);
		}
		ventana.draw(via); ventana.draw(nvia);
		ventana.draw(vel); ventana.draw(nvel);
		ventana.draw(delay); ventana.draw(ndelay);
		ventana.draw(aceptar);
		ventana.draw(flecha);
		ventana.display();
		sleep(milliseconds(20+retraso));
	}
}
}
