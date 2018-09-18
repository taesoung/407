#include <iostream>
#include <string.h>
#include <Windows.h>
#include <conio.h>


class Player
{
	char face[100] = "^__^";
	int pos;
public:
	Player() : pos(20)
	{
	}
	~Player() {}
	void move(int num) { pos += num; }
	int getPosition()const { return pos; }
	void checkRange(int screen_size) {
		if (pos < 0) pos = 0;
		if (pos >= screen_size - 1) pos = screen_size - 1;
	}
	void draw(char *screen, int screen_size) {
		checkRange(screen_size);
		strncpy(screen + pos, face, strlen(face));
	}
private:

};
class Enemy
{
	char face[100] = "@__@";
	char faceAttacked[100] = ">__<";
	int pos;
	int nAnimations = 0;
public:
	Enemy() : pos(80) {}
	~Enemy() {}
	void move(int num) { pos += num; }
	int getPosition() const{ return pos; }
	void checkRange(int screen_size) {
		if (pos < 0) pos = 0;
		if (pos >= screen_size - 1) pos = screen_size - 1;
	}
	void draw(char *screen,int screen_size) {
		checkRange(screen_size);
		strncpy(screen + pos, face, strlen(face));
	}
	void update() {
		if (nAnimations == 0) return;
		
	}
	void OnHit() {
		nAnimations = 30;
		strcpy(face, faceAttacked);
	}
private:

};
class Bullet
{
	char shape = '-';
	int pos;
public:
	Bullet(int pos) :pos(pos) {}
	~Bullet() {}

	void move(int num) { pos += num; }
	int getPosition() { return pos; }
	void checkRange(int screen_size) {
		if (pos < 0) pos = 0;
		if (pos >= screen_size - 1) pos = screen_size - 1;
	}
	void draw(char *screen, int screen_size) {
		checkRange(screen_size);
		screen[pos] = shape;
	}
	void update(const Player& player, const Enemy& enemy) {
		if (player.getPosition() < enemy.getPosition()) {
			move(+1);
		}
		else
			move(-1);
	}
private:

};

int main() {

	const int screen_size = 119;
	char screen[screen_size + 1 + 1];
	Player player;
	Enemy enemy;
	Bullet *pBullet = nullptr;
	while (true) {
		memset(screen, ' ', screen_size);
		if (kbhit()) {
			char key = getch();
			if (key == 27)break;
			if (key == -32)
				key = getch();
			// printf("%d", key);
			switch (key)
			{
			case 'a':case 75:
				player.move(-1);
				break;
			case 'd':case 77:
				player.move(1);
				break;
			case 32:
				if (pBullet == nullptr)
					pBullet = new Bullet(player.getPosition());
				break;
			default:
				break;
			}
		}
		player.draw(screen, screen_size);
		enemy.draw(screen, screen_size);
		if (pBullet != nullptr) {
			pBullet->draw(screen, screen_size);
				if (pBullet->getPosition() == enemy.getPosition()) {

					enemy.OnHit();
					delete pBullet;
					pBullet = nullptr;
				}
				else
				{
					pBullet->update(player, enemy);
				}
		}
		screen[screen_size] = '\r';
		screen[screen_size + 1] = '\0';

		std::cout << screen;
		Sleep(50);
	}



	return 0;
}