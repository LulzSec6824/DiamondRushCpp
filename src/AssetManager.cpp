#include "AssetManager.h"
#include <iostream>
#include <fstream>

AssetManager& AssetManager::GetInstance() {
    static AssetManager instance;
    return instance;
}

void AssetManager::LoadTexture(const std::string& name, const std::string& filePath) {
    textures[name] = ::LoadTexture(filePath.c_str());
}

Texture2D AssetManager::GetTexture(const std::string& name) {
    if (!HasTexture(name)) {
        std::cerr << "Texture not found: " << name << std::endl;
        return { 0 }; // Return empty texture
    }
    return textures[name];
}

bool AssetManager::HasTexture(const std::string& name) const {
    return textures.find(name) != textures.end();
}

void AssetManager::LoadSpriteSheet(const std::string& name, const std::string& filePath, int frameWidth, int frameHeight) {
    SpriteSheetInfo info;
    info.texture = ::LoadTexture(filePath.c_str());
    info.frameWidth = frameWidth;
    info.frameHeight = frameHeight;
    info.columns = info.texture.width / frameWidth;
    info.rows = info.texture.height / frameHeight;
    
    spriteSheets[name] = info;
}

Rectangle AssetManager::GetSpriteRect(const std::string& sheetName, int frameIndex) {
    if (spriteSheets.find(sheetName) == spriteSheets.end()) {
        std::cerr << "Sprite sheet not found: " << sheetName << std::endl;
        return { 0, 0, 0, 0 };
    }
    
    const auto& sheet = spriteSheets[sheetName];
    int column = frameIndex % sheet.columns;
    int row = frameIndex / sheet.columns;
    
    return { 
        static_cast<float>(column * sheet.frameWidth), 
        static_cast<float>(row * sheet.frameHeight),
        static_cast<float>(sheet.frameWidth), 
        static_cast<float>(sheet.frameHeight) 
    };
}

Texture2D AssetManager::GetSpriteSheet(const std::string& name) {
    if (spriteSheets.find(name) == spriteSheets.end()) {
        std::cerr << "Sprite sheet not found: " << name << std::endl;
        return { 0 }; // Return empty texture
    }
    return spriteSheets[name].texture;
}

void AssetManager::LoadSound(const std::string& name, const std::string& filePath) {
    sounds[name] = ::LoadSound(filePath.c_str());
}

Sound AssetManager::GetSound(const std::string& name) {
    if (!HasSound(name)) {
        std::cerr << "Sound not found: " << name << std::endl;
        return { 0 }; // Return empty sound
    }
    return sounds[name];
}

bool AssetManager::HasSound(const std::string& name) const {
    return sounds.find(name) != sounds.end();
}

void AssetManager::LoadFont(const std::string& name, const std::string& filePath) {
    fonts[name] = ::LoadFont(filePath.c_str());
}

Font AssetManager::GetFont(const std::string& name) {
    if (!HasFont(name)) {
        std::cerr << "Font not found: " << name << std::endl;
        return GetFontDefault(); // Return default font
    }
    return fonts[name];
}

bool AssetManager::HasFont(const std::string& name) const {
    return fonts.find(name) != fonts.end();
}

void AssetManager::LoadLevelData(const std::string& name, const std::string& filePath) {
    std::ifstream file(filePath, std::ios::binary);
    if (!file) {
        std::cerr << "Failed to open level file: " << filePath << std::endl;
        return;
    }
    
    // Get file size
    file.seekg(0, std::ios::end);
    size_t fileSize = file.tellg();
    file.seekg(0, std::ios::beg);
    
    // Read file content
    std::vector<uint8_t> data(fileSize);
    file.read(reinterpret_cast<char*>(data.data()), fileSize);
    
    levelData[name] = std::move(data);
}

const std::vector<uint8_t>& AssetManager::GetLevelData(const std::string& name) {
    static std::vector<uint8_t> emptyData;
    if (levelData.find(name) == levelData.end()) {
        std::cerr << "Level data not found: " << name << std::endl;
        return emptyData;
    }
    return levelData[name];
}

void AssetManager::LoadGameAssets() {
    // Load textures
    LoadTexture("player", "resources/textures/player.png");
    LoadTexture("tiles", "resources/textures/tiles.png");
    LoadTexture("ui", "resources/textures/ui.png");
    
    // Load sprite sheets
    LoadSpriteSheet("player_sheet", "resources/textures/player_sheet.png", 32, 32);
    LoadSpriteSheet("diamond_sheet", "resources/textures/diamond_sheet.png", 16, 16);
    
    // Load sounds
    LoadSound("diamond_collect", "resources/sounds/diamond_collect.wav");
    LoadSound("level_complete", "resources/sounds/level_complete.wav");
    
    // Load fonts
    LoadFont("main_font", "resources/fonts/main_font.ttf");
    
    // Load level data
    for (int i = 1; i <= 3; i++) {
        LoadLevelData("level" + std::to_string(i), "resources/levels/level" + std::to_string(i) + ".dat");
    }
}

void AssetManager::UnloadTexture(const std::string& name) {
    if (HasTexture(name)) {
        ::UnloadTexture(textures[name]);
        textures.erase(name);
    }
}

void AssetManager::UnloadSound(const std::string& name) {
    if (HasSound(name)) {
        ::UnloadSound(sounds[name]);
        sounds.erase(name);
    }
}

void AssetManager::UnloadFont(const std::string& name) {
    if (HasFont(name)) {
        ::UnloadFont(fonts[name]);
        fonts.erase(name);
    }
}

void AssetManager::UnloadAll() {
    // Unload all textures
    for (auto& texture : textures) {
        ::UnloadTexture(texture.second);
    }
    textures.clear();
    
    // Unload all sprite sheets
    for (auto& sheet : spriteSheets) {
        ::UnloadTexture(sheet.second.texture);
    }
    spriteSheets.clear();
    
    // Unload all sounds
    for (auto& sound : sounds) {
        ::UnloadSound(sound.second);
    }
    sounds.clear();
    
    // Unload all fonts
    for (auto& font : fonts) {
        ::UnloadFont(font.second);
    }
    fonts.clear();
    
    // Clear level data
    levelData.clear();
}



AssetManager::~AssetManager() {
    UnloadAll();
}