//
//  GameLayerTest.cpp
//  Shooting
//
//  Created by wilford on 14-7-22.
//
//

#include "GameLayerTest.h"
#include <string>
#include <sstream>
#include "SplitBombModelManager.h"
#include "NormalBombModelManager.h"
#include "common.h"
#include "ArmatureFactory.h"

template <typename T>
std::string to_string(T value)
{
    std::ostringstream os ;
    os << value ;
    return os.str() ;
}

bool GameLayerTest::init(){
    if (!Layer::init() )
    {
        return false;
    }

    do{
        
        
        _gameLayer = Layer::create();
        _controllerlayer = Layer::create();
        _manLayer = Node::create();
        _bulletLayer = Node::create();
        _effectDownLayer = Node::create();
        _effectUpLayer = Node::create();
        _bombLayer = Node::create();
        this->addChild(_gameLayer,0);
        _gameLayer->addChild(_manLayer,10);
        _gameLayer->addChild(_bulletLayer,7);
        _gameLayer->addChild(_effectDownLayer,9);
        _gameLayer->addChild(_effectUpLayer,11);
        _gameLayer->addChild(_bombLayer,15);
        this->addChild(_controllerlayer,10);
        
        _map = TMXTiledMap::create("map/map.tmx");
        
        CC_BREAK_IF(!_map);
        
        Size _mapSize = _map->getContentSize();
        
        
        ElementBase* box = ElementBase::create();
        box->setPhysicsBody(PhysicsBody::createEdgeBox(_map->getContentSize(),PHYSICSBODY_MATERIAL_DEFAULT,20));
        box->getPhysicsBody()->setContactTestBitmask(WALL_CONTACT_MASK);
        box->getPhysicsBody()->setCollisionBitmask(WALL_COLLISION_MASK);
        box->setAnchorPoint(Point::ANCHOR_MIDDLE);
        box->setPosition(_mapSize.width/2, _mapSize.height/2);
        _gameLayer->addChild(box);
        //_map->setVisible(false);
        
//        auto bgLayer = _map->getLayer("bg");
//        bgLayer->setAnchorPoint(_nBottomLeft);
//        bgLayer->setPosition(Point(_pLeft,_pBottom));
//        
//        TMXObjectGroup* objects = _map->getObjectGroup("box");
//        
//        ElementBase *boxOfPoint = NULL;
//        int count = 1;
//        ValueMap point;
//        
////        for (auto child : _map->getChildren()){
////            SpriteBatchNode* n = dynamic_cast<SpriteBatchNode*>(child);
////            n->getTexture()->setAntiAliasTexParameters();
////        }
//        
//        
//        point = objects->getObject(std::string("wall")+to_string(count));
//        while (point.begin()!= point.end())
//        {
//            float x = point.at("x").asFloat();
//            float y = point.at("y").asFloat();
//            float w = point.at("width").asFloat();
//            float h = point.at("height").asFloat();
//            boxOfPoint = ElementBase::create();
//            boxOfPoint->setPosition(Point(x+w/2, y+h/2));
//            boxOfPoint->setAnchorPoint(Point::ANCHOR_MIDDLE);
//            boxOfPoint->setPhysicsBody(PhysicsBody::createBox(Size(w, h)));
//            _gameLayer->addChild(boxOfPoint,10);
//            boxOfPoint->getPhysicsBody()->setDynamic(false);
//            boxOfPoint->getPhysicsBody()->setContactTestBitmask(WALL_CONTACT_MASK);
//            boxOfPoint->getPhysicsBody()->setCollisionBitmask(WALL_COLLISION_MASK);
//            count++;
//            point = objects->getObject(std::string("wall")+to_string(count));
//        }  
//        boxOfPoint = NULL;
        _gameLayer->addChild(_map, 0);
        
        int xLineCount = floor(_mapSize.width/55);
        int yLineCount = floor(_mapSize.height/55);
        Array2D<Cell> man_Map = Array2D<Cell>(xLineCount,yLineCount);
        for (int x =0;x<xLineCount;x++) {
            for (int y =0; y<yLineCount; y++) {
                Cell *cell = new Cell();
                cell->setX(x);
                cell->setY(y);
                cell->setWeight(1);
                //cell->setWeight(t_getRandom(4) == 0?4:1);
                man_Map.Set(x,y,cell);
            }
        }
        
//        man_line_container = LineContainer::create(xLineCount,yLineCount,55,55);
//        man_line_container ->updateMapParameter(man_Map);
//        
//        _gameLayer->addChild(man_line_container,5);
        
        man_AStar = new mAStar(man_Map,55,55);
     //   _animation = CocAnimationTest::create(_gameLayer);
     //   CC_BREAK_IF(!_animation);
        _hero = HeroFactory::create(0,man_AStar);
        
        CC_ASSERT(_hero);
        _manLayer->addChild(_hero);
        _hero->setPosition(Point(_pCenterX,_pCenterY));
        _hero->setTag(999);
        _hero->onFire = bind(&GameLayerTest::onFire, this,placeholders::_1,placeholders::_2,placeholders::_3,placeholders::_4,placeholders::_5,placeholders::_6);
        
        Sprite *spJs=Sprite::create("game/joystick.png");//Ò¡¸Ë
        Sprite *spJsBG=Sprite::create("game/joystick_bg.png");//Ò¡¸Ë±³¾°
        CcJoystick *joystick=CcJoystick::CcJoystickWithCenter(Point(130,130),70.0f ,spJs ,spJsBG,false);//´´½¨Ò¡¸Ë
        for (int i=0; i<5; i++) {
            Sprite* e = Sprite::create("game/joystick_effect_"+to_string(i)+string(".png"));
            joystick->addChild(e);
            if (i%2 == 0) {
                e->runAction(CCRepeatForever::create(CCRotateBy::create(2.0f, 30)));
            }else{
                e->runAction(CCRepeatForever::create(CCRotateBy::create(2.0f, -30)));
            }
            
            e->setPosition(Point(130,130));
        }
        CC_BREAK_IF(!joystick);
        joystick->onDirectionChanged = [&](Point dir){
            _jsDir = dir;
//            if (_animation) {
//                _animation->move(_jsDir*300);
//            }
            if (_hero) {
                _hero->move(_jsDir);
            }
        };
        _controllerlayer->addChild(joystick,10);//Ò¡¸ËÌí¼Óµ½layerÖÐ
        
//        Sprite *spJs1=Sprite::create("joystick.png");//Ò¡¸Ë
//        Sprite *spJsBG1=Sprite::create("joystick_bg.png");//Ò¡¸Ë±³¾°
//        CcJoystick *joystick1=CcJoystick::CcJoystickWithCenter(Point(_pRight-130.0f,_pBottom+130.0f),90.0f ,spJs1 ,spJsBG1,false);//´´½¨Ò¡¸Ë
//        CC_BREAK_IF(!joystick);
//        joystick1->onDirectionChanged = [&](Point dir){
//            if (dir!=Point::ZERO) {
//                _hero->dir(dir);
//            }
//            
//            if (_bulletDir == Point::ZERO) {
//                _hero->startFire();
//            }
//            if (dir == Point::ZERO) {
//                _hero->endFire();
//            }
//            
//            
//            _bulletDir = dir;
//        };
//        _controllerlayer->addChild(joystick1,10);//Ò¡¸ËÌí¼Óµ½layerÖÐ
        
        auto dispatcher = Director::getInstance()->getEventDispatcher();
    
        
        auto listener = EventListenerTouchOneByOne::create();
        listener->onTouchBegan = CC_CALLBACK_2(GameLayerTest::onTouchBegan, this);
        listener->onTouchMoved = CC_CALLBACK_2(GameLayerTest::onTouchMoved, this);
        listener->onTouchEnded = CC_CALLBACK_2(GameLayerTest::onTouchEnded, this);
        listener->setSwallowTouches(true);
        dispatcher->addEventListenerWithSceneGraphPriority(listener, this);
        
//        EventListenerCustom* _listener = EventListenerCustom::create("game_custom_event1", [=](EventCustom* event){
//            std::string str("Custom event 1 received, ");
//            char* buf = static_cast<char*>(event->getUserData());
//            str += buf;
//            str += " times";
//            CCLOG("%s",str.c_str());
//        });
//        
//        EventListenerCustom* _listener1 = EventListenerCustom::create("game_custom_event1", [=](EventCustom* event){
//            std::string str("Custom event 2 received, ");
//            char* buf = static_cast<char*>(event->getUserData());
//            str += buf;
//            str += " times";
//            CCLOG("%s",str.c_str());
//        });
//        
//        _eventDispatcher->addEventListenerWithFixedPriority(_listener, 1);
//        _eventDispatcher->addEventListenerWithFixedPriority(_listener1, 2);
//        
//        static int count = 0;
//        ++count;
//        char* buf = new char[10];
//        sprintf(buf, "%d", count);
//        EventCustom event("game_custom_event1");
//        event.setUserData(buf);
//        _eventDispatcher->dispatchEvent(&event);
//        CC_SAFE_DELETE_ARRAY(buf);

//        auto listener = EventListenerTouchAllAtOnce::create();
//        listener->onTouchesBegan = CC_CALLBACK_2(GameLayerTest::onTouchesBegan,this);
//        dispatcher->addEventListenerWithSceneGraphPriority(listener, this);
        
        
        
        ElementsContact* contactNode = ElementsContact::create();
        this->addChild(contactNode);
        
        label_bullets = Label::createWithTTF("Bullets", "STXINGKA.ttf", 30);
        label_clips = Label::createWithTTF("Clips", "STXINGKA.ttf", 30);
        
        this->addChild(label_clips);
        this->addChild(label_bullets);
        
        label_bullets->setPosition(Point(_pCenterX-50,_pTop-20));
        label_clips->setPosition(Point(_pCenterX+100,_pTop-20));
        label_bullets->setAnchorPoint(_nLeft);
        label_clips->setAnchorPoint(_nLeft);
        
        
      ;
        
        return true;
    }while (0);
    return false;
}

