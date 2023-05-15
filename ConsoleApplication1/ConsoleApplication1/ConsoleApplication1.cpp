#include <iostream>
#include<SFML/Audio.hpp>
#include<SFML/Graphics.hpp>
#include<cstdlib>
using namespace sf;
using namespace std;
int main()
{
	RenderWindow window(VideoMode(600, 600), "SFMLTuto");
	Music music;
	music.openFromFile("audio/Going-Up.ogg");
	music.setVolume(20);
	music.play();
	music.setLoop(true);

	Music fall;
	fall.openFromFile("audio/tt.ogg");
	fall.setVolume(20);

	Music collect;
	collect.openFromFile("audio/collect.ogg");
	collect.setVolume(20);


	Texture backgroundTexture;
	backgroundTexture.loadFromFile("images/background.png");
	Sprite backgroundSprite(backgroundTexture);

	window.setFramerateLimit(60);

	Texture basket;
	basket.loadFromFile("images/basket.png");
	Sprite basketSprite(basket);
	basketSprite.setPosition(Vector2f(270.0f, 500.0f));
	basketSprite.setScale(0.13f, 0.125f);

	Texture apple;
	apple.loadFromFile("images/apple.png");
	Sprite appleSprite(apple);
	appleSprite.setScale(0.05f, 0.05f);
	appleSprite.setPosition(Vector2f(250.0f, 0.0f));

	Font font; 
	font.loadFromFile("font/Abaddon Bold.ttf");
	Text scoreZone;
	scoreZone.setFont(font);
	scoreZone.setCharacterSize(24);
	scoreZone.setPosition(480, 20);
	
	Texture GO;
	GO.loadFromFile("images/game_over.png");
	Sprite GOSprite(GO);
	GOSprite.setScale(0.47f, 0.47f);
	GOSprite.setPosition(Vector2f(150.0f, 150.0f));

	
	Font font2; 
	font2.loadFromFile("font/game_over.ttf");
	Text game_over;
	game_over.setFont(font2);
	game_over.setCharacterSize(48);
	game_over.setFillColor(sf::Color::Red);
	game_over.setPosition(260, 341);
	

	int score = 0;
	int pointsEarned = 100;
	float deltaTime = 0.035f; // replace with actual delta time
	float playerSpeed = 64;
	float playerJumpSpeed = 150;
	float playerGravity = 300;
	float playerYVelocity = 0;
	int heart=3;
	bool isDead = false;

	int h1 = 0;
	int h2 = 0;
	int h3 = 0;

	Texture t1;
	Texture t2;
	t1.loadFromFile("images/heart_alive.png");	
	t2.loadFromFile("images/heart_dead.png");

	
	Sprite heart2[2];
	heart2[0] = Sprite(t1);
	heart2[1] = Sprite(t2);
	heart2[1].setScale(3.0f, 3.0f);
	heart2[1].setPosition(60, 20);
	heart2[0].setScale(3.0f, 3.0f);
	heart2[0].setPosition(60, 20);

	Sprite heart3[2];
	heart3[0] = Sprite(t1);
	heart3[1] = Sprite(t2);
	heart3[1].setScale(3.0f, 3.0f);
	heart3[1].setPosition(100, 20);
	heart3[0].setScale(3.0f, 3.0f);
	heart3[0].setPosition(100, 20);

	Sprite heart1[2];
	heart1[0] = Sprite(t1);
	heart1[1] = Sprite(t2);
	heart1[1].setScale(3.0f, 3.0f);
	heart1[1].setPosition(20, 20);
	heart1[0].setScale(3.0f, 3.0f);
	heart1[0].setPosition(20, 20);


	auto checkCollision = [](const Sprite& basketSprite, const Sprite& appleSprite)
	{
		return basketSprite.getGlobalBounds().intersects(appleSprite.getGlobalBounds());
	};

	
	 while (window.isOpen())
	{
		 
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				window.close();
			}
		}

		playerYVelocity += playerGravity * deltaTime;
		appleSprite.move(0, playerYVelocity * deltaTime);

		if ((appleSprite.getPosition().y > 600) && (appleSprite.getPosition().x > 600))
		{
			int pos = rand() % 580;
			appleSprite.setPosition(pos, 0);
			playerYVelocity = 0;

			score += pointsEarned;
			scoreZone.setString("Score: " + std::to_string(score));
			
		}


		if ((appleSprite.getPosition().y > 600) && (appleSprite.getPosition().x < 600))
		{
			heart--;
			if (heart>=1)
			{
				int pos = rand() % 580;
				appleSprite.setPosition(pos, 0);
				playerYVelocity = 0;
				
			}
			
			
		}


		if (heart == 3)
		{
			h1 = 0;
			h2 = 0;
			h3 = 0;
		}
		else if (heart == 2)
		{
			h3 = 1;
		}
		else if (heart == 1)
		{
			h2 = 1;
		}
		else
		{
			h1 =1 ;
			isDead = true;
		
		}
		
		if (((Keyboard::isKeyPressed(Keyboard::Q)) || (Keyboard::isKeyPressed(Keyboard::Left))) && (basketSprite.getPosition().x >-0)) {
			basketSprite.move(-10,0);
		}
		if (((Keyboard::isKeyPressed(Keyboard::D)) || (Keyboard::isKeyPressed(Keyboard::Right))) && (basketSprite.getPosition().x <500))
		{
			basketSprite.move(10,0);
		}

		if (checkCollision(basketSprite, appleSprite))
		{
			appleSprite.setPosition(appleSprite.getPosition().x +1000, appleSprite.getPosition().y+1000);
			collect.play();
		}
		
		window.clear();
		window.draw(backgroundSprite);

		window.draw(heart1[h1]);
		window.draw(heart2[h2]);
		window.draw(heart3[h3]);

		window.draw(appleSprite);
		window.draw(basketSprite);

		window.draw(scoreZone);

		if (isDead) 
		{
			music.stop();
			game_over.setString("Score: " + to_string(score));
			window.draw(GOSprite);
			window.draw(game_over);

			Event event;
			while (window.pollEvent(event))
			{
				fall.play();
			}
		}
		window.display();
	}
	return 0;
}
