#include <SFML/Graphics.hpp>
#include <unistd.h>
#include <random>

using namespace sf;
using namespace std;

int main(){
RenderWindow ventana(VideoMode(600, 400), "pong");

Texture tfondo; tfondo.loadFromFile("fondo.jpg");
Sprite fondo; fondo.setTexture(tfondo);

Texture	tbarra; tbarra.loadFromFile("barra.png");
Sprite barrai; barrai.setTexture(tbarra);
Sprite barrad; barrad.setTexture(tbarra);
int barraiy = 140, barrady = 140;
Texture tbola; tbola.loadFromFile("bola.png");
Sprite bola; bola.setTexture(tbola);
int bolax = 280, bolay = 180;

int puntosi = 0, puntosd = 0;
char direccionx = 'd', direcciony = 'a';
int aleatorio = 0;
int vbola = 4, vbarra = 3;

random_device rd;
default_random_engine rng(rd());
uniform_int_distribution<int> aleator(0,3);

while (ventana.isOpen()){
	Event evento;
	while (ventana.pollEvent(evento)){
		if (evento.type == Event::Closed)
			ventana.close();
	}
	if (Keyboard::isKeyPressed(Keyboard::Up) and barrady > 0)
		barrady-=vbarra;
	if (Keyboard::isKeyPressed(Keyboard::Down) and barrady < 280)
		barrady+=vbarra;
	if (Keyboard::isKeyPressed(Keyboard::W)and barraiy > 0)
		barraiy-=vbarra;
	if (Keyboard::isKeyPressed(Keyboard::S) and barraiy < 280)
		barraiy+=vbarra;
		
	int retraso = 0;	
	int limited=580,limitei=0;
	if  (bolay-104 < barrady and barrady < bolay+24)
		limited = 560;
	if  (bolay-104 < barraiy and barraiy < bolay+24)
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
	
	if (bolax > limited){
		direccionx = 'i';
		aleatorio = aleator(rng);
	}
	if (bolax < limitei){
		direccionx = 'd';
		aleatorio = aleator(rng);
	}
	
	if (bolay < 0)
		direcciony = 'b';
	if (bolay > 380)
		direcciony = 'a';
	
	if (direcciony == 'b')
		bolay+=aleatorio;
	else
		bolay-=aleatorio;
	
	if (bolax > 580){
		puntosi += 1;
		bolax = 280;
		bolay = 180;
		direccionx = 'i';
		aleatorio = 0;
		retraso = 500000;
		barrady = 140;
		barraiy = 140;
	}
	if (bolax < 0){
		puntosd += 1;
		bolax = 280;
		bolay = 180;
		direccionx = 'd';
		aleatorio = 0;
		retraso = 500000;
		barrady = 140;
		barraiy = 140;
	}
	
	barrai.setPosition(0,barraiy);
	barrad.setPosition(580,barrady);
	bola.setPosition(bolax,bolay);
	
	ventana.setTitle("pong: " + to_string(puntosi) + " - " + to_string(puntosd));

	ventana.clear();
	ventana.draw(fondo);
	ventana.draw(barrai);
	ventana.draw(barrad);
	ventana.draw(bola);
	/*if (puntosi > 9){
		ventana.draw(algo);
	}
	if (puntosd > 9){
		ventana.draw(algo);
	}*/
	ventana.display();
	
	usleep(10000+retraso);//limita a 100 fps + el retraso del sake
}
}
