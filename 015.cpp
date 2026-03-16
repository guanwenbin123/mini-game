#include <iostream>
#include <windows.h>
#include <cstdlib>
#include <ctime>
#include <conio.h>
#include <vector>
using namespace std;

namespace GameEngine {
    struct Projectile {
        int positionX;
        int positionY;
        int travelDirection;
        bool isActive;
    };
    
    class BattleTankGame {
        private:
            int enemyTankX;
            int enemyTankY;
            int playerTankX;
            int playerTankY;
            vector<Projectile> activeProjectiles;
            int playerScore;
            int playerFacingDirection;
            int enemyFacingDirection;
            int gameFrameCounter;
            
        public:
            BattleTankGame() {
                enemyTankX = 20;
                enemyTankY = 10;
                playerTankX = 10;
                playerTankY = 10;
                playerScore = 0;
                playerFacingDirection = 1;
                enemyFacingDirection = 0;
                gameFrameCounter = 0;
            }
            
            void MoveCursorToScreenPosition(int x, int y) {
                COORD cursorPosition = {x, y};
                HANDLE consoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
                SetConsoleCursorPosition(consoleOutput, cursorPosition);
            }
            
            void HideConsoleCursor() {
                HANDLE consoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
                CONSOLE_CURSOR_INFO cursorInfo;
                GetConsoleCursorInfo(consoleOutput, &cursorInfo);
                cursorInfo.bVisible = FALSE;
                SetConsoleCursorInfo(consoleOutput, &cursorInfo);
            }
            
            char GetPlayerTankCharacter(int direction) {
                switch(direction) {
                    case 0: return '^';
                    case 1: return 'v';
                    case 2: return '<';
                    case 3: return '>';
                    default: return 'P';
                }
            }
            
            char GetEnemyTankCharacter(int direction) {
                switch(direction) {
                    case 0: return '^';
                    case 1: return 'v';
                    case 2: return '<';
                    case 3: return '>';
                    default: return 'E';
                }
            }
            
            void PlayerFireProjectile() {
                Projectile newProjectile;
                newProjectile.positionX = playerTankX;
                newProjectile.positionY = playerTankY;
                newProjectile.travelDirection = playerFacingDirection;
                newProjectile.isActive = true;
                activeProjectiles.push_back(newProjectile);
            }
            
            void UpdateAllProjectiles() {
                for(unsigned int projectileIndex = 0; projectileIndex < activeProjectiles.size(); projectileIndex++) {
                    if(activeProjectiles[projectileIndex].isActive) {
                        MoveCursorToScreenPosition(activeProjectiles[projectileIndex].positionX, 
                                                   activeProjectiles[projectileIndex].positionY);
                        cout << " ";
                        
                        switch(activeProjectiles[projectileIndex].travelDirection) {
                            case 0: if(activeProjectiles[projectileIndex].positionY > 0) 
                                      activeProjectiles[projectileIndex].positionY--; break;
                            case 1: if(activeProjectiles[projectileIndex].positionY < 24) 
                                      activeProjectiles[projectileIndex].positionY++; break;
                            case 2: if(activeProjectiles[projectileIndex].positionX > 0) 
                                      activeProjectiles[projectileIndex].positionX--; break;
                            case 3: if(activeProjectiles[projectileIndex].positionX < 79) 
                                      activeProjectiles[projectileIndex].positionX++; break;
                        }
                        
                        if(activeProjectiles[projectileIndex].positionX == enemyTankX && 
                           activeProjectiles[projectileIndex].positionY == enemyTankY) {
                            playerScore += 10;
                            enemyTankX = rand() % 80;
                            enemyTankY = rand() % 25;
                            enemyFacingDirection = rand() % 4;
                            activeProjectiles[projectileIndex].isActive = false;
                            MoveCursorToScreenPosition(enemyTankX, enemyTankY);
                            cout << GetEnemyTankCharacter(enemyFacingDirection);
                        }
                        
                        if(activeProjectiles[projectileIndex].positionX <= 0 || 
                           activeProjectiles[projectileIndex].positionX >= 79 || 
                           activeProjectiles[projectileIndex].positionY <= 0 || 
                           activeProjectiles[projectileIndex].positionY >= 24) {
                            MoveCursorToScreenPosition(activeProjectiles[projectileIndex].positionX, 
                                                       activeProjectiles[projectileIndex].positionY);
                            cout << " ";
                            activeProjectiles[projectileIndex].isActive = false;
                        }
                        
                        if(activeProjectiles[projectileIndex].isActive) {
                            MoveCursorToScreenPosition(activeProjectiles[projectileIndex].positionX, 
                                                       activeProjectiles[projectileIndex].positionY);
                            cout << "*";
                        }
                    }
                }
                
                for(int projectileIndex = activeProjectiles.size() - 1; projectileIndex >= 0; projectileIndex--) {
                    if(!activeProjectiles[projectileIndex].isActive) {
                        activeProjectiles.erase(activeProjectiles.begin() + projectileIndex);
                    }
                }
            }
            
