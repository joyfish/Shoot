//
//  Location.h
//  Shoot
//
//  Created by wilford on 14/10/22.
//
//

#ifndef __Shoot__Location__
#define __Shoot__Location__

#include "cocos2d.h"
#include "json/document.h"


using namespace cocos2d;
using namespace rapidjson;

#define loc(__T__) \
Location::S()->getString(__T__)

class Location{
    
public:
    static Location* S(){
        if (instance == NULL) {
            instance = new Location();
        }
        return instance;
    }
    
    static void purge(){
        CC_SAFE_DELETE(instance);
        instance = NULL;
    }
    
    const std::string getString(std::string key){
        return d[key.c_str()].GetString();
    }
    
    
private:
    Location(){
        std::string filePath = FileUtils::getInstance()->fullPathForFilename("location/cn.json");
        std::string contentStr = FileUtils::getInstance()->getStringFromFile(filePath);
        d.Parse<rapidjson::kParseDefaultFlags>(contentStr.c_str());
    }
    ~Location(){}
    
    
    Document d;
    static Location* instance;
};


#endif /* defined(__Shoot__Location__) */
