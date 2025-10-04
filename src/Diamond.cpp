#include "Diamond.h"
#include "AssetManager.h"
#include <cmath> // For sinf

Diamond::Diamond(float x, float y) {
    position = {x, y};
    collected = false;
    collider = { x, y, 16, 16 };
    animTime = 0;
    currentFrame = 0;
    sparkleTime = 0;
}

void Diamond::Update() {
    if (!collected) {
        // Simple animation
        animTime += GetFrameTime();
        
        // Update animation frame (4 frames of animation)
        if (animTime > 0.1f) {
            currentFrame = (currentFrame + 1) % 4;
            animTime = 0;
        }
        
        // Sparkle effect timer
        sparkleTime += GetFrameTime();
        if (sparkleTime > 1.0f) {
            sparkleTime = 0;
        }
    }
}

void Diamond::Draw() {
    if (!collected) {
        // Draw diamond with animation
        Color tint = WHITE;
        
        // Pulsing effect
        float scale = 1.0f + 0.1f * sinf(GetTime() * 5.0f);
        
        // Draw diamond as a blue rhombus
        DrawRectanglePro(
            {position.x + 8, position.y + 8, 16 * scale, 16 * scale}, // Rectangle
            {8 * scale, 8 * scale}, // Origin (center)
            45.0f, // Rotation to make a diamond shape
            SKYBLUE
        );
        
        // Draw sparkle effect periodically
        if (sparkleTime > 0.7f) {
            DrawCircle(position.x + 8, position.y + 8, 3, WHITE);
        }
    }
}