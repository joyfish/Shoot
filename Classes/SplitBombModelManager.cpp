//
//  SplitBombModelManager.cpp
//  Shooting
//
//  Created by wilford on 14-8-28.
//
//

#include "SplitBombModelManager.h"

string SplitBombModelManager::ID = "id";
string SplitBombModelManager::FILE_NAME = "file_name";
string SplitBombModelManager::ANIM_NAME = "anim_name";
string SplitBombModelManager::COUNT = "count";
string SplitBombModelManager::B_SPEED = "b_speed";
string SplitBombModelManager::RANGE = "range";
string SplitBombModelManager::IS_CROSS = "is_cross";


SplitBombModelManager::SplitBombModelManager(){
    std::string filePath = FileUtils::getInstance()->fullPathForFilename("split_bombs/split_bombs.json");
    std::string contentStr = FileUtils::getInstance()->getStringFromFile(filePath);
    Document d;
    d.Parse<rapidjson::kParseDefaultFlags>(contentStr.c_str());
    
    size_t size = d.Size();
    
    for (int i = 0; i < size; i++) {
        const rapidjson::Value& root = DICTOOL->getSubDictionary_json(d, i);
        SplitBombModel* model = new SplitBombModel();
        model->id = root[ID.c_str()].GetInt();
        model->file_name = root[FILE_NAME.c_str()].GetString();
        model->anim_name = root[ANIM_NAME.c_str()].GetString();
        model->count = root[COUNT.c_str()].GetInt();
        model->b_speed = root[B_SPEED.c_str()].GetDouble();
        model->range = root[RANGE.c_str()].GetDouble();
        model->is_cross = root[IS_CROSS.c_str()].GetInt();
        _models.pushBack(model);
    }
}