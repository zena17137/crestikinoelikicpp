#include <SFML/Graphics.hpp>
#include <time.h>

using namespace sf;

bool svob[9] = { false };

class Stav {
public:
	Sprite sprite[9];
	bool tik[9];

	Stav(Texture& image) {
		for (int i = 0; i < 9; i++) {
			sprite[i].setTexture(image);
			tik[i] = false;
		}
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++)
				sprite[i * 3 + j].setPosition(200 * j, 200 * i);
	}

	void update(int& vid) {
		for (int i = 0; i < 9; i++)
			sprite[i].setTextureRect(IntRect(200 * (vid - 1), 0, 200, 200));
	}
};

int BotStav() {
	int res = 0;

	bool verno = false;
	while (!verno) {
		res = rand() % 9;

		if (!svob[res])
			verno = true;
		else
			verno = false;
	}

	return res;
}

int main() {
	srand(time(0));
	RenderWindow window(VideoMode(600, 600), "Tic tac toe!");

	Texture f;
	f.loadFromFile("C:/Users/Андрей/Desktop/Paint/fon.png");
	Sprite fon(f);

	Texture c;
	c.loadFromFile("C:/Users/Андрей/Desktop/Paint/crnol.png");
	Sprite vibor[2];
	for (int i = 0; i < 2; i++) {
		vibor[i].setTexture(c);
		vibor[i].setPosition(50 + 300 * i, 180);
	}
	int vib = 0;
	Stav player(c), bot(c);

	int sv = 0;

	Texture l;
	l.loadFromFile("C:/Users/Андрей/Desktop/Paint/line.png");
	Sprite line(l);
	bool win = false, hotbot = false;
	bool dumbot = false;

	while (window.isOpen())
	{
		Vector2i pos = Mouse::getPosition(window);
		
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();

			if (event.type == Event::MouseButtonPressed)
				if (event.key.code == Mouse::Left) {
					if (vib == 0) {
						for (int i = 0; i < 2; i++)
							if (vibor[i].getGlobalBounds().contains(pos.x, pos.y))
								vib = i + 1;
					}
					else
						for (int i = 0; i < 9; i++)
							if (player.sprite[i].getGlobalBounds().contains(pos.x, pos.y) && !svob[i]) {
								player.tik[i] = true;
								svob[i] = true;
								sv++;

								hotbot = true;
							}
				}
		}

		for (int i = 0; i < 2; i++)
			if (vibor[i].getGlobalBounds().contains(pos.x, pos.y))
				vibor[i].setTextureRect(IntRect(200 * i, 200, 200, 200));
			else
				vibor[i].setTextureRect(IntRect(200 * i, 0, 200, 200));

		bool winplay[8][2];
		for (int i = 0; i < 8; i++) {
			if (i < 3) {
				winplay[i][0] = player.tik[3 * i] && player.tik[1 + 3 * i] && player.tik[2 + 3 * i];
				winplay[i][1] = bot.tik[3 * i] && bot.tik[1 + 3 * i] && bot.tik[2 + 3 * i];
			}
			else if (i >= 3 && i < 6) {
				winplay[i][0] = player.tik[i - 3] && player.tik[i] && player.tik[i + 3];
				winplay[i][1] = bot.tik[i - 3] && bot.tik[i] && bot.tik[i + 3];
			}
			else if (i >= 6) {
				winplay[i][0] = player.tik[2 * (i - 6)] && player.tik[4] && player.tik[8 - 2 * (i - 6)];
				winplay[i][1] = bot.tik[2 * (i - 6)] && bot.tik[4] && bot.tik[8 - 2 * (i - 6)];
			}

			for (int j = 0; j < 2; j++)
				if (winplay[i][j]) {
					win = true;
					if (i < 3) {
						line.setTextureRect(IntRect(0, 0, 600, 10));
						int ly = 95 + 200 * i;
						line.setPosition(0, ly);
					}
					else if (i < 6) {
						line.setTextureRect(IntRect(0, 0, 600, 10));
						line.setRotation(90);
						int lx = 105 + 200 * (i - 3);
						line.setPosition(lx, 0);
					}
					else if (i == 6)
						line.setTextureRect(IntRect(0, 10, 600, 600));
					else if (i == 7)
						line.setTextureRect(IntRect(600, 10, -600, 600));
				}
		}

		if (hotbot && !win && sv < 9) {
			sv++;

			int botstav = 0;

			if (!dumbot) {
				botstav = BotStav();
				dumbot = true;
			}
			else {
				bool cdat = true;

				for (int i = 0; i < 3; i++) {
					if (player.tik[i] && player.tik[3 + i] && !svob[6 + i]) {
						botstav = 6 + i;
						cdat = false;
					}
					if (player.tik[6 + i] && player.tik[3 + i] && !svob[i]) {
						botstav = i;
						cdat = false;
					}
					if (player.tik[3 * i] && player.tik[1 + 3 * i] && !svob[2 + 3 * i]) {
						botstav = 2 + 3 * i;
						cdat = false;
					}
					if (player.tik[2 + 3 * i] && player.tik[1 + 3 * i] && !svob[3 * i]) {
						botstav = 3 * i;
						cdat = false;
					}
				}
				if (player.tik[0] && player.tik[4] && !svob[8]) {
					botstav = 8;
					cdat = false;
				}
				if (player.tik[8] && player.tik[4] && !svob[0]) {
					botstav = 0;
					cdat = false;
				}
				if (player.tik[2] && player.tik[4] && !svob[6]) {
					botstav = 6;
					cdat = false;
				}
				if (player.tik[6] && player.tik[4] && !svob[2]) {
					botstav = 2;
					cdat = false;
				}
				if (player.tik[2] && player.tik[6] && !svob[4]) {
					botstav = 4;
					cdat = false;
				}

				if (cdat)
					botstav = BotStav();
			}

			bot.tik[botstav] = true;
			svob[botstav] = true;

			hotbot = false;
		}

		player.update(vib);

		int biv = vib + 1;
		if (biv == 3)
			biv = 1;

		bot.update(biv);

		window.clear(Color::White);
		if (vib == 0)
			for (int i = 0; i < 2; i++)
				window.draw(vibor[i]);
		else {
			window.draw(fon);
			for (int i = 0; i < 9; i++) {
				if (player.tik[i])
					window.draw(player.sprite[i]);

				if (bot.tik[i])
					window.draw(bot.sprite[i]);
			}
		}
		if (win)
			window.draw(line);
		window.display();
	}

	return 0;
}