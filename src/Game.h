#pragma once

#include "../raylib/src/raylib.h"
#include <memory>

// Forward declarations
class Player;
class Level;
class GameStateManager;

class Game {
public:
    Game();
    ~Game();
    
    void Run();
    void Quit();
    
    // Getters
    Player& GetPlayer() const { return *player; }
    Level& GetCurrentLevel() const { return *currentLevel; }
    GameStateManager& GetStateManager() { return *stateManager; }
    
    int GetScore() const { return score; }
    int GetLives() const { return lives; }
    int GetCollectedDiamonds() const { return collectedDiamonds; }
    int GetTotalDiamonds() const { return totalDiamonds; }
    
    // Game actions
    void LoadLevel(int levelNumber);
    void AddScore(int points);
    void CollectDiamond();
    void LoseLife();
    
private:
    void Initialize();
    void ProcessInput();
    void Update();
    void Render();
    void Shutdown();
    
    // Game state
    bool isRunning;
    std::unique_ptr<GameStateManager> stateManager;
    
    // Window settings
    const int screenWidth = 800;
    const int screenHeight = 600;
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
};