#include <stdio.h>
#include <string.h>
#include <Windows.h>
#include <conio.h>

class Player
{
	char face[100];
	int pos;
public:
	Player(int pos = 20, const char* face = "(^__^)") :pos(pos)
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
	void setDirection(Enemy *pEnemy) {


	}
private:

};
class Enemy
{
	int Hp;
	char face[100];
	char faceStay[100];
	char faceAttacked[100];
	int pos;
	int nAnimations;
public:
	Enemy(const char* face = "@__@", const char* faceAttacked = ">__<"
	) : pos(rand()%180), nAnimations(0),Hp(10) {
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
	int d​irection;
public:
	Bullet(int pos,int d​irection) :pos(pos) , d​irection(d​irection){}
	~Bullet() {}

	void move() { pos += d​irection; }
	int getPosition() { return pos; }
	void checkRange(int screen_size) {
		if (pos < 0) pos = 0;
		if (pos >= screen_size - 1) pos = screen_size - 1;
	}
	void draw(char *screen, int screen_size) {
		checkRange(screen_size);
		screen[pos] = shape;
	}
private:

};

int main() {

	const int screen_size = 119;
	char screen[screen_size + 1 + 1];
	Player player(20);
	Enemy *enemy = new Enemy[5];
	Bullet *pBullet[10] = {nullptr};
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
				for (int i = 0; i < 10;i++) {
					if (pBullet[i] == nullptr) {
						pBullet[i] = new Bullet(player.getPosition());
						break;
					}
				}
				break;
			default:
				break;
			}
		}
		player.draw(screen, screen_size);
		for (int i = 0; i < 5; i++) {
			if (enemy + i != nullptr) {
				enemy[i].draw(screen, screen_size);
			}
		}
	
        for (int i = 0; i < 10; i++) {
			if (pBullet[i] != nullptr) {
				pBullet[i]->draw(screen, screen_size);
				if (pBullet[i]->getPosition() == enemy[i].getPosition()) {

					enemy[i].OnHit();
					delete pBullet[i];
					pBullet[i] = nullptr;
				}
				else
				{

					pBullet[i]->move();
				}
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