#include "Player.h"
#include "AssetManager.h"
#include <iostream>

Player::Player(float x, float y) 
    : position({x, y}),
      velocity({0, 0}), 
      speed(2.0f), 
      state(State::IDLE),
      direction(Direction::DOWN),
      currentFrame(0),
      frameTime(0.1f),
      frameCounter(0),
      diamondCount(0),
      lives(3) {
    
    // Initialize player collider
    UpdateCollider();
}

void Player::UpdateCollider() {
    collider = { position.x, position.y, 16, 16 };
}

void Player::Reset(float x, float y) {
    position.x = x;
    position.y = y;
    velocity = {0, 0};
    state = State::IDLE;
    direction = Direction::DOWN;
    frameCounter = 0;
    currentFrame = 0;
    UpdateCollider();
}

void Player::HandleInput() {
    // Reset velocity
    velocity = {0, 0};
    
    // Only process input if not trapped or in special state
    if (state == State::TRAPPED) return;
    
    // Movement controls
    if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)) {
        velocity.x = -speed;
        direction = Direction::LEFT;
        state = State::WALKING;
    }
    else if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) {
        velocity.x = speed;
        direction = Direction::RIGHT;
        state = State::WALKING;
    }
    else if (IsKeyDown(KEY_UP) || IsKeyDown(KEY_W)) {
        velocity.y = -speed;
        direction = Direction::UP;
        state = State::WALKING;
    }
    else if (IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S)) {
        velocity.y = speed;
        direction = Direction::DOWN;
        state = State::WALKING;
    }
    else {
        state = State::IDLE;
    }
}

void Player::Update() {
    // Update position based on velocity
    position.x += velocity.x;
    position.y += velocity.y;
    
    // Update collider
    UpdateCollider();
    
    // Update animation
    if (state == State::WALKING) {
        frameCounter += GetFrameTime();
        if (frameCounter >= frameTime) {
            currentFrame = (currentFrame + 1) % 4; // 4 frames of animation
            frameCounter = 0;
        }
    }
    else {
        currentFrame = 0; // Reset to idle frame
    }
}

void Player::Draw() {
    // Draw player based on direction and state
    Color tint = WHITE;
    
    // Simple colored rectangle for now
    DrawRectangle(position.x, position.y, 16, 16, BLUE);
    
    // Draw direction indicator
    switch (direction) {
        case Direction::UP:
            DrawTriangle(
                {position.x + 8, position.y}, 
                {position.x, position.y + 8}, 
                {position.x + 16, position.y + 8}, 
                RED);
            break;
        case Direction::RIGHT:
            DrawTriangle(
                {position.x + 16, position.y + 8}, 
                {position.x + 8, position.y}, 
                {position.x + 8, position.y + 16}, 
                RED);
            break;
        case Direction::DOWN:
            DrawTriangle(
                {position.x + 8, position.y + 16}, 
                {position.x, position.y + 8}, 
                {position.x + 16, position.y + 8}, 
                RED);
            break;
        case Direction::LEFT:
            DrawTriangle(
                {position.x, position.y + 8}, 
                {position.x + 8, position.y}, 
                {position.x + 8, position.y + 16}, 
                RED);
            break;
    }
}

void Player::CollectDiamond() {
    diamondCount++;
}

void Player::TakeDamage() {
    lives--;
    if (lives <= 0) {
        Die();
    }
}

void Player::Die() {
    state = State::TRAPPED;
}

void Player::Respawn() {
    lives = 3;
    state = State::IDLE;
}
        velocity.x = speed;
        facingRight = true;
        state = State::WALKING;
    }
    else {
        state = State::IDLE;
    }
    
    // Jumping
    if ((IsKeyPressed(KEY_SPACE) || IsKeyPressed(KEY_W) || IsKeyPressed(KEY_UP)) && isGrounded) {
        velocity.y = -jumpForce;
        isGrounded = false;
        state = State::JUMPING;
        
        // Play jump sound
        if (AssetManager::GetInstance().HasSound("jump")) {
            PlaySound(AssetManager::GetInstance().GetSound("jump"));
        }
    }
}

void Player::Update(float deltaTime) {
    // Apply gravity
    if (!isGrounded) {
        velocity.y += 0.5f; // Gravity
        
        if (velocity.y > 0) {
            state = State::FALLING;
        }
    }
    
    // Update position based on velocity
    position.x += velocity.x;
    position.y += velocity.y;
    
    // Update collider position
    collider.x = position.x;
    collider.y = position.y;
    
    // Handle invincibility timer
    if (isInvincible) {
        invincibleTime -= deltaTime;
        if (invincibleTime <= 0) {
            isInvincible = false;
        }
    }
    
    // Update animation
    frameTime += deltaTime;
    if (frameTime >= 0.1f) {
        frameTime = 0;
        currentFrame = (currentFrame + 1) % frameCount;
    }
}

