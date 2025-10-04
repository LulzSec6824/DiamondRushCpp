#include "AssetManager.h"
#include <iostream>

AssetManager::~AssetManager() {
    UnloadAll();
}

// Texture management
void AssetManager::LoadTexture(const std::string& name, const std::string& filePath) {
    if (textures.find(name) != textures.end()) {
        ::UnloadTexture(textures[name]);
    }
    textures[name] = ::LoadTexture(filePath.c_str());
}

Texture2D AssetManager::GetTexture(const std::string& name) {
    if (textures.find(name) != textures.end()) {
        return textures[name];
    }
    std::cerr << "Texture not found: " << name << std::endl;
    return { 0 };
}

bool AssetManager::HasTexture(const std::string& name) const {
    return textures.find(name) != textures.end();
}

// Sprite sheet management
void AssetManager::LoadSpriteSheet(const std::string& name, const std::string& filePath, int frameWidth, int frameHeight) {
    LoadTexture(name, filePath);
    spriteSheetInfo[name] = { frameWidth, frameHeight };
}

Rectangle AssetManager::GetSpriteRect(const std::string& sheetName, int frameIndex) {
    if (spriteSheetInfo.find(sheetName) == spriteSheetInfo.end()) {
        std::cerr << "Sprite sheet not found: " << sheetName << std::endl;
        return { 0, 0, 0, 0 };
    }
    
    auto& info = spriteSheetInfo[sheetName];
    Texture2D texture = textures[sheetName];
    
    int framesPerRow = texture.width / info.first;
    int row = frameIndex / framesPerRow;
    int col = frameIndex % framesPerRow;
    
    return { 
        static_cast<float>(col * info.first), 
        static_cast<float>(row * info.second), 
        static_cast<float>(info.first), 
        static_cast<float>(info.second) 
    };
}

Texture2D AssetManager::GetSpriteSheet(const std::string& name) {
    return GetTexture(name);
}

// Sound management
void AssetManager::LoadSound(const std::string& name, const std::string& filePath) {
    if (sounds.find(name) != sounds.end()) {
        ::UnloadSound(sounds[name]);
    }
    sounds[name] = ::LoadSound(filePath.c_str());
}

Sound AssetManager::GetSound(const std::string& name) {
    if (sounds.find(name) != sounds.end()) {
        return sounds[name];
    }
    std::cerr << "Sound not found: " << name << std::endl;
    return { 0 };
}

bool AssetManager::HasSound(const std::string& name) const {
    return sounds.find(name) != sounds.end();
}

// Font management
void AssetManager::LoadFont(const std::string& name, const std::string& filePath) {
    if (fonts.find(name) != fonts.end()) {
        ::UnloadFont(fonts[name]);
    }
    fonts[name] = ::LoadFont(filePath.c_str());
}

Font AssetManager::GetFont(const std::string& name) {
    if (fonts.find(name) != fonts.end()) {
        return fonts[name];
    }
    std::cerr << "Font not found: " << name << std::endl;
    return GetFontDefault();
}

bool AssetManager::HasFont(const std::string& name) const {
    return fonts.find(name) != fonts.end();
}

// Level data management
void AssetManager::LoadLevelData(const std::string& name, const std::string& filePath) {
    // Load binary level data
    unsigned int size = 0;
    unsigned char* data = LoadFileData(filePath.c_str(), &size);
    
    if (data && size > 0) {
        levelData[name] = std::vector<uint8_t>(data, data + size);
        UnloadFileData(data);
    } else {
        std::cerr << "Failed to load level data: " << filePath << std::endl;
    }
}

const std::vector<uint8_t>& AssetManager::GetLevelData(const std::string& name) {
    static std::vector<uint8_t> emptyData;
    if (levelData.find(name) != levelData.end()) {
        return levelData[name];
    }
    std::cerr << "Level data not found: " << name << std::endl;
    return emptyData;
}

// Batch loading
void AssetManager::LoadTextures() {
    // Load textures for Diamond Rush
    LoadTexture("player", "resources/textures/player_sheet.svg");
    LoadSpriteSheet("player_sheet", "resources/textures/player_sheet.svg", 32, 32);
    
    LoadTexture("tiles", "resources/textures/tiles.svg");
    LoadSpriteSheet("tiles_sheet", "resources/textures/tiles.svg", 16, 16);
    
    LoadTexture("diamond", "resources/textures/diamond_sheet.svg");
    LoadSpriteSheet("diamond_sheet", "resources/textures/diamond_sheet.svg", 16, 16);
    
    // Additional textures for UI, menus, etc.
    // These would be created based on the original game assets
}

void AssetManager::LoadSounds() {
    // Load sounds for Diamond Rush
    LoadSound("diamond_collect", "resources/sounds/diamond_collect.wav");
    LoadSound("level_complete", "resources/sounds/level_complete.wav");
}

void AssetManager::LoadFonts() {
    // Load fonts for Diamond Rush
    LoadFont("main_font", "resources/fonts/main_font.ttf");
}

void AssetManager::LoadLevels() {
    // Load level data for Diamond Rush
    for (int i = 1; i <= 3; i++) {
        LoadLevelData("level" + std::to_string(i), "resources/levels/level" + std::to_string(i) + ".dat");
    }
}

// Cleanup
void AssetManager::UnloadAll() {
    for (auto& texture : textures) {
        ::UnloadTexture(texture.second);
    }
    textures.clear();
    spriteSheetInfo.clear();
    
    for (auto& sound : sounds) {
        ::UnloadSound(sound.second);
    }
    sounds.clear();
    
    for (auto& font : fonts) {
        ::UnloadFont(font.second);
    }
    fonts.clear();
    
    levelData.clear();
}

void AssetManager::UnloadTexture(const std::string& name) {
    if (textures.find(name) != textures.end()) {
        ::UnloadTexture(textures[name]);
        textures.erase(name);
    }
}

void AssetManager::UnloadSound(const std::string& name) {
    if (sounds.find(name) != sounds.end()) {
        ::UnloadSound(sounds[name]);
        sounds.erase(name);
    }
}

void AssetManager::UnloadFont(const std::string& name) {
    if (fonts.find(name) != fonts.end()) {
        ::UnloadFont(fonts[name]);
        fonts.erase(name);
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