#include <SFML/Graphics.hpp>
#include <cmath>

using namespace sf;
using namespace std;

int main(){
RenderWindow ventana(VideoMode(600,400), "pong");

Texture tfondo; tfondo.loadFromFile("fondo.jpg");
Sprite fondo; fondo.setTexture(tfondo);

Texture	tbarra; tbarra.loadFromFile("barra.png");
Sprite barrai; barrai.setTexture(tbarra);
Sprite barrad; barrad.setTexture(tbarra);
int barraiy = 140, barrady = 140;

Texture tbola; tbola.loadFromFile("bola.png");
Sprite bola; bola.setTexture(tbola);
int bolax = 280, bolay = 180;

Texture tganai; tganai.loadFromFile("ganai.png");
Sprite ganai; ganai.setTexture(tganai);
Texture tganad; tganad.loadFromFile("ganad.png");
Sprite ganad; ganad.setTexture(tganad);

int puntosi = 0, puntosd = 0;
char direccionx = 'd';
int angulo = -1;
int vbola = 4, vbarra = 3;
int pvictoria = 10;

while (ventana.isOpen()){
	Event evento;
	while (ventana.pollEvent(evento)){
		if (evento.type == Event::Closed)
			ventana.close();
	}
	if (Keyboard::isKeyPressed(Keyboard::Up) and barrady > 0)
		barrady -= vbarra;
	if (Keyboard::isKeyPressed(Keyboard::Down) and barrady < 300)
		barrady += vbarra;
	if (Keyboard::isKeyPressed(Keyboard::W)and barraiy > 0)
		barraiy -= vbarra;
	if (Keyboard::isKeyPressed(Keyboard::S) and barraiy < 300)
		barraiy += vbarra;
		
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
		angulo += 2 - (100+(barrady-bolay))/25;
	}
	if (bolax < limitei and limitei == 20){
		direccionx = 'd';
		angulo += 2 - (100+(barraiy-bolay))/25;
	}
	
	if (bolay < 0)
		angulo = abs(angulo);
	if (bolay > 380)
		angulo -= angulo*2;
	
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

	ventana.clear();
	ventana.draw(fondo);
	ventana.draw(barrai);
	ventana.draw(barrad);
	ventana.draw(bola);
	if (puntosi >= pvictoria){
		ventana.draw(ganai);
		ventana.setTitle("pong: gana la barra izkierda");
	}else if (puntosd >= pvictoria){
		ventana.draw(ganad);
		ventana.setTitle("pong: gana la barra derecha");
	}else
		ventana.setTitle("pong: " + to_string(puntosi) + " - " + to_string(puntosd));
	
	ventana.display();

	sleep(milliseconds(10+retraso));//limita a 100 fps + el retraso del sake
}
}
