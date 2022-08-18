#include <SFML/Graphics.hpp>

using namespace sf;

int main(void)
{
	RenderWindow app(VideoMode(256, 256), "puzzleGame");
	app.setFramerateLimit(60);

	Texture t;
	t.loadFromFile("images/15.png");

	int w = 64;	//퍼즐 하나의 폭 (전체이미지는 256x256)

	int grid[6][6] = { 0, };	//0은 벽을 의미

	Sprite sprite[17];

	int number = 1;

	//초기 이미지 및 타일설정
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			sprite[number].setTexture(t);
			sprite[number].setTextureRect((IntRect(j * w, i * w, w, w)));
			grid[i + 1][j + 1] = number;
			number++;
		}
	}
	while (app.isOpen())
	{
		Event e;
		while (app.pollEvent(e))
		{
			if (e.type == Event::Closed)
				app.close();
			if (e.type == Event::MouseButtonPressed) 
			{
				if (e.key.code == Mouse::Left)
				{
					//마우스로 누른 위치의 좌표화
					Vector2i pos = Mouse::getPosition(app);
					int x, y;		//grid에 대한 x행 y열
					x = pos.x / 64 + 1;
					y = pos.y / 64 + 1;

					int dx = 0, dy = 0;

					if (grid[y + 1][x] == 16) { dy = 1; dx = 0; }
					if (grid[y - 1][x] == 16) { dy = -1; dx = 0; }
					if (grid[y ][x+1] == 16) { dy = 0; dx = 1; }
					if (grid[y][x-1] == 16) { dy = 0; dx = -1; }

					//마우스로 누른 타일과 빈 칸의 위치바꿈
					int temp = grid[y][x];
					grid[y][x] = 16;
					grid[y + dy][x + dx] = temp;
				}
			}
		}
		app.clear(Color::White);
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				//해ㅐ당 행렬에 있는 숫다 가지도 오기
				int n = grid[i + 1][j + 1];

				sprite[n].setPosition(j * w, i * w);
				app.draw(sprite[n]);
			}
		}
		app.display();
	}
}