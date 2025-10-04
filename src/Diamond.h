#pragma once

#include "GameObject.h"

class Diamond : public GameObject {
public:
    Diamond(float x, float y);
    ~Diamond() = default;
    
    void Update(float deltaTime) override;
    void Draw() override;
    
    bool IsCollected() const { return collected; }
    void Collect() { collected = true; }
    Rectangle GetBounds() const override { return collider; }
    
private:
    bool collected;
    Rectangle collider;
    float animTime;
    int currentFrame;
};