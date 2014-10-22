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
    
    
    
    //���췽��
    DropDownList::DropDownList(Label* label, Size size)
    : showLabel(label)
    , isShowMenu(false)
    , lastSelectedIndex(-1)
    ,onSelectedChanged(nullptr)
    {
        //������һ��menu���������ڻ�����ӵ���ͼ��
        
        
        mainMenu = CCMenu::create();
        mainMenu->setPosition(Point(size.width / 2, -size.height / 2));
        mainMenu->setColor(DROPDOWNLIST_NORMAL_COLOR3);
        mainMenu->retain();
        
        
        showLabel->setPosition(Point(size.width / 2, size.height / 2));
        showLabel->setColor(DROPDOWNLIST_LABEL_COLOR);
        
        
        this->addChild(showLabel);
        this->setContentSize(size);
    }
    //��������
    DropDownList::~DropDownList()
    {
        
    }
    //����ʵ�����󷽷�
    DropDownList* DropDownList::create(Label* label, Size size)
    {
        
        
        DropDownList* list = new DropDownList(label, size);
        list->autorelease();
        return list;
    }
    //��ȡ��ǰѡ��label��string
    std::string DropDownList::getString()
    {
        return showLabel->getString();
    }
    //��ȡ��ǰѡ�е�index
    int DropDownList::getSelectedIndex()
    {
        return lastSelectedIndex;
    }
    //����ѡ��index
    void DropDownList::setSelectedIndex(int index)
    {
        if (index == lastSelectedIndex) {
            return;
        }
        if (onSelectedChanged) {
            onSelectedChanged(index);
        }
        lastSelectedIndex = index;
        for (int i = 0, j = (int)selectLabels.size(); i < j; ++i)//���������б�
        {
            if (i == lastSelectedIndex)
            {
                bgLayers[i]->setColor(DROPDOWNLIST_HIGHLIGHT_COLOR3);//��ǰѡ�еľ͸���
                showLabel->setString(selectLabels[i]->getString());//showLabel����ʾ��ѡ�е�
            }
            else
            {
                bgLayers[i]->setColor(DROPDOWNLIST_NORMAL_COLOR3);//����δ��ѡ�еľ�normal
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
        Point location =   touch->getLocation(); //��ȡ������ľ���λ������
        if (!boundingBox().containsPoint(location)) {
            if (isShowMenu)  //�����˵��Ǵ򿪵�״̬
            {
                onClose();
                return true;
            }

            return false;
        }
        
//        CCLOG("BEGAN------------------------------");
//        CCLOG("location : %f,%f", location.x, location.y);
        
        
        if (isShowMenu==false)  //�����˵��ǹر�״̬
        {
            isShowMenu = true;
            addChild(mainMenu,1);//�򿪲˵�
            for (int i = 0, j = (int)selectLabels.size(); i < j; ++i)//����selectlabel
            {
                if (i == lastSelectedIndex)
                {
                    bgLayers[i]->setColor(DROPDOWNLIST_HIGHLIGHT_COLOR3);//ѡ�и���
                }
                else
                {
                    bgLayers[i]->setColor(DROPDOWNLIST_NORMAL_COLOR3);
                }
            }
        }
        
        return true;
    }
    
    
    //������menu item �����һ��label���ǵ�����
    void DropDownList:: addLabel(Label* label)
    {
        Size size = getContentSize();//��ȡ��ǰ�����˵��Ĵ�С
        
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
    
    
    //ѡ�������б��
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
        //�ر������б��
    }
    
    
    //�ر������б��
    void DropDownList::onClose()
    {
        if (isShowMenu) {
            removeChild(mainMenu, true);  //ͨ��ɾ��mainMenu,�ر������б��
            isShowMenu = false;
        }
        
    }
    
    
}


NS_CC_END