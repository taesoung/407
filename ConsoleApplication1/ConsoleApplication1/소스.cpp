#include <stdio.h>
#include <string.h>
#include <Windows.h>
#include <conio.h>

class Player
{
	char face[100];
	int pos;
public:
	Player(int pos = 20 , const char* face ="(^__^)") :pos(pos)
	{
		strcpy(this->face, face);
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
	char face[100];
	char faceStay[100];
	char faceAttacked[100];
	int pos;
	int nAnimations;
public:
	Enemy(int pos = 80,const char* face = "@__@",const char* faceAttacked = ">__<"
	) : pos(pos), nAnimations(0){
		strcpy(this->face, face);
		strcpy(this->faceAttacked, faceAttacked);
	}
	~Enemy() {}
	void move(int num) { pos += num; }
	int getPosition() const { return pos; }
	void checkRange(int screen_size) {
		if (pos < 0) pos = 0;
		if (pos >= screen_size - 1) pos = screen_size - 1;
	}
	void draw(char *screen, int screen_size) {
		checkRange(screen_size);
		strncpy(screen + pos, face, strlen(face));
	}
	void update() {
		if (nAnimations == 0) return;
		nAnimations--;
		if (nAnimations == 0) {
			strcpy(face, faceStay);
		}
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
	Player player(20);
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
		enemy.update();
		screen[screen_size] = '\r';
		screen[screen_size + 1] = '\0';

		printf("%s", screen);
		Sleep(50);
	}



	return 0;
}