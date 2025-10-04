#include "Player.h"
#include "Game.h"
#include "GameState.h"
#include "AssetManager.h"
#include <iostream>
#include <memory>
#include "raylib.h"

// MenuState Implementation
MenuState::MenuState(Game* game) : GameState(game), selectedOption(0) {
    // Initialize button positions
    playButton = { 300, 200, 200, 50 };
    exitButton = { 300, 300, 200, 50 };
}

void MenuState::Enter() {
    std::cout << "Entering Menu State" << std::endl;
}

void MenuState::Exit() {
    std::cout << "Exiting Menu State" << std::endl;
}

void MenuState::ProcessInput() {
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        Vector2 mousePos = GetMousePosition();
        
        if (CheckCollisionPointRec(mousePos, playButton)) {
            game->GetStateManager().ChangeState(std::make_unique<GameplayState>(game));
        }
        else if (CheckCollisionPointRec(mousePos, exitButton)) {
            game->Quit();
        }
    }
    
    // Keyboard navigation
    if (IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_UP)) {
        selectedOption = (selectedOption == 0) ? 1 : 0;
    }
    
    if (IsKeyPressed(KEY_ENTER)) {
        if (selectedOption == 0) {
            game->GetStateManager().ChangeState(std::make_unique<GameplayState>(game));
        }
        else {
            game->Quit();
        }
    }
}

void MenuState::Update(float deltaTime) {
    // Animation updates if needed
}

void MenuState::Render() {
    ClearBackground(RAYWHITE);
    
    // Draw title
    DrawText("DIAMOND RUSH", 250, 100, 40, DARKBLUE);
    
    // Draw buttons
    DrawRectangleRec(playButton, (selectedOption == 0) ? SKYBLUE : LIGHTGRAY);
    DrawRectangleRec(exitButton, (selectedOption == 1) ? SKYBLUE : LIGHTGRAY);
    
    DrawText("PLAY", playButton.x + 70, playButton.y + 15, 20, BLACK);
    DrawText("EXIT", exitButton.x + 70, exitButton.y + 15, 20, BLACK);
    
    // Draw footer
    DrawText("C++ Raylib Version", 300, 400, 20, GRAY);
}

// GameplayState Implementation
GameplayState::GameplayState(Game* game) 
    : GameState(game), currentLevel(1), levelCompleted(false), levelCompletedTimer(0) {
}

void GameplayState::Enter() {
    std::cout << "Entering Gameplay State" << std::endl;
    LoadLevel(currentLevel);
}

void GameplayState::Exit() {
    std::cout << "Exiting Gameplay State" << std::endl;
}

void GameplayState::ProcessInput() {
    if (levelCompleted) {
        if (IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_SPACE)) {
            if (currentLevel < 3) { // Assuming 3 levels total
                currentLevel++;
                LoadLevel(currentLevel);
            }
            else {
                // Game completed, return to menu
                game->GetStateManager().ChangeState(std::make_unique<MenuState>(game));
            }
        }
        return;
    }
    
    // Handle player input
    game->GetPlayer().ProcessInput();
    
    // Debug keys
    if (IsKeyPressed(KEY_R)) {
        RestartLevel();
    }
    
    if (IsKeyPressed(KEY_ESCAPE)) {
        game->GetStateManager().ChangeState(std::make_unique<MenuState>(game));
    }
}

void GameplayState::Update(float deltaTime) {
    if (levelCompleted) {
        levelCompletedTimer += deltaTime;
        if (levelCompletedTimer > 3.0f) { // Wait 3 seconds before auto-advancing
            if (currentLevel < 3) {
                currentLevel++;
                LoadLevel(currentLevel);
            }
            else {
                // Game completed, return to menu
                game->GetStateManager().ChangeState(std::make_unique<MenuState>(game));
            }
        }
        return;
    }
    
    // Update game objects
    game->GetPlayer().Update(deltaTime);
    
    // Check for level completion
    if (game->GetCurrentLevel().IsCompleted()) {
        levelCompleted = true;
        levelCompletedTimer = 0;
        // Play completion sound
        PlaySound(AssetManager::GetInstance().GetSound("level_complete"));
    }
    
    // Check for player death
    if (game->GetPlayer().IsDead()) {
        game->GetStateManager().ChangeState(std::make_unique<GameOverState>(game));
    }
}