void GameLayerTest::onEnter(){
    Layer::onEnter();
    Label* label = Label::createWithTTF("", "STXINGKA.ttf", 30);

    
    DropDownList* list = DropDownList::create(label, Size(200,50));
    Vector<GunModel*> _models = GunModelManager::getInstance()->getModels();
    for (auto m : _models) {
        list->addLabel(Label::createWithTTF(m->name.c_str(), "STXINGKA.ttf", 30));
        Gun* g = Gun::create(m->id);
        g->retain();
        gunlist.push_back(g);
    }
   
    
    this->addChild(list);
    list->setPosition(Point(_pLeft,_pTop-45));
    
    list->onSelectedChanged = CC_CALLBACK_1(GameLayerTest::onGunChanged, this);
    
    list->setSelectedIndex(0);
    
//    CCLOG("%s",NormalBombModelManager::getInstance()->getModelByID(0)->file_name.c_str());
//    CCLOG("%s",SplitBombModelManager::getInstance()->getModelByID(0)->file_name.c_str());
    
    BulletFactory::init(_bulletLayer);
    NormalBombFactory::init(_bulletLayer);
    SplitBombFactory::init(_bulletLayer);
    
    
    scheduleUpdate();
}

void GameLayerTest::onExit(){
    Layer::onExit();
}

