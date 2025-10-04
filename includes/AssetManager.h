#pragma once

#include "../raylib/src/raylib.h"
#include <unordered_map>
#include <string>
#include <memory>
#include <vector>
#include <functional>
#include <cstdint>

class AssetManager {
public:
    AssetManager();
    ~AssetManager();
    
    // Texture management
    void LoadTexture(const std::string& name, const std::string& filePath);
    Texture2D GetTexture(const std::string& name);
    bool HasTexture(const std::string& name) const;
    
    // Sprite sheet management
    void LoadSpriteSheet(const std::string& name, const std::string& filePath, int frameWidth, int frameHeight);
    Rectangle GetSpriteRect(const std::string& sheetName, int frameIndex);
    Texture2D GetSpriteSheet(const std::string& name);
    
    // Sound management
    void LoadSound(const std::string& name, const std::string& filePath);
    Sound GetSound(const std::string& name);
    bool HasSound(const std::string& name) const;
    
    // Font management
    void LoadFont(const std::string& name, const std::string& filePath);
    Font GetFont(const std::string& name);
    bool HasFont(const std::string& name) const;
    
    // Level data management
    void LoadLevelData(const std::string& name, const std::string& filePath);
    const std::vector<uint8_t>& GetLevelData(const std::string& name);
    
    // Batch loading
    void LoadTextures();
    void LoadSounds();
    void LoadFonts();
    void LoadLevels();
    
    // Cleanup
    void UnloadAll();
    void UnloadTexture(const std::string& name);
    void UnloadSound(const std::string& name);
    void UnloadFont(const std::string& name);

private:
    std::unordered_map<std::string, Texture2D> textures;
    std::unordered_map<std::string, std::pair<int, int>> spriteSheetInfo;
    std::unordered_map<std::string, Sound> sounds;
    std::unordered_map<std::string, Font> fonts;
    std::unordered_map<std::string, std::vector<uint8_t>> levelData;
};