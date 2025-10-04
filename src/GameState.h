#pragma once

#include "../raylib/src/raylib.h"
#include <memory>

// Forward declarations
class Game;

// Base GameState class
class GameState {
public:
    GameState(Game* game) : game(game) {}
    virtual ~GameState() = default;
    
    virtual void Enter() = 0;
    virtual void Exit() = 0;
    virtual void ProcessInput() = 0;
    virtual void Update(float deltaTime) = 0;
    virtual void Render() = 0;
    
protected:
    Game* game;
};

// Menu State
class MenuState : public GameState {
public:
    MenuState(Game* game);
    void Enter() override;
    void Exit() override;
    void ProcessInput() override;
    void Update(float deltaTime) override;
    void Render() override;
    
private:
    int selectedOption;
    Rectangle playButton;
    Rectangle exitButton;
};

// Gameplay State
class GameplayState : public GameState {
public:
    GameplayState(Game* game);
    void Enter() override;
    void Exit() override;
    void ProcessInput() override;
    void Update(float deltaTime) override;
    void Render() override;
    
    void LoadLevel(int levelNumber);
    void RestartLevel();
    
private:
    int currentLevel;
    bool levelCompleted;
    float levelCompletedTimer;
};

// Game Over State
class GameOverState : public GameState {
public:
    GameOverState(Game* game);
    void Enter() override;
    void Exit() override;
    void ProcessInput() override;
    void Update(float deltaTime) override;
    void Render() override;
    
private:
    Rectangle retryButton;
    Rectangle menuButton;
};

// State Manager
class GameStateManager {
public:
    GameStateManager(Game* game);
    
    void ChangeState(std::unique_ptr<GameState> newState);
    void ProcessInput();
    void Update(float deltaTime);
    void Render();
    
private:
    Game* game;
    std::unique_ptr<GameState> currentState;
};