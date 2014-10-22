//
//  DropDownList.h
//  Shooting
//
//  Created by wilford on 14-8-19.
//
//

#ifndef __Shooting__DropDownList__
#define __Shooting__DropDownList__

#include "cocos2d.h"
USING_NS_CC;


NS_CC_BEGIN
namespace CustomDropDownListBox
{
    
#define DROPDOWNLIST_LABEL_COLOR Color3B(255,255,255)
    //���ñ�����ɫ
#define DROPDOWNLIST_NORMAL_COLOR       Color4B(128, 128, 128, 255)
#define DROPDOWNLIST_SELECTED_COLOR     Color4B(200, 200, 200, 255)
#define DROPDOWNLIST_HIGHLIGHT_COLOR    Color4B(0, 0, 255, 255)
    
    
#define DROPDOWNLIST_NORMAL_COLOR3       Color3B(128, 128, 128)
#define DROPDOWNLIST_SELECTED_COLOR3     Color3B(200, 200, 200)
#define DROPDOWNLIST_HIGHLIGHT_COLOR3    Color3B(0, 0, 255)
    
#define DROPDOWNLIST_MAX_H 7
    
    
    class DropDownList : public Layer
    {
    public:
        //���췽��
        DropDownList(Label* label, Size size);
        
        
        //��������
        ~DropDownList();
        
        
        //����ʵ�����󷽷�
        static DropDownList* create(Label* label, Size size);
        
        
        //��ȡ��ǰѡ��label��string
        std::string getString();
        
        
        //��ȡ��ǰѡ�е�index
        int getSelectedIndex();
        
        
        //����ѡ��index
        void setSelectedIndex(int index);
        
        void onEnter();
        
        //void registerWithTouchDispatcher();
        
        virtual bool onTouchBegan(Touch *touch, Event *event);
        
        //������menu item �����һ��label���ǵ�����
        void addLabel(Label* label);
        
        
        //ѡ�������б��
        void onSelected(Ref* sender);
        
        
        //�ر������б��
        void onClose();
    
        
        
    private:
        Menu* mainMenu;  //�����б�ѡ��ļ���
        Label* showLabel;  //��ʾѡ�еĽ��
        std::vector<Label*> selectLabels;  //�����б�label
        std::vector<LayerColor*> bgLayers; //�������� ����
        bool isShowMenu;  //�Ƿ���ʾ�������б�
        int lastSelectedIndex;  //ѡ�������б��index
        
    public:
        std::function<void(int)> onSelectedChanged;
    };
}
NS_CC_END

#endif /* defined(__Shooting__DropDownList__) */
