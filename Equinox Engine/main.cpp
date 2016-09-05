#include "Precompiled.h"
//#include "Vector2Ext.h"
//#include <thread> //Use this for threading ?
#define DEBUG 1
using namespace std;
//WHAT NEXT:  Wormhole win animation. Use sin and cos to get ciruclar orbit of asteroids. Collision of asteroids gameover.

sf::Texture * getTexture(sf::Texture *p_texture, string location);
bool ballSelected(sf::Vector2i, sf::Vector2f);
void propText(sf::Text&, string,int,sf::Color,sf::Text::Style, sf::Vector2f); //add param for position
void printTest();
void orbVelocity(Ball *ball, Wormhole goal);
void InitAst(vector<Planet> planets, vector<Asteroid> *asteroids);
void InitPlanets(vector<Planet> *planets);
void customPlanets(vector<Planet> *planets);
void demoPlanets(vector<Planet> *planets);
int main() {
	// Start of setup
	const int height = 900;
	const int width = 1600;
	const float fps = 100;
	sf::Time accumulator = sf::Time::Zero;
	float dt = 1.f / fps;
	sf::Time clamp = sf::seconds(0.02f);
	sf::RenderWindow window(sf::VideoMode(width, height), "Equinox");
	vector<Planet> planets;
	vector<Asteroid> asteroids;
	Ball shape1(20.f, 50.f,100.f); //(1000.f,300.f) Orbit 1
	Ball *p_shape1 = &shape1;
	InitPlanets(&planets);
	//Planet planet1(&planets,50.f, 400.f, 225.f); //400.f, 225.f UNCOMMENT
	//Planet planet2(&planets, 100.f, 400.f, 675.f);
	//Planet planet3(&planets, 100.f, 1200.f, 225.f);//1200.f, 225.f UNCOMMENT
	//Planet planet4(&planets, 25.f, 1200.f, 675.f);
	Wormhole goal(25.f,1500.f,450.f); //Demo 1
	//Wormhole goal(100.f, 800.f, 450.f); //Orbit 1
	//Planet *p_planet1 = &planet1;
	InitAst(planets, &asteroids);
	cout << planets.size() << endl;
#pragma region InitArrow
	Arrow arrow(p_shape1,100,25);
	//Wormhole goal1;
	sf::Sprite background;
	//Arrow *p_arrow = &arrow;
	//arrow.setPosition(70.f, 100.f);
	//sf::Vector2f size(100, 25);
	//arrow.setSize(size);
	//arrow.setOrigin(0.f, 12.5f);
#pragma endregion
	sf::Font font;
	if (!font.loadFromFile("Roboto-Regular.ttf"))
		cout << "Font not loaded" << endl;
	sf::Text text;
	text.setFont(font);
	bool ballYSet = false;
	bool ballThrust = false;
	sf::Texture ballTexture;
	sf::Texture planetTexture;
	sf::Texture *p_planetTexture = &planetTexture;
	sf::Texture arrowTexture;
	sf::Texture backTexture;
	sf::Texture wormTexture;
	sf::Texture astTexture;
	sf::Texture *p_astTexture = &astTexture;
	shape1.setTexture(getTexture(&ballTexture,"equinox_ball_text_final.png"));
	p_planetTexture = getTexture(&planetTexture, "equinox_planet_text_final.png");
	for (int i = 0; i < planets.size(); i++) {
		planets[i].setTexture(p_planetTexture);
		//planets[i].setFillColor(sf::Color::Black);
	}
	//planet1.setTexture(getTexture(&planetTexture,"equinox_planet_text_final.png"));
	arrow.setTexture(getTexture(&arrowTexture, "equinox_arrow_text_final.png"));
	background.setTexture(*(getTexture(&backTexture, "equinox_background_image_final.png")));
	goal.setTexture(getTexture(&wormTexture, "equinox_wormhole_text_final.png"));
	p_astTexture = getTexture(&astTexture,"equinox_asteroid_text_final.png");
	for (int i = 0; i < asteroids.size(); i++) {
		asteroids[i].setTexture(p_astTexture);
	}
	window.setKeyRepeatEnabled(false);
	sf::Clock clock;

	while (window.isOpen()) {
		int looptime = 0;
		accumulator += clock.getElapsedTime();
		clock.restart();
		if (accumulator.asSeconds() > clamp.asSeconds())
			accumulator = clamp;

		//float vecMag = vec.magnitude();
		//cout << vecMag << endl;
		//shape1.setCentre();
#if DEBUG
		//shape1.printRadius();
		//shape1.printCentre();
#endif
		//updateGame(elapsed);
		sf::Vector2i *localPosition = &(sf::Mouse::getPosition(window));
		//sf::Vector2f mousePos(localPosition.x, localPosition.y);
		//sf::Vector2f ball1Centre(shape1.getPosition().x+20.f,shape1.getPosition().y+20.f);
		
		sf::Event event;
		//Start of input/physics loop
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::EventType::MouseButtonPressed) {
				if (event.key.code == sf::Mouse::Left) {
					if (ballYSet) {
						if (!ballThrust) {
							sf::Vector2f force = arrow.getForce(); //UNCOMMENT 
							p_shape1->thrustVelocity(force, 1); //UNCOMMENT
							//orbVelocity(p_shape1,goal); //Orbit
							ballThrust = true;
						}
					}
				}
			}
			if (event.type == sf::Event::EventType::KeyPressed) {
				if (event.key.code == sf::Keyboard::Return) {
					if (!ballYSet) {
						ballYSet = true;
						text.setString("The Ball has been aligned, press ESC to reset the position.");
					}
				}
				if (event.key.code == sf::Keyboard::Escape) {
					if (ballYSet) {
						ballYSet = false;
						if (ballThrust) {
							ballThrust = false;
							shape1.setRadius(20.f);
							shape1.setPosition(50.f, 100.f);
						}
						if (gameover || win) {
							ballYSet = false;
							ballThrust = false;
							win = false;
							gameover = false;
							shape1.setRadius(20.f);
							shape1.setPosition(50.f, 100.f);
						}
					}
				}
			}
		}
		if (!ballYSet) {
			sf::Vector2f textPos(200.f, 0.f);
			propText(text, "Use the mouse to align the ball in the y-axis. Once done, press enter.", 25, sf::Color::White, sf::Text::Regular, textPos);
			p_shape1->align(localPosition);
		}
		if (ballYSet) {
			if (!ballThrust) {
				arrow.update(localPosition);
			}
		}
		if (win) {
			text.setString("You have won the game! Press escape to restart.");
		}
		if (gameover) {
			text.setString("Game over! Press escape to restart.");
		}
		while (accumulator.asSeconds() > dt) {
			//p_shape1->circOrbit(&goal, dt);
			if (!gameover && !win && ballYSet && ballThrust) 
				p_shape1->update(planets, dt, &goal, asteroids); //UNCOMMENT
			goal.rotate(1);
			if (!gameover) {
				for (int i = 0; i < asteroids.size(); i++) {
					asteroids[i].rotate(1);
					asteroids[i].circOrbit(); //Circular orbit
				}
			}
			
			
			//p_shape1->update(&goal, dt);
			accumulator -= sf::seconds(dt);
			//cout << accumulator.asSeconds() << endl;
			//cout << "In second while loop" << endl;
		}
		//for (int i = 0; i < planets.size(); i++) {
			//planets[i].rotate(0.1);
		//}
		
		/*if (!ballYSet) {
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {
				ballYSet = true;
				text.setString("The Ball has been aligned, press ESC to reset the position.");
			}
			else {
				sf::Vector2f textPos(200.f, 0.f);
				propText(text, "Use the mouse to align the ball in the y-axis. Once done, press enter.", 25, sf::Color::White, sf::Text::Regular, textPos);
				p_shape1->align(localPosition);
			}
		}
		if (ballYSet) {
			if (!ballThrust) {
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
				{
					p_shape1->move(1, 0);
					planet1.rotate(0.01);
				}
				arrow.update(localPosition);
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
				{
					ballYSet = false;
				}
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				{
					sf::Vector2f force = arrow.getForce();
					p_shape1->thrustVelocity(force, 2.5);

					ballThrust = true;
				}
			}
			else if (ballThrust)
			{
				//Start of physics loop
				while (accumulator.asSeconds() > dt) {
					p_shape1->update(planets, dt);
					p_shape1->update(&goal, dt);
					accumulator -= sf::seconds(dt);
					//cout << accumulator.asSeconds() << endl;
					//cout << "In second while loop" << endl;
				}
			}
		}
		if (gameover || win) {
			if (win) {
				text.setString("You have won the game! Press enter to restart.");
			}
			if (gameover) {
				text.setString("Game over! Press enter to restart.");
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {
				ballYSet = false;
				ballThrust = false;
				win = false;
				gameover = false;
				p_shape1 = new Ball(20.f, 50.f, 100.f);
				p_shape1->setTexture(getTexture(&ballTexture, "equinox_ball_text_final.png"));
				arrow.update(localPosition);
			}
		}*/
			//End of input/physics loop
		//sf::Time elapsed = clock.restart(); //Keep track of time
