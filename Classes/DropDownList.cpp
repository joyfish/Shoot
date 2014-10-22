//
//  DropDownList.cpp
//  Shooting
//
//  Created by wilford on 14-8-19.
//
//

#include "DropDownList.h"
#include "cocos2d.h"
USING_NS_CC;


NS_CC_BEGIN
namespace CustomDropDownListBox
{
    
    
    
    //构造方法
    DropDownList::DropDownList(Label* label, Size size)
    : showLabel(label)
    , isShowMenu(false)
    , lastSelectedIndex(-1)
    ,onSelectedChanged(nullptr)
    {
        //创建好一个menu，但是现在还不添加到视图中
        
        
        mainMenu = CCMenu::create();
        mainMenu->setPosition(Point(size.width / 2, -size.height / 2));
        mainMenu->setColor(DROPDOWNLIST_NORMAL_COLOR3);
        mainMenu->retain();
        
        
        showLabel->setPosition(Point(size.width / 2, size.height / 2));
        showLabel->setColor(DROPDOWNLIST_LABEL_COLOR);
        
        
        this->addChild(showLabel);
        this->setContentSize(size);
    }
    //析构函数
    DropDownList::~DropDownList()
    {
        
    }
    //创建实例对象方法
    DropDownList* DropDownList::create(Label* label, Size size)
    {
        
        
        DropDownList* list = new DropDownList(label, size);
        list->autorelease();
        return list;
    }
    //获取当前选中label的string
    std::string DropDownList::getString()
    {
        return showLabel->getString();
    }
    //获取当前选中的index
    int DropDownList::getSelectedIndex()
    {
        return lastSelectedIndex;
    }
    //设置选中index
    void DropDownList::setSelectedIndex(int index)
    {
        if (index == lastSelectedIndex) {
            return;
        }
        if (onSelectedChanged) {
            onSelectedChanged(index);
        }
        lastSelectedIndex = index;
        for (int i = 0, j = (int)selectLabels.size(); i < j; ++i)//遍历整个列表，
        {
            if (i == lastSelectedIndex)
            {
                bgLayers[i]->setColor(DROPDOWNLIST_HIGHLIGHT_COLOR3);//当前选中的就高亮
                showLabel->setString(selectLabels[i]->getString());//showLabel就显示被选中的
            }
            else
            {
                bgLayers[i]->setColor(DROPDOWNLIST_NORMAL_COLOR3);//其他未被选中的就normal
            }
        }
    }
    
    
    void DropDownList::onEnter()
    {
        CCLayer::onEnter();
        auto dispatcher = Director::getInstance()->getEventDispatcher();
        auto listener = EventListenerTouchOneByOne::create();
        listener->onTouchBegan = CC_CALLBACK_2(DropDownList::onTouchBegan, this);
        listener->setSwallowTouches(true);
        dispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    }
    
    
    
    bool DropDownList::onTouchBegan(Touch *touch, Event *event)
    {
        
        
        
        
        //Point locInView = touch->getLocationInView();
        Point location =   touch->getLocation(); //获取触摸点的绝对位置坐标
        if (!boundingBox().containsPoint(location)) {
            if (isShowMenu)  //下拉菜单是打开的状态
            {
                onClose();
                return true;
            }

            return false;
        }
        
//        CCLOG("BEGAN------------------------------");
//        CCLOG("location : %f,%f", location.x, location.y);
        
        
        if (isShowMenu==false)  //下拉菜单是关闭状态
        {
            isShowMenu = true;
            addChild(mainMenu,1);//打开菜单
            for (int i = 0, j = (int)selectLabels.size(); i < j; ++i)//遍历selectlabel
            {
                if (i == lastSelectedIndex)
                {
                    bgLayers[i]->setColor(DROPDOWNLIST_HIGHLIGHT_COLOR3);//选中高亮
                }
                else
                {
                    bgLayers[i]->setColor(DROPDOWNLIST_NORMAL_COLOR3);
                }
            }
        }
        
        return true;
    }
    
    
    //创建以menu item 并添加一个label覆盖到上面
    void DropDownList:: addLabel(Label* label)
    {
        Size size = getContentSize();//获取当前下拉菜单的大小
        
        LayerColor* normal = LayerColor::create(DROPDOWNLIST_NORMAL_COLOR, size.width, size.height);
        LayerColor* selected = LayerColor::create(DROPDOWNLIST_SELECTED_COLOR, size.width, size.height);
        
        
        bgLayers.push_back(normal);
        selectLabels.push_back(label);
        

        std::function<void(Ref*)> callback = CC_CALLBACK_1(DropDownList::onSelected,this);
        
        MenuItem* item = MenuItemSprite::create(
                                                    normal,
                                                    selected,
                                                    NULL,
                                                    callback
                                                    );
        
        
        label->setPosition(Point(size.width / 2, size.height / 2));
        //label->setColor(DROPDOWNLIST_LABEL_COLOR);
        item->addChild(label);
        item->setTag((int)selectLabels.size() - 1);
        item->setPosition((int)(selectLabels.size()-1)/DROPDOWNLIST_MAX_H*size.width, -((int)(selectLabels.size()-1)%DROPDOWNLIST_MAX_H) * size.height);
        
        mainMenu->addChild(item);
    }
    
    
    //选中下拉列表后
    void DropDownList::onSelected(Ref* sender)
    {
        MenuItem* item = dynamic_cast<MenuItem*>(sender);
        if (item)
        {
            if (item->getTag()!=lastSelectedIndex) {
                if (onSelectedChanged) {
                    onSelectedChanged(item->getTag());
                }
                lastSelectedIndex = item->getTag();
                showLabel->setString(selectLabels[item->getTag()]->getString());
            }
        }
        
        
        onClose();
        //关闭下拉列表框
    }
    
    
    //关闭下拉列表框
    void DropDownList::onClose()
    {
        if (isShowMenu) {
            removeChild(mainMenu, true);  //通过删除mainMenu,关闭下拉列表框
            isShowMenu = false;
        }
        
    }
    
    
}


NS_CC_END