void GameLayerTest::update(float dt){
//    if (_animation) {
//        _animation->move(_jsDir*100);
//    }
    if (_istouched) {
//        if (_animation) {
//            _animation->dir(_touchPoint);
//        }
        if (_hero) {
            _hero->dir(_touchPoint-_hero->getPosition());
        }
    }
    
   
    
    keepHeroInCenter();
    updateGunBulletsAndClips();
}

void GameLayerTest::onFire(ElementType type, cocos2d::Point b_point,Point c_point, float r_rotate,float rotate, const GunModel& gunModel){
    //LOG_FUNCTION_LIFE
    if (gunModel.shoot_bullets <= 0) {
        return;
    }
    if (gunModel.shoot_bullets>1) {
        int shoot_bullets = gunModel.shoot_bullets;
        float r_padding = gunModel.precision/(shoot_bullets-1);
        float start_rotate = rotate - gunModel.precision/2;
        for (int i=0;i<shoot_bullets; i++) {
            BulletFactory::create(type,b_point,start_rotate+r_padding*i,gunModel);
        }
    }else{
         BulletFactory::create(type,b_point,r_rotate,gunModel);
    }
    
    
    
    function<void(Armature*,MovementEventType,string)> callback = [](Armature* armature, MovementEventType evt, string animationName){
        switch (evt) {
            case cocostudio::COMPLETE:
            armature->removeFromParent();
            break;
            default:
            break;
        }
    };

    
    if (!gunModel.g_ef1_file_name.empty()) {
        ArmatureFactory::create(_effectUpLayer, c_point, rotate, gunModel.g_ef1_file_name, gunModel.g_ef1_anim_name);
    }
    
    
    
    if (!gunModel.g_ef0_file_name.empty()) {
        ArmatureFactory::create(_effectDownLayer, b_point, rotate, gunModel.g_ef0_file_name, gunModel.g_ef0_anim_name);
    }
    
    

}