            void DisplayGameStatus() {
                MoveCursorToScreenPosition(0, 0);
                cout << "Score: " << playerScore << "  ";
            }
            
            int RunGameLoop() {
                HideConsoleCursor();
                srand(time(NULL));
                system("cls");
                
                cout << "Controls: WASD-move, Space-fire, ESC-exit" << endl;
                cout << "Player Tank: ^v<>  Enemy Tank: ^v<>" << endl;
                cout << "Press any key to start...";
                _getch();
                
                system("cls");
                
                MoveCursorToScreenPosition(playerTankX, playerTankY);
                cout << GetPlayerTankCharacter(playerFacingDirection);
                MoveCursorToScreenPosition(enemyTankX, enemyTankY);
                cout << GetEnemyTankCharacter(enemyFacingDirection);
                
                while(true) {
                    DisplayGameStatus();
                    
                    if(gameFrameCounter % 3 == 0) {
                        MoveCursorToScreenPosition(enemyTankX, enemyTankY);
                        cout << " ";
                        
                        int randomDirection = rand() % 4;
                        enemyFacingDirection = randomDirection;
                        
                        switch(randomDirection) {
                            case 0: if(enemyTankY > 0) enemyTankY--; break;
                            case 1: if(enemyTankY < 24) enemyTankY++; break;
                            case 2: if(enemyTankX > 0) enemyTankX--; break;
                            case 3: if(enemyTankX < 79) enemyTankX++; break;
                        }
                        
                        MoveCursorToScreenPosition(enemyTankX, enemyTankY);
                        cout << GetEnemyTankCharacter(enemyFacingDirection);
                    }
                    gameFrameCounter++;
                    
                    UpdateAllProjectiles();
                    
                    if(_kbhit()) {
                        char playerInput = _getch();
                        MoveCursorToScreenPosition(playerTankX, playerTankY);
                        cout << " ";
                        
                        switch(playerInput) {
                            case 'w': 
                                if(playerTankY > 0) playerTankY--; 
                                playerFacingDirection = 0;
                                break;
                            case 's': 
                                if(playerTankY < 24) playerTankY++; 
                                playerFacingDirection = 1;
                                break;
                            case 'a': 
                                if(playerTankX > 0) playerTankX--; 
                                playerFacingDirection = 2;
                                break;
                            case 'd': 
                                if(playerTankX < 79) playerTankX++; 
                                playerFacingDirection = 3;
                                break;
                            case ' ':
                                PlayerFireProjectile();
                                break;
                            case 27:
                                return 0;
                        }
                        
                        MoveCursorToScreenPosition(playerTankX, playerTankY);
                        cout << GetPlayerTankCharacter(playerFacingDirection);
                    }
                    Sleep(100);
                }
                return 0;
            }
    };
}

int main() {
    GameEngine::BattleTankGame gameInstance;
    gameInstance.RunGameLoop();
    return 0;
}
