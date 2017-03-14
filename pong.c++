#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

using namespace sf;
using namespace std;

inline unsigned int division(unsigned int dividendo, unsigned int divisor) {
    return (dividendo + (divisor/2)) / divisor;
}

int main() {
RenderWindow ventana(VideoMode(600,400), "pong");

Music boing; boing.openFromFile("Boing.ogg");
Music boingp; boingp.openFromFile("Boingp.ogg");
Music sii; sii.openFromFile("sii.ogg");

RectangleShape barrai(Vector2f(20,100)); barrai.setFillColor(Color::Cyan);
RectangleShape barrad(Vector2f(20,100)); barrad.setFillColor(Color::Cyan);

CircleShape bola(10); bola.setFillColor(Color::Cyan);

Font ubuntu; ubuntu.loadFromFile("Ubuntu-M.ttf");
Text gana("",ubuntu,77); gana.setFillColor(Color::Black);

Text uj("1 jugador",ubuntu,88); uj.setFillColor(Color::Black); uj.setPosition(64,10);
Text dj("2 jugadores",ubuntu,88); dj.setFillColor(Color::Black); dj.setPosition(64,110);
Text op("opciones",ubuntu,88); op.setFillColor(Color::Black); op.setPosition(64,210);

Text via("vista de la ia",ubuntu,48); via.setFillColor(Color::Black); via.setPosition(10,10);
Text nvia("300",ubuntu,60); nvia.setFillColor(Color::Black); nvia.setPosition(480,10);

Text vel("velocidad",ubuntu,48); vel.setFillColor(Color::Black); vel.setPosition(10,85);
Text nvel("5",ubuntu,60); nvel.setFillColor(Color::Black); nvel.setPosition(480,85);

Text delay("retraso del sake",ubuntu,48); delay.setFillColor(Color::Black); delay.setPosition(10,160);
Text ndelay("500",ubuntu,60); ndelay.setFillColor(Color::Black); ndelay.setPosition(480,160);

Text sonidos("activar sonidos",ubuntu,48); sonidos.setFillColor(Color::Black); sonidos.setPosition(10,235);
Text asonidos("si",ubuntu,60); asonidos.setFillColor(Color::Black); asonidos.setPosition(480,235);

Text aceptar("aceptar",ubuntu,66); aceptar.setFillColor(Color::Black); aceptar.setPosition(200,310);

Texture tcyan; tcyan.loadFromFile("tcyan.png");
Sprite flecha(tcyan);

uint_fast16_t vbolainicial = 4, vbarra = 3, vistaia = 300, rsake = 500;
bool sonidosactivados = true;
inicio:
ventana.setTitle("pong");
flecha.setPosition(5,73);
int barraiy = 140, barrady = 140, bolax = 280, bolay = 180;
uint_fast8_t vbola = vbolainicial, puntosi = 0, puntosd = 0;
char direccionx = 'd';
char ganador = ' ';
int_fast8_t angulo = -1;
uint_fast8_t pvictoria = 10;
uint_fast8_t modo = 0, seleccion = 1, reiniciar = 1, ajuste = 1, sakeinicial = 1;

while (ventana.isOpen()){
	Event evento;
	bool abajo=false,arriba=false,izkierda=false,derecha=false,enter=false;
	while (ventana.pollEvent(evento)){
		if (evento.type == Event::Closed)
			ventana.close();
		if (evento.type == Event::KeyReleased){
			arriba = (evento.key.code == Keyboard::Up);
			abajo = (evento.key.code == Keyboard::Down);
			izkierda = (evento.key.code == Keyboard::Left);	
			derecha = (evento.key.code == Keyboard::Right);
			enter = (evento.key.code == Keyboard::Return);
			if (evento.key.code == Keyboard::Escape)
				goto inicio;
		}
	}
	if (modo == 0){
		int posicion[4] = {0,30,130,235};
		if (arriba and seleccion > 1)
			seleccion -= 1;
		if (abajo and seleccion < 3)
			seleccion += 1;
		flecha.setPosition(5,posicion[seleccion]);
		if (enter){
			modo = seleccion;
			if (modo < 3)
				reiniciar = 1;
			else
				ajuste = 1;
		}
		ventana.clear(Color::White);
		ventana.draw(uj);
		ventana.draw(dj);
		ventana.draw(op);
		ventana.draw(flecha);
		ventana.display();
		sleep(milliseconds(20));
	}
	if (modo == 1){// codigo de la ia
		if (barraiy+40 > bolay and barraiy > 0 and bolax < vistaia and direccionx == 'i')
			barraiy -= vbarra;
		if (barraiy+40 < bolay and barraiy < 300 and bolax < vistaia and direccionx == 'i')
			barraiy += vbarra;
	}
	if (modo == 2){//codigo del segundo jugador
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
		
		if (puntosi < pvictoria and puntosd < pvictoria){
			int limited = 580, limitei = 0;
			if  (bolay < barrady+95 and barrady-15 < bolay)
				limited = 560;
			if  (bolay < barraiy+95 and barraiy-15 < bolay)
				limitei = 20;
			
			if (puntosi >= 3 or puntosd >= 3)
				vbola = vbolainicial + 1;
			if (puntosi >= 7 or puntosd >= 7){
				vbola = vbolainicial + 2;
				vbarra = 4;
			}
			
			if (direccionx == 'd')
				bolax += vbola;
			else
				bolax -= vbola;
			
			if (bolax > limited and limited == 560){
				direccionx = 'i';
				angulo += 2-division(100+(barrady-10-bolay),25);
				if (sonidosactivados) 
					boing.play();
			}
			if (bolax < limitei and limitei == 20){
				direccionx = 'd';
				angulo += 2-division(100+(barraiy-10-bolay),25);
				if (sonidosactivados) 
					boing.play();
			}
			
			if (bolay < 0 or bolay > 380){
				angulo = -angulo;
				if (sonidosactivados) 
					boingp.play();
			}
			bolay+=angulo;
			
			if (bolax >= 580){
				puntosi += 1;
				direccionx = 'i';
			}
			if (bolax <= 0){
				puntosd += 1;
				direccionx = 'd';
			}
			if (bolax <= 0 and modo == 1 and sonidosactivados)
				sii.play();
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
		}
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
		}
		if (puntosd >= pvictoria and not(puntosi >= pvictoria)){
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
			if (izkierda)
				reiniciar = 1;
			if (derecha)
				reiniciar = 0;
			if (reiniciar == 1)
				flecha.setPosition(20,280);
			else
				flecha.setPosition(200,280);
			if (enter){
				if (reiniciar == 0)
					ventana.close();
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
			sleep(milliseconds(20));//limita a 50 fps cuando alguien ha ganado
	}
	if (modo == 3){
		ventana.clear(Color::White);
		int posicion[][2] = {{0,400},{10,400},{85,400},{160,400},{235,400},{320,120}};
		int retraso = 0;
		
		if (arriba and ajuste > 1)
			ajuste -= 1;
		if (abajo and ajuste < 5)
			ajuste += 1;

		if (Keyboard::isKeyPressed(Keyboard::Right)){
			retraso = 130;	
			if (ajuste == 1 and vistaia < 600)
				vistaia += 10;
			if (ajuste == 2 and vbolainicial < 255)
				vbolainicial += 1;
			if (ajuste == 3 and rsake < 950)
				rsake += 50;
			if (ajuste == 4 and sonidosactivados == true)
				sonidosactivados = false;
		}
		if (Keyboard::isKeyPressed(Keyboard::Left)){
			retraso = 130;	
			if (ajuste == 1 and vistaia > 10)
				vistaia -= 10;
			if (ajuste == 2 and vbolainicial > 1)
				vbolainicial -= 1;
			if (ajuste == 3 and rsake > 50)
				rsake -= 50;
			if (ajuste == 4 and sonidosactivados == false)
				sonidosactivados = true;
		}
		nvia.setString(to_string(vistaia));
		nvel.setString(to_string(vbolainicial));
		ndelay.setString(to_string(rsake));
		if (sonidosactivados)
			asonidos.setString("si");
		else
			asonidos.setString("no");
		
		flecha.setPosition(posicion[ajuste][1],posicion[ajuste][0]);
		if (enter and ajuste == 5){
			vbola = vbolainicial;
			seleccion = 1;
			modo = 0;
		}
		ventana.draw(via); ventana.draw(nvia);
		ventana.draw(vel); ventana.draw(nvel);
		ventana.draw(delay); ventana.draw(ndelay);
		ventana.draw(sonidos); ventana.draw(asonidos);
		ventana.draw(aceptar);
		ventana.draw(flecha);
		ventana.display();
		sleep(milliseconds(20+retraso));
	}
}
}
