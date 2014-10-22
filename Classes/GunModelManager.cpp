//
//  GunModelManager.cpp
//  Shooting
//
//  Created by wilford on 14-8-4.
//
//

#include "GunModelManager.h"
#include "json/document.h"
#include "cocostudio/DictionaryHelper.h"

string GunModelManager::ID = "id";
string GunModelManager::NAME = "name";
string GunModelManager::TYPE = "type";
string GunModelManager::HANDTYPE = "handtype";
string GunModelManager::ATK = "atk";
string GunModelManager::DURATION = "duration";
string GunModelManager::B_COUNT ="b_count";
string GunModelManager::RELOAD_TIME = "reload_time";
string GunModelManager::B_SPEED = "b_speed";
string GunModelManager::SPEED = "speed";
string GunModelManager::PRECISION = "precision";
string GunModelManager::P_SPEED = "p_speed";
string GunModelManager::P_BACK_SPEED = "p_back_speed";
string GunModelManager::RANGE = "range";
string GunModelManager::SHOOT_BULLETS = "shoot_bullets";
string GunModelManager::INIT_CLIPS = "init_clips";
string GunModelManager::PRICE = "price";
string GunModelManager::UNLOCK = "unlock";
string GunModelManager::DES = "des";
string GunModelManager::BULLET_WAY = "bullet_way";
string GunModelManager::BULLET_IS_CROSS = "bullet_is_cross";
string GunModelManager::BULLET_OUTRANGE = "bullet_outrange";
string GunModelManager::BULLET_OUTRANGE_2 = "bullet_outrange_2";
string GunModelManager::BULLET_COLLISION = "bullet_collision";
string GunModelManager::BULLET_COLLISION_2 = "bullet_collision_2";
string GunModelManager::B_FILE_ID = "b_file_id";
string GunModelManager::B_ANIM_ID = "b_anim_id";
string GunModelManager::GUN_EFFECT0_OFFSET = "gun_effect0_offset";
string GunModelManager::GUN_EFFECT1_OFFSET = "gun_effect1_offset";
string GunModelManager::G_EF0_FILE_ID = "g_ef0_file_id";
string GunModelManager::G_EF0_ANIM_ID = "g_ef0_anim_id";
string GunModelManager::G_EF1_FILE_ID = "g_ef1_file_id";
string GunModelManager::G_EF1_ANIM_ID = "g_ef1_anim_id";


GunModelManager::GunModelManager(){
    std::string filePath = FileUtils::getInstance()->fullPathForFilename("guns/guns.json");
    std::string contentStr = FileUtils::getInstance()->getStringFromFile(filePath);
    Document d;
    d.Parse<rapidjson::kParseDefaultFlags>(contentStr.c_str());
    
    size_t size = d.Size();
    
    for (int i = 0; i < size; i++) {
        const rapidjson::Value& root = DICTOOL->getSubDictionary_json(d, i);
        GunModel* model = new GunModel();
        model->id = root[ID.c_str()].GetInt();
        model->name = root[NAME.c_str()].GetString();
        model->type = root[TYPE.c_str()].GetInt();
        model->handtype = static_cast<HAND_TYPE>(root[HANDTYPE.c_str()].GetInt());
        model->atk = root[ATK.c_str()].GetInt();
        model->duration = root[DURATION.c_str()].GetDouble();
        model->b_count = root[B_COUNT.c_str()].GetInt();
        model->reload_time = root[RELOAD_TIME.c_str()].GetDouble();
        model->b_speed = root[B_SPEED.c_str()].GetDouble();
        model->speed = root[SPEED.c_str()].GetDouble();
        model->precision = root[PRECISION.c_str()].GetDouble();
        model->p_speed = root[P_SPEED.c_str()].GetDouble();
        model->p_back_speed = root[P_BACK_SPEED.c_str()].GetDouble();
        model->range = root[RANGE.c_str()].GetDouble();
        model->shoot_bullets = root[SHOOT_BULLETS.c_str()].GetInt();
        model->init_clips = root[INIT_CLIPS.c_str()].GetInt();
        model->price = root[PRICE.c_str()].GetInt();
        model->des = root[DES.c_str()].GetString();
        model->bullet_way = root[BULLET_WAY.c_str()].GetInt();
        model->bullet_is_cross = root[BULLET_IS_CROSS.c_str()].GetInt();
        model->bullet_outrange = root[BULLET_OUTRANGE.c_str()].GetInt();
        if (!root[BULLET_OUTRANGE_2.c_str()].IsNull()) {
            model->bullet_outrange_2 = root[BULLET_OUTRANGE_2.c_str()].GetInt();
        }else{
            model->bullet_outrange_2 = 0;
        }
        
        model->bullet_collision = root[BULLET_COLLISION.c_str()].GetInt();
        if (!root[BULLET_COLLISION_2.c_str()].IsNull()) {
            model->bullet_collision_2 = root[BULLET_COLLISION_2.c_str()].GetInt();
        }else{
            model->bullet_collision_2 = 0;
        }
        
        model->b_file_name = string(BULLET_FILE_PATH)+ string(BULLET_FILE_NAME) +to_string(root[B_FILE_ID.c_str()].GetInt())+".ExportJson";
        model->b_anim_name = string(BULLET_ANIM)+ to_string(root[B_ANIM_ID.c_str()].GetInt());
        model->gun_effect0_offset = root[GUN_EFFECT0_OFFSET.c_str()].GetDouble();
        model->gun_effect1_offset = root[GUN_EFFECT1_OFFSET.c_str()].GetDouble();
        if (root[G_EF0_FILE_ID.c_str()].GetInt() != -1) {
            model->g_ef0_file_name = string(FIRE_EFFECT_FILE_PATH)+ to_string(root[G_EF0_FILE_ID.c_str()].GetInt())+".ExportJson";
            model->g_ef0_anim_name = string(FIRE_EFFECT_ANIM)+ to_string(root[G_EF0_ANIM_ID.c_str()].GetInt());
        }else{
            model->g_ef0_file_name = "";
        }
        if (root[G_EF1_FILE_ID.c_str()].GetInt()!=-1) {
            model->g_ef1_file_name = string(CARTRIDGE_FILE_PATH) + to_string(root[G_EF1_FILE_ID.c_str()].GetInt()) + ".ExportJson";
            model->g_ef1_anim_name = string(CARTRIDGE_ANIM)+ to_string(root[G_EF1_ANIM_ID.c_str()].GetInt());
        }else{
            model->g_ef1_file_name = "";
        }
        
//        model->bullet_outrange = 1;
//        model->bullet_outrange_2 = 0;
//        model->bullet_collision = 1,
//        model->bullet_collision_2 = 0;
        
        _models.pushBack(model);
    }
}
