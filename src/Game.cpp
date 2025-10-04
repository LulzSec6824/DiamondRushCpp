#include "Game.h"
#include "Player.h"
#include "Level.h"
#include "GameState.h"
#include "AssetManager.h"
#include "iostream"
#include <memory>
#include <cmath>

Game::Game() : isRunning(false), score(0), collectedDiamonds(0), totalDiamonds(0), lives(3), currentLevelNumber(1) {
}

Game::~Game() {
    Shutdown();
}

void Game::Initialize() {
    // Initialize raylib window
    InitWindow(screenWidth, screenHeight, title);
    SetTargetFPS(60);
    
    // Initialize audio
    InitAudioDevice();
    
    // Load game assets
    AssetManager::GetInstance().LoadGameAssets();
    
    // Initialize game objects
    player = std::make_unique<Player>(screenWidth / 2, screenHeight / 2);
    
    // Initialize state manager and set initial state to menu
    stateManager = std::make_unique<GameStateManager>(this);
    stateManager->ChangeState(std::make_unique<MenuState>(this));
    
    isRunning = true;
}

void Game::Run() {
    Initialize();
    
    // Main game loop
    while (!WindowShouldClose() && isRunning) {
        float deltaTime = GetFrameTime();
        
        ProcessInput();
        Update();
        Render();
    }
    
    Shutdown();
}

void Game::Quit() {
    isRunning = false;
}

void Game::ProcessInput() {
    stateManager->ProcessInput();
}





void Game::Shutdown() {
    // Unload all assets
    AssetManager::GetInstance().UnloadAll();
    
    // Close audio device
    CloseAudioDevice();
    
    // Close window
    CloseWindow();
}

void Game::LoadLevel(int levelNumber) {
    currentLevelNumber = levelNumber;
    currentLevel = std::make_unique<Level>(levelNumber);
    totalDiamonds = currentLevel->GetDiamondCount();
    collectedDiamonds = 0;
    
    // Reset player position
    player->Reset(currentLevel->GetPlayerStartPosition().x, currentLevel->GetPlayerStartPosition().y);
}

void Game::AddScore(int points) {
    score += points;
}

void Game::CollectDiamond() {
    collectedDiamonds++;
    AddScore(100); // Each diamond is worth 100 points
    
    // Play sound effect
    PlaySound(AssetManager::GetInstance().GetSound("diamond_collect"));
}

void Game::LoseLife() {
    lives--;
    
    if (lives <= 0) {
        // Game over will be handled by the state system
    }
}

void Game::Update() {
    float deltaTime = GetFrameTime();
    
    if (stateManager) {
        stateManager->Update(deltaTime);
    }
    
    // Update game objects
    if (currentLevel) {
        currentLevel->Update(deltaTime);
        
        if (player) {
            player->Update(deltaTime);
            currentLevel->CheckCollisions(*player);
            
            // Check if player collected a diamond
            if (player->HasCollectedDiamond()) {
                CollectDiamond();
                player->ResetDiamondCollected();
            }
        }
    }
}

void Game::Render() {
    BeginDrawing();
    ClearBackground(RAYWHITE);
    
    // Draw level
    if (currentLevel) {
        currentLevel->Draw();
    }
    
    // Draw player
    if (player) {
        player->Draw();
    }
    
    // Draw UI
    DrawText(TextFormat("SCORE: %d", score), 20, 20, 20, BLACK);
    DrawText(TextFormat("DIAMONDS: %d/%d", collectedDiamonds, totalDiamonds), 20, 50, 20, BLACK);
    DrawText(TextFormat("LIVES: %d", lives), 20, 80, 20, BLACK);
    
    EndDrawing();
}