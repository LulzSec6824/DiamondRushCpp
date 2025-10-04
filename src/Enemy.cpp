#include "Enemy.h"
#include "AssetManager.h"

Enemy::Enemy(float x, float y) 
    : GameObject(x, y),
      velocity({0, 0}),
      speed(2.0f),
      direction(1.0f),
      patrolDistance(100.0f),
      startX(x),
      animTime(0),
      currentFrame(0),
      frameCount(4) {
    
    // Initialize enemy collider
    collider = { position.x, position.y, 32, 32 };
}

void Enemy::Update(float deltaTime) {
    // Update patrol movement
    position.x += speed * direction * deltaTime;
    
    // Check if enemy has reached patrol limit
    if (position.x > startX + patrolDistance) {
        direction = -1.0f;
    } else if (position.x < startX - patrolDistance) {
        direction = 1.0f;
    }
    
    // Update collider position
    collider.x = position.x;
    collider.y = position.y;
    
    // Update animation
    animTime += deltaTime;
    if (animTime >= 0.2f) {
        animTime = 0;
        currentFrame = (currentFrame + 1) % frameCount;
    }
}

void Enemy::Draw() {
    // Try to draw with sprite if available
    if (AssetManager::GetInstance().HasTexture("enemy")) {
        // Get the sprite sheet
        Texture2D texture = AssetManager::GetInstance().GetTexture("enemy");
        
        // Calculate source rectangle based on animation frame
        Rectangle source = { currentFrame * 32.0f, 0, 32.0f, 32.0f };
        
        // Calculate destination rectangle
        Rectangle dest = { position.x, position.y, 32.0f, 32.0f };
        
        // Draw the sprite with correct direction
        DrawTexturePro(
            texture,
            source,
            dest,
            {0, 0},
            0.0f,
            direction > 0 ? WHITE : (Color){255, 255, 255, 255}
        );
    } else {
        // Fallback to colored rectangle
        DrawRectangleRec(collider, RED);
    }
    
    // Draw debug collision box
    #ifdef _DEBUG
    DrawRectangleLinesEx(collider, 1, BLUE);
    #endif
}