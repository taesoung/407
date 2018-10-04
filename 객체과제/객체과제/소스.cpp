#include <stdio.h>
#include <string.h>
#include <Windows.h>
#include <conio.h>
#include <time.h>
class Player
{
	int Hp;
	char face[100];
	char stayface[100];
	int pos;
	int magazine;
	int coolTime;
	int NotHpDownTime;
	bool change;
public:
	Player(int pos = 20, const char* face = "(^__^)") :pos(pos), magazine(10), coolTime(0), Hp(10), NotHpDownTime(60), change(false)
	{
		strcpy(this->face, face);
		strcpy(this->stayface, face);
	}
	~Player() {}
	void move(int num) { pos += num; }
	int getPosition()const { return pos; }
	int getHp() { return Hp; }
	int checkMagazine() { return magazine; }
	void loseBullet() {
		magazine--;
		if (magazine == 0) {
			coolTime = 120;
		}
		return;
	}
	void checkRange(int screen_size) {
		if (pos < 0) pos = 0;
		if (pos >= screen_size - 1) pos = screen_size - 1;
	}
	void draw(char *screen, int screen_size) {
		checkRange(screen_size);
		strncpy(screen + pos, face, strlen(face));
	}
	void update() {
		if (coolTime == 0) return;
		coolTime--;
		if (coolTime == 0)
			magazine = 10;
	}
	void changeFace() {
		if (change == true) {
			strcpy(this->face, "      ");
			change = false;
		}
		else {
			strcpy(this->face, stayface);
			change = true;
		}

	}
	void Hpupdate() {
		if (NotHpDownTime == 0) return;

		NotHpDownTime--;
		changeFace();
		if (NotHpDownTime == 0)
			strcpy(this->face, stayface);
	}

	void HpDown() {
		if (NotHpDownTime == 0) {
			Hp -= 2;
			NotHpDownTime = 60;
		}
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
	int poscoolTime;
	int nAnimations;
	bool die;
public:
	Enemy(const char* face = "@__@", const char* faceAttacked = ">__<"
	) : pos(rand() % 119), nAnimations(0), Hp(10), poscoolTime(60), die(false) {
		strcpy(this->face, face);
		strcpy(this->faceStay, face);
		strcpy(this->faceAttacked, faceAttacked);
	}
	~Enemy() {}

	int getPosition() const { return pos; }
	int getHp() { return Hp; }
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
		Hp--;
		nAnimations = 30;
		strcpy(face, faceAttacked);

	}
	int setDirection(Player *player) {

		if (player->getPosition() > this->getPosition())
			return 1;
		else
			return -1;
	}
	void posUpdate(int num) {

		poscoolTime--;
		if (poscoolTime == 0) {
			poscoolTime = 60;

			pos += num;
		}
	}
	void re() {
		Hp = 10;
		pos = rand() % 119;
		strcpy(face, faceStay);
		die = false;
	}
	int enemyDie() {
		if (die == false) {
			die = true;
			return 1;
		}
		else
			return 0;

	}
private:

};
class Bullet
{
	char shape = '-';
	int pos;
	int d​irection;
public:
	Bullet(int pos, int d​irection) :pos(pos), d​irection(d​irection) {}
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
	const int max_enemy = 5;
	char screen[screen_size + 1 + 1];
	Player player(20);
	Enemy *enemy = new Enemy[max_enemy];
	Bullet *pBullet[10] = { nullptr };

	const int MS_PER_FRAME = 16; // 16 ms 
	clock_t last_tick, current_tick, elapsed_ms;
	int direction = 1;
	int bulletNum = 0;

	int spawnTime = 0;
	int kill = 0;
	int lastTime = 0;
	while (true) {
		last_tick = clock();
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
				direction = -1;
				break;
			case 'd':case 77:
				player.move(1);
				direction = 1;
				break;
			case 32:
				if (player.checkMagazine() > 0) {
					pBullet[bulletNum++] = new Bullet(player.getPosition(), direction);
					player.loseBullet();
					if (bulletNum == 10)
						bulletNum = 0;
				}
				break;
			default:
				break;
			}
		}
		if (spawnTime == 180) {
			for (int i = 0; i < 5; i++) {
				if (enemy[i].getHp() == 0) {
					enemy[i].re();
					spawnTime = 0;
					break;
				}
			}
		}
		if (spawnTime < 180)
			spawnTime++;
		player.draw(screen, screen_size);
		for (int i = 0; i < 5; i++) {
			if (enemy[i].getHp() != 0) {
				enemy[i].draw(screen, screen_size);
			}
		}


		for (int i = 0; i < 10; i++) {
			if (pBullet[i] != nullptr) {
				pBullet[i]->draw(screen, screen_size);
				for (int j = 0; j < max_enemy; j++) {
					if (enemy[j].getHp() != 0) {
						if (pBullet[i]->getPosition() == enemy[j].getPosition()) {

							enemy[j].OnHit();
							delete pBullet[i];
							pBullet[i] = nullptr;
							break;
						}
						if (j == max_enemy - 1)
							pBullet[i]->move();

					}
				}
			}
		}
		player.update();
		player.Hpupdate();
		for (int i = 0; i < 5; i++) {
			if (enemy[i].getHp() != 0) {
				enemy[i].update();
				enemy[i].posUpdate(enemy[i].setDirection(&player));
				if (player.getPosition() - 6 < enemy[i].getPosition() && player.getPosition() + 8 > enemy[i].getPosition()) {
					player.HpDown();
				}

			}
			else
				kill += enemy[i].enemyDie();
		}
		screen[screen_size] = '\r';
		screen[screen_size + 1] = '\0';

		printf("%s", screen);
		lastTime++;
		if (player.getHp() <= 0)
			break;
		current_tick = clock();
		elapsed_ms = (current_tick - last_tick) * 1000 / CLOCKS_PER_SEC;
		if (elapsed_ms <= MS_PER_FRAME) {
			Sleep(MS_PER_FRAME - elapsed_ms);
		}

	}
	printf("총 생존시간 : %d초 , KILL : %d\n", lastTime / 60, kill);


	int not;
	scanf("%d", &not); //게임오버때 누르고있으면 바로끝나서 넣엇습니다.

	return 0;
}