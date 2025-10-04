#pragma once

#include "raylib.h"
#include "GameObject.h"

class Player {
public:
    Player(float x, float y);
    ~Player() = default;
    
    void HandleInput();
    void Update();
    void Draw();
    
    // Player states
    enum class State {
        IDLE,
        WALKING,
        PUSHING,
        CLIMBING,
        FALLING,
        DIGGING,
        TRAPPED
    };
    
    // Directions
    enum class Direction {
        UP,
        RIGHT,
        DOWN,
        LEFT
    };
    
    // Getters
    Rectangle GetBounds() const { return collider; }
    Vector2 GetPosition() const { return position; }
    Vector2 GetVelocity() const { return velocity; }
    State GetState() const { return state; }
    Direction GetDirection() const { return direction; }
    
    // Setters
    void SetPosition(float x, float y) { position.x = x; position.y = y; UpdateCollider(); }
    
    // Actions
    void CollectDiamond();
    void TakeDamage();
    void Die();
    void Respawn();
    
    // Diamond collection tracking
    int GetDiamondCount() const { return diamondCount; }
    void Reset(float x, float y);
    
private:
    // Position and movement
    Vector2 position;
    Vector2 velocity;
    float speed;
    State state;
    Direction direction;
    
    // Animation
    int currentFrame;
    float frameTime;
    float frameCounter;
    
    // Collision
    Rectangle collider;
    void UpdateCollider();
    
    // Game stats
    int diamondCount;
    int lives;
    
    // Collision
    Rectangle collider;
    
    // State
    State state;
    bool facingRight;
    
    // Animation
    float frameTime;
    int currentFrame;
    int frameCount;
    
    // Game state
    bool diamondCollected;
};