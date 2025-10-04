#pragma once

#include "../raylib/src/raylib.h"
#include <memory>
#include <string>

// Forward declarations
class Player;
class Level;
class AssetManager;
class GameState;

class Game {
public:
    Game();
    ~Game();
    
    void Run();
    void Quit();
    void Pause();
    void Resume();
    
    // Getters
    Player& GetPlayer() const { return *player; }
    Level& GetCurrentLevel() const { return *currentLevel; }
    
    int GetScore() const { return score; }
    int GetLives() const { return lives; }
    int GetCollectedDiamonds() const { return collectedDiamonds; }
    int GetTotalDiamonds() const { return totalDiamonds; }
    
    // Game actions
    void LoadLevel(int levelNumber);
    void AddScore(int points);
    void CollectDiamond();
    void LoseLife();
    
    // Constants for key mappings
    static const int KEY_ANY_OK = 0;
    static const int KEY_OK = 1;
    static const int KEY_CANCEL = 2;
    static const int KEY_RESPAWN = 3;
    static const int KEY_UP = 4;
    static const int KEY_DOWN = 5;
    static const int KEY_LEFT = 6;
    static const int KEY_RIGHT = 7;

    // Constants for seal positions
    static const int SEAL_POS_ANGKOR = 0;
    static const int SEAL_POS_BAVARIA = 1;
    static const int SEAL_POS_SIBERIA = 2;
    static const int SEAL_POS_SHOP = 3;

    // Constants for seal movement
    static const int SEAL_MOVE_NOOP = -1;
    static const int SEAL_MOVE_UP = 0;
    static const int SEAL_MOVE_RIGHT = 1;
    static const int SEAL_MOVE_DOWN = 2;
    static const int SEAL_MOVE_LEFT = 3;
    static const int SEAL_MOVE_OK = 4;

    // Constants for stages
    static const int STAGE_ANGKOR_FALLING_TORCHES = 5;
    static const int STAGE_ANGKOR_GREAT_ANACONDA = 8;
    static const int STAGE_ANGKOR_DEMO = 13;
    static const int STAGE_BAVARIA_EVIL_TEUTONIC_KNIGHT = 9;
    static const int STAGE_SIBERIA_YETTI = 10;
    
private:
    void Initialize();
    void ProcessInput();
    void Update();
    void Render();
    void Shutdown();
    void LoadResources();
    
    // Game state
    bool isRunning;
    bool isPaused;
    std::unique_ptr<GameState> currentState;
    std::unique_ptr<AssetManager> assetManager;
    
    // Window settings
    const int screenWidth = 240;
    const int screenHeight = 320;
    const char* title = "Diamond Rush";
    
    // Game objects
    std::unique_ptr<Player> player;
    std::unique_ptr<Level> currentLevel;
    
    // Game variables
    int score;
    int collectedDiamonds;
    int totalDiamonds;
    int lives;
    int currentLevelNumber;
    int currentSealPosition;
    int currentSealMoveDirection;
    int sealArrowOffsetX;
    int sealArrowOffsetY;
};