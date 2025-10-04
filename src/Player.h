#pragma once

#include "../raylib/src/raylib.h"
#include "GameObject.h"

class Player : public GameObject {
public:
    Player(float x, float y);
    ~Player() = default;
    
    void HandleInput();
    void Update(float deltaTime) override;
    void Draw() override;
    
    // Player states
    enum class State {
        IDLE,
        WALKING,
        JUMPING,
        FALLING,
        PUSHING
    };
    
    // Getters
    Rectangle GetBounds() const override { return collider; }
    Vector2 GetVelocity() const { return velocity; }
    State GetState() const { return state; }
    
    // Setters
    void SetGrounded(bool grounded) { isGrounded = grounded; }
    void SetPosition(float x, float y) { position.x = x; position.y = y; collider.x = x; collider.y = y; }
    
    // Actions
    void CollectDiamond();
    void TakeDamage();
    
    // Diamond collection tracking
    bool HasCollectedDiamond() const { return diamondCollected; }
    void Reset(float x, float y);
    
private:
    // Movement properties
    Vector2 velocity;
    float speed;
    float jumpForce;
    bool isGrounded;
    
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