void Player::Render() {
    // Check if we have the player sprite sheet
    if (AssetManager::GetInstance().HasTexture("player_sheet")) {
        // Get the sprite sheet
        Texture2D playerSheet = AssetManager::GetInstance().GetTexture("player_sheet");
        
        // Determine which animation frame to use based on state
        int frameOffset = 0;
        switch (state) {
            case State::IDLE:
                frameOffset = 0;
                break;
            case State::WALKING:
                frameOffset = 4;
                break;
            case State::JUMPING:
                frameOffset = 8;
                break;
            case State::FALLING:
                frameOffset = 12;
                break;
            case State::PUSHING:
                frameOffset = 16;
                break;
        }
        
        // Calculate source rectangle for the current frame
        Rectangle source = {
            static_cast<float>((currentFrame + frameOffset) * 32), 
            0, 
            static_cast<float>(facingRight ? 32 : -32), 
            32
        };
        
        // Calculate destination rectangle
        Rectangle dest = {
            position.x, 
            position.y, 
            32, 
            48
        };
        
        // Draw the player sprite
        // Flash if invincible
        if (!isInvincible || static_cast<int>(invincibleTime * 10) % 2 == 0) {
            DrawTexturePro(playerSheet, source, dest, {0, 0}, 0, WHITE);
        }
    } else {
        // Fallback to colored rectangle if sprite sheet not available
        Color playerColor = BLUE;
        
        switch (state) {
            case State::IDLE:
                playerColor = BLUE;
                break;
            case State::WALKING:
                playerColor = GREEN;
                break;
            case State::JUMPING:
            case State::FALLING:
                playerColor = YELLOW;
                break;
            case State::PUSHING:
                playerColor = PURPLE;
                break;
        }
        
        // Draw the player rectangle with the appropriate color
        // Flash if invincible
        if (!isInvincible || static_cast<int>(invincibleTime * 10) % 2 == 0) {
            DrawRectangleRec(collider, playerColor);
        }
    }
    
    // Draw debug collision box
    #ifdef _DEBUG
    DrawRectangleLinesEx(collider, 1, RED);
    #endif
}

Rectangle Player::GetBounds() const {
    return collider;
}

void Player::OnCollideWithWall() {
    // Handle wall collision
    if (velocity.x > 0) {
        // Colliding from the left
        position.x = collider.x - 1;
    } else if (velocity.x < 0) {
        // Colliding from the right
        position.x = collider.x + 1;
    }
    
    velocity.x = 0;
}

void Player::OnCollideWithGround() {
    // Handle ground collision
    if (velocity.y > 0) {
        // Colliding from above
        isGrounded = true;
        velocity.y = 0;
        
        if (velocity.x == 0) {
            state = State::IDLE;
        } else {
            state = State::WALKING;
        }
    }
}

void Player::OnCollideWithCeiling() {
    // Handle ceiling collision
    if (velocity.y < 0) {
        // Colliding from below
        velocity.y = 0;
    }
}

void Player::OnCollideWithDiamond() {
    diamondCollected = true;
}

void Player::OnCollideWithEnemy() {
    if (!isInvincible) {
        health--;
        isInvincible = true;
        invincibleTime = 2.0f; // 2 seconds of invincibility
        
        // Play damage sound
        if (AssetManager::GetInstance().HasSound("damage")) {
            PlaySound(AssetManager::GetInstance().GetSound("damage"));
        }
    }
}

void Player::OnCollideWithExit() {
    // Handle exit collision - will be handled by the game class
}
            break;
        case State::PUSHING:
            playerColor = ORANGE;
            break;
    }
    
    DrawRectangleRec(collider, playerColor);
    
    // Draw direction indicator
    if (facingRight) {
        DrawTriangle(
            {position.x + collider.width + 5, position.y + collider.height / 2},
            {position.x + collider.width + 15, position.y + collider.height / 2 - 10},
            {position.x + collider.width + 15, position.y + collider.height / 2 + 10},
            RED
        );
    } else {
        DrawTriangle(
            {position.x - 5, position.y + collider.height / 2},
            {position.x - 15, position.y + collider.height / 2 - 10},
            {position.x - 15, position.y + collider.height / 2 + 10},
            RED
        );
    }
}

void Player::CollectDiamond() {
    // Set the flag that a diamond was collected
    diamondCollected = true;
    
    // Visual feedback for diamond collection
    // In a full implementation, we would play a sound here
    
    // The score increase will be handled by the Game class
}

void Player::TakeDamage() {
    // Visual feedback for taking damage
    // In a full implementation, we would play a sound here
    
    // Apply knockback
    velocity.y = -5.0f;
    
    // Temporary invincibility will be handled by Game class
}