#if DEBUG
		//cout << elapsed.asSeconds() << endl;
#endif
		//Start of rendering
		window.clear();
		window.draw(background);
		window.draw(*p_shape1);
		if (ballYSet && !(ballThrust))
			window.draw(arrow);
		for (int i = 0; i < planets.size(); i++) {
			window.draw(planets[i]);
		}
		for (int i = 0; i < asteroids.size(); i++) {
			window.draw(asteroids[i]);
		}
		window.draw(goal);
		//window.draw(planet1);
		window.draw(text);
		window.display();
	}
	//End of main loop
}


void propText(sf::Text &text, string strToDraw, int charSize, sf::Color color, sf::Text::Style textstyle, sf::Vector2f pos) {
	text.setString(strToDraw);
	text.setCharacterSize(charSize);
	//text.setColor(color);
	text.setStyle(textstyle);
	text.setPosition(pos.x, pos.y);
}

sf::Texture * getTexture(sf::Texture *p_texture, string location) {
	if (!p_texture->loadFromFile(location)) {
		cout << "Texture not loaded" << endl;
	}
	p_texture->setSmooth(true);
	return p_texture;
}

void printTest() {
	cout << "SEPERATE THREAD!" << endl;
}

void orbVelocity(Ball * ball,Wormhole goal) {
	sf::Vector2f orbRadius(ball->getPosition().x - goal.getPosition().x, ball->getPosition().y - goal.getPosition().y);
	cout << orbRadius.x << "," << orbRadius.y << endl;
	sf::Vector2f orbRadiusSquared(orbRadius.x*orbRadius.x, orbRadius.y*orbRadius.y);
	float magnitude = sqrtl(orbRadiusSquared.x + orbRadiusSquared.y);
	sf::Vector2f orbRadiusUnitVec = orbRadius / magnitude;
	cout << orbRadiusUnitVec.x << "," << orbRadiusUnitVec.y << endl;
	sf::Vector2f velocityUnitVec(orbRadiusUnitVec.y *(-1), orbRadiusUnitVec.x);
	cout << velocityUnitVec.x << "," << velocityUnitVec.y << endl;
	//float velocityX = (sqrtf(goal.getMass() / orbRadius.x))* velocityUnitVec.x;
	//float velocityY = (sqrtf(goal.getMass() / orbRadius.y))* velocityUnitVec.y;
	float speed = sqrtl(goal.getMass() / magnitude);
	cout << speed << endl;
	cout << goal.getMass() << endl;
	ball->m_velocity = sf::Vector2f(speed*velocityUnitVec.x, speed*velocityUnitVec.y);
	cout << ball->m_velocity.x << "," << ball->m_velocity.y << endl;
}