void GameplayState::Render() {
    ClearBackground(BLACK);
    
    // Render level
    game->GetCurrentLevel().Render();
    
    // Render player
    game->GetPlayer().Render();
    
    // Render UI
    DrawRectangle(0, 0, GetScreenWidth(), 40, ColorAlpha(BLACK, 0.7f));
    DrawText(TextFormat("LEVEL: %d", currentLevel), 20, 10, 20, WHITE);
    DrawText(TextFormat("SCORE: %d", game->GetScore()), 200, 10, 20, WHITE);
    DrawText(TextFormat("DIAMONDS: %d/%d", game->GetCollectedDiamonds(), game->GetTotalDiamonds()), 400, 10, 20, WHITE);
    DrawText(TextFormat("LIVES: %d", game->GetLives()), 700, 10, 20, WHITE);
    
    // Render level completed message
    if (levelCompleted) {
        DrawRectangle(200, 200, 400, 100, ColorAlpha(BLACK, 0.8f));
        DrawText("LEVEL COMPLETED!", 250, 220, 30, GOLD);
        DrawText("Press ENTER to continue", 270, 260, 20, WHITE);
    }
}

void GameplayState::LoadLevel(int levelNumber) {
    levelCompleted = false;
    game->LoadLevel(levelNumber);
}

void GameplayState::RestartLevel() {
    LoadLevel(currentLevel);
}

// GameOverState Implementation
GameOverState::GameOverState(Game* game) : GameState(game) {
    retryButton = { 300, 250, 200, 50 };
    menuButton = { 300, 320, 200, 50 };
}

void GameOverState::Enter() {
    std::cout << "Entering Game Over State" << std::endl;
}

void GameOverState::Exit() {
    std::cout << "Exiting Game Over State" << std::endl;
}

void GameOverState::ProcessInput() {
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        Vector2 mousePos = GetMousePosition();
        
        if (CheckCollisionPointRec(mousePos, retryButton)) {
            game->GetStateManager().ChangeState(std::make_unique<GameplayState>(game));
        }
        else if (CheckCollisionPointRec(mousePos, menuButton)) {
            game->GetStateManager().ChangeState(std::make_unique<MenuState>(game));
        }
    }
    
    if (IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_SPACE)) {
        game->GetStateManager().ChangeState(std::make_unique<GameplayState>(game));
    }
    
    if (IsKeyPressed(KEY_ESCAPE)) {
        game->GetStateManager().ChangeState(std::make_unique<MenuState>(game));
    }
}

void GameOverState::Update(float deltaTime) {
    // Animation updates if needed
}

void GameOverState::Render() {
    ClearBackground(BLACK);
    
    DrawText("GAME OVER", 300, 150, 40, RED);
    DrawText(TextFormat("FINAL SCORE: %d", game->GetScore()), 320, 200, 20, WHITE);
    
    DrawRectangleRec(retryButton, MAROON);
    DrawRectangleRec(menuButton, DARKBLUE);
    
    DrawText("RETRY", retryButton.x + 70, retryButton.y + 15, 20, WHITE);
    DrawText("MENU", menuButton.x + 70, menuButton.y + 15, 20, WHITE);
}

// GameStateManager Implementation
GameStateManager::GameStateManager(Game* game) : game(game), currentState(nullptr) {
}

void GameStateManager::ChangeState(std::unique_ptr<GameState> newState) {
    if (currentState) {
        currentState->Exit();
    }
    
    currentState = std::move(newState);
    
    if (currentState) {
        currentState->Enter();
    }
}

void GameStateManager::ProcessInput() {
    if (currentState) {
        currentState->ProcessInput();
    }
}

void GameStateManager::Update(float deltaTime) {
    if (currentState) {
        currentState->Update(deltaTime);
    }
}

void GameStateManager::Render() {
    if (currentState) {
        currentState->Render();
    }
}