void GameLayerTest::onGunChanged(int idx){
//    GunModel* gunModel = GunModelManager::getInstance()->getModel(idx);
//    if (gunModel) {
        if (_hero) {
            _hero->changeGun(gunlist[idx]);
        }
//    }
}

void GameLayerTest::keepHeroInCenter(){
    if (_hero->getPosition() == _heroPrePoint) {
        
        return;
    }
//    log("hero_pos %f,%f",_hero->getPosition().x,_hero->getPosition().y);
    Size mapSize = _map->getContentSize();
    Rect layerLimit = Rect(0,0,mapSize.width-_pRight,mapSize.height-_pTop);
    
    //Point heroInWorld = _gameLayer-> convertToWorldSpace(_animation->pos());
    Point heroInWorld = _manLayer-> convertToWorldSpace(_hero->getPosition());
    Point offsetPosition = Point(_pCenterX,_pCenterY) - heroInWorld;
    
//    log("heroInWorld %f,%f",heroInWorld.x,heroInWorld.y);

    
    Point pos = _gameLayer->getPosition()+offsetPosition;
    pos.x = MAX(-layerLimit.getMaxX(),pos.x);
    pos.x = MIN(-layerLimit.getMinX(),pos.x);
    pos.y = MAX(-layerLimit.getMaxY(),pos.y);
    pos.y = MIN(-layerLimit.getMinY(),pos.y);
    PositionNodeWithPhysicsChildren(_gameLayer,pos);//    _gameLayer->setPosition(pos);
    _heroPrePoint =_hero->getPosition();
//    log("physicsBoy %f,%f",_hero->getPhysicsBody()->getPosition().x,_hero->getPhysicsBody()->getPosition().y);
}

void GameLayerTest::updateGunBulletsAndClips(){
    label_bullets->setString("Bullets:"+ to_string(_hero->getGunData()->getBCount()));
    label_clips->setString("Clips:"+to_string(_hero->getGunData()->getClips()));
}

bool GameLayerTest::onTouchBegan(cocos2d::Touch *pTouch, cocos2d::Event *pEvent){
    _istouched = true;
    _touchPoint = pTouch->getLocation()- _gameLayer->getPosition();
    _hero->dir(_touchPoint-_hero->getPosition());
    _hero->startFire();
    //_hero->AIMoveTo(_touchPoint);
    
    return true;
}

void GameLayerTest::onTouchMoved(cocos2d::Touch *pTouch, cocos2d::Event *pEvent){
    _touchPoint = pTouch->getLocation()- _gameLayer->getPosition();
}

void GameLayerTest::onTouchEnded(cocos2d::Touch *pTouch, cocos2d::Event *pEvent){
    _istouched = false;
    _hero->endFire();
}
