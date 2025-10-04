#pragma once

#include "GameObject.h"

class Enemy : public GameObject {
public:
    Enemy(float x, float y);
    ~Enemy() = default;
    
    void Update(float deltaTime) override;
    void Draw() override;
    
    Rectangle GetBounds() const override { return collider; }
    
private:
    Rectangle collider;
    Vector2 velocity;
    float speed;
    float direction;
    float patrolDistance;
    float startX;
    
    // Animation
    float animTime;
    int currentFrame;
    int frameCount;
};