//
//  NormalBombModelManager.cpp
//  Shooting
//
//  Created by wilford on 14-8-28.
//
//

#include "NormalBombModelManager.h"

string NormalBombModelManager::ID = "id";
string NormalBombModelManager::FILE_NAME = "file_name";
string NormalBombModelManager::ANIM_NAME = "anim_name";
string NormalBombModelManager::DURATION = "duration";


NormalBombModelManager::NormalBombModelManager(){
    std::string filePath = FileUtils::getInstance()->fullPathForFilename("normal_bombs/normal_bombs.json");
    std::string contentStr = FileUtils::getInstance()->getStringFromFile(filePath);
    Document d;
    d.Parse<rapidjson::kParseDefaultFlags>(contentStr.c_str());
    
    size_t size = d.Size();
    
    for (int i = 0; i < size; i++) {
        const rapidjson::Value& root = DICTOOL->getSubDictionary_json(d, i);
        NormalBombModel* model = new NormalBombModel();
        model->id = root[ID.c_str()].GetInt();
        model->file_name = root[FILE_NAME.c_str()].GetString();
        model->anim_name = root[ANIM_NAME.c_str()].GetString();
        model->duration = root[DURATION.c_str()].GetDouble();
        _models.pushBack(model);
    }
}