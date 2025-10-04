#include "Diamond.h"
#include <cmath> // For sinf

Diamond::Diamond(float x, float y) 
    : GameObject(x, y), collected(false), animTime(0) {
    
    // Set up collider
    collider = { x, y, 24, 24 };
}

void Diamond::Update(float deltaTime) {
    if (!collected) {
        // Simple animation
        animTime += deltaTime;
        
        // Update animation frame
        currentFrame = static_cast<int>((animTime * 8.0f)) % 4;
    }
}

void Diamond::Draw() {
    if (!collected) {
        // Pulsing animation effect
        float scale = 1.0f + 0.2f * sinf(animTime * 5.0f);
        
        // Draw diamond as a rotated rectangle to simulate a rhombus
        DrawRectanglePro(
            {position.x + 12, position.y + 12, 24 * scale, 24 * scale}, // Rectangle
            {12 * scale, 12 * scale}, // Origin (center of the rectangle)
            45.0f, // Rotation in degrees
            SKYBLUE
        );
        
        // Draw outline as a rotated rectangle
        DrawRectangleLinesEx(
            {position.x + 12 - (12 * scale), position.y + 12 - (12 * scale), 24 * scale, 24 * scale}, // Rectangle
            1, // Line thickness
            DARKBLUE
        );
    }
}