void InitAst(vector<Planet> planets, vector<Asteroid> *asteroids) {
	for (int i = 0; i < planets.size(); i++) {
		Asteroid ast(&planets[i], asteroids);
	}
}

void InitPlanets(vector<Planet> *planets) {
	string mystr;
	int choice;
	cout << "Would you like to: " << endl;
	cout << "1) Use a pre-existing demo" << endl;
	cout << "2) Set-up custom planets" << endl;
	do
	getline(cin, mystr);
	while (stoi(mystr) < 1 && stoi(mystr) > 2);
	choice = stoi(mystr);
	switch (choice) {
	case 1 :
		demoPlanets(planets);
		break;
	case 2:
		customPlanets(planets);
		break;
	}

}

void customPlanets(vector<Planet> *planets) {
	string mystr;
	int planetNum;
	float planetRadius;
	float planetX;
	float planetY;
	cout << "How many planets would you like to have?" << endl;
	getline(cin, mystr);
	planetNum = stoi(mystr);
	for (int i = 0; i < planetNum; i++) {
		cout << "Planet " << i + 1 << ": Enter Radius" << endl;
		getline(cin, mystr);
		planetRadius = stoi(mystr);
		cout << "Planet " << i + 1 << ": Enter X Pos" << endl;
		getline(cin, mystr);
		planetX = stoi(mystr);
		cout << "Planet " << i + 1 << ": Enter Y Pos" << endl;
		getline(cin, mystr);
		planetY = stoi(mystr);
		Planet planet(planets, planetRadius, planetX, planetY);
	}
}

void demoPlanets(vector<Planet> *planets) {
	string mystr;
	int choice;
	cout << endl;
	cout << "Which demo would you like?" << endl;
	cout << "Demo 1: Two suns. Top of screen. Left small, right big." << endl;
	cout << "Demo 2: Two suns. One top, one bottom. Top small, bottom big." << endl;
	cout << "Demo 3: Two suns. One top, one bottom. Top big, bottom small." << endl;
	cout << "Demo 4: Four suns. All 4 corners. Equal size. Small." << endl;
	cout << "Demo 5: Four suns. All 4 corners. Equal size. Big." << endl;
	do
	getline(cin, mystr);
	while (stoi(mystr) < 1 && stoi(mystr) > 4);
	choice = stoi(mystr);
	switch (choice) {
		case 1:
		{
			Planet planet1(planets, 50.f, 400.f, 225.f);
			Planet planet2(planets, 100.f, 1200.f, 225.f);
			break;
		}
		case 2:
		{
			Planet planet1(planets, 50.f, 800.f, 225.f);
			Planet planet2(planets, 100.f, 800.f, 675.f);
			break;
		}
		case 3:
		{
			Planet planet1(planets, 100.f, 800.f, 225.f);
			Planet planet2(planets, 50.f, 800.f, 675.f);
			break;
		}
		case 4:
		{
			Planet planet1(planets, 50.f, 400.f,225.f);
			Planet planet2(planets, 50.f, 1200.f,225.f);
			Planet planet3(planets, 50.f, 400.f, 675.f);
			Planet planet4(planets, 50.f, 1200.f, 675.f);
			break;
		}
		case 5:
		{
			Planet planet1(planets, 100.f, 400.f, 225.f);
			Planet planet2(planets, 100.f, 1200.f, 225.f);
			Planet planet3(planets, 100.f, 400.f, 675.f);
			Planet planet4(planets, 100.f, 1200.f, 675.f);
			break;
		}
	}
}
