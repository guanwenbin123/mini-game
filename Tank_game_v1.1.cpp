#include <iostream>
#include <windows.h>
#include <cstdlib>
#include <ctime>
#include <conio.h>
#include <vector>
using namespace std;

namespace GameEngine {
    struct Shot {  
        int x;
        int y;
        int dir;
        bool alive;
		bool isEnemy;
    };

    struct Tank { 
        int x;
        int y;
        int face;  
    };

    class BattleGame {
        private:
            vector<Tank> enemy;  
            Tank player; 
            vector<Shot> shots;  
            int score;  
            int playerAmmo; 
            int diff; 
            int frame;  
            int maxEnemy; 
        public:
            BattleGame(int d) { 
                diff = d;
                score = 0;
                frame = 0;
                player.x = 10;
                player.y = 10;
                player.face = 1;
                playerAmmo = (diff == 1) ? 5 : 999;  
                maxEnemy = (diff == 0) ? 1 : 3;  
                for(int i = 0; i < maxEnemy; i++) {
                    Tank e;
                    e.x = 20 + i * 5;
                    e.y = 10 + i * 3;
                    e.face = rand() % 4;
                    enemy.push_back(e);
                }
            }
            void MoveTo(int x, int y) {
                COORD pos = {x, y};
                HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
                SetConsoleCursorPosition(hOut, pos);
            }
            void HideCursor() {
                HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
                CONSOLE_CURSOR_INFO curInfo;
                GetConsoleCursorInfo(hOut, &curInfo);
                curInfo.bVisible = FALSE;
                SetConsoleCursorInfo(hOut, &curInfo);
            }
            char GetTankChar(int d) {
                switch(d) {
                    case 0: return '^';
                    case 1: return 'v';
                    case 2: return '<';
                    case 3: return '>';
                    default: return 'T';
                }
            }
            void PlayerFire() {
                if(diff == 1 && playerAmmo <= 0) return;  
                if(diff == 1) playerAmmo--;  
                Shot s;
                s.x = player.x;
                s.y = player.y;
                s.dir = player.face;
                s.alive = true;
                s.isEnemy = false;
                shots.push_back(s);
            }
            void EnemyFire(int eIndex) {
                Shot s;
                s.x = enemy[eIndex].x;
                s.y = enemy[eIndex].y;
                s.dir = enemy[eIndex].face;
                s.alive = true;
                s.isEnemy = true;
                shots.push_back(s);
            }
            void UpdateShots() {
                for(unsigned int i = 0; i < shots.size(); i++) {
                    if(shots[i].alive) {
                        MoveTo(shots[i].x, shots[i].y);
                        cout << " ";
                        switch(shots[i].dir) {
                            case 0: if(shots[i].y > 0) shots[i].y--; break;
                            case 1: if(shots[i].y < 24) shots[i].y++; break;
                            case 2: if(shots[i].x > 0) shots[i].x--; break;
                            case 3: if(shots[i].x < 79) shots[i].x++; break;
                        }
                        bool hitPlayer = false;
                        bool hitEnemy = false;
                        int hitIndex = -1;
                        if(shots[i].x == player.x && shots[i].y == player.y) {
                            MoveTo(35, 12);
                            cout << "GAME OVER!";
                            Sleep(2000);
                            exit(0);
                        }
                        for(unsigned int e = 0; e < enemy.size(); e++) {
                            if(shots[i].x == enemy[e].x && shots[i].y == enemy[e].y) {
                                hitEnemy = true;
                                hitIndex = e;
                                break;
                            }
                        }
                        if(hitEnemy) {
                            score += 10;
                            if(diff == 1) playerAmmo += 3; 
                            enemy[hitIndex].x = rand() % 80;
                            enemy[hitIndex].y = rand() % 25;
                            enemy[hitIndex].face = rand() % 4;
                            MoveTo(enemy[hitIndex].x, enemy[hitIndex].y);
                            cout << GetTankChar(enemy[hitIndex].face);
                            shots[i].alive = false;
                        }
                        if(shots[i].x <= 0 || shots[i].x >= 79 ||
                           shots[i].y <= 0 || shots[i].y >= 24) {
                            MoveTo(shots[i].x, shots[i].y);
                            cout << " ";
                            shots[i].alive = false;
                        }
                        if(shots[i].alive) {
                            MoveTo(shots[i].x, shots[i].y);
                            if(shots[i].isEnemy){
                            	cout << "+";
							} else{
                            	cout << "*";
                        	}
                        }
                    }
                }
                for(int i = shots.size() - 1; i >= 0; i--) {
                    if(!shots[i].alive) {
                        shots.erase(shots.begin() + i);
                    }
                }
            }
            void ShowStatus() {
                MoveTo(0, 0);
                cout << "Score: " << score;
                if(diff == 1) { 
                    cout << " Ammo: " << playerAmmo;
                }
                cout << "       "; 
            }
            int Run() {
                HideCursor();
                srand(time(NULL));
                system("cls");
                string diffName[3] = {"Easy", "Medium", "Hard"};
                cout << "Difficulty: " << diffName[diff] << endl;
                cout << "Controls: WASD-move, Space-fire, ESC-exit" << endl;
                if(diff == 1) cout << "Defeat enemies to get ammo!" << endl;
                cout << "Press any key to start...";
                _getch();
                system("cls");
                for(unsigned int i = 0; i < enemy.size(); i++) {
                    MoveTo(enemy[i].x, enemy[i].y);
                    cout << GetTankChar(enemy[i].face);
                }
                MoveTo(player.x, player.y);
                cout << GetTankChar(player.face);
                while(true) {
                    ShowStatus();
                    if(frame % 3 == 0) {
                        for(unsigned int i = 0; i < enemy.size(); i++) {
                            MoveTo(enemy[i].x, enemy[i].y);
                            cout << " ";
                            int dir = rand() % 4;
                            enemy[i].face = dir;
                            switch(dir) {
                                case 0: if(enemy[i].y > 0) enemy[i].y--; break;
                                case 1: if(enemy[i].y < 24) enemy[i].y++; break;
                                case 2: if(enemy[i].x > 0) enemy[i].x--; break;
                                case 3: if(enemy[i].x < 79) enemy[i].x++; break;
                            }
                            MoveTo(enemy[i].x, enemy[i].y);
                            cout << GetTankChar(enemy[i].face);
                        }
                    }
                    if(diff == 2 && frame % 30 == 0) {
                        for(unsigned int i = 0; i < enemy.size(); i++) {
                            if(rand() % 3 == 0) {  
                                EnemyFire(i);
                            }
                        }
                    }
                    frame++;
                    UpdateShots();  
                    if(_kbhit()) {
                        char key = _getch();
                        MoveTo(player.x, player.y);
                        cout << " ";
                        switch(key) {
                            case 'w':
                                if(player.y > 0) player.y--;
                                player.face = 0;
                                break;
                            case 's':
                                if(player.y < 24) player.y++;
                                player.face = 1;
                                break;
                            case 'a':
                                if(player.x > 0) player.x--;
                                player.face = 2;
                                break;
                            case 'd':
                                if(player.x < 79) player.x++;
                                player.face = 3;
                                break;
                            case ' ':
                                PlayerFire();
                                break;
                            case 27: 
                                return 0;
                        }
                         
                        MoveTo(player.x, player.y);
                        cout << GetTankChar(player.face);
                    }
                    Sleep(100); 
                }
                return 0;
            }
    };
}

int main() {
    int chosenDiff = 0;
    cout << "Select Difficulty:" << endl;
    cout << "0 - Easy (1 enemy, infinite ammo)" << endl;
    cout << "1 - Medium (3 enemies, limited ammo)" << endl;
    cout << "2 - Hard (3 enemies, they fire back)" << endl;
    cout << "Enter choice (0-2): ";
    cin >> chosenDiff;
    if(chosenDiff < 0 || chosenDiff > 2) chosenDiff = 0;

    GameEngine::BattleGame game(chosenDiff);
    game.Run();
    return 0;
}
