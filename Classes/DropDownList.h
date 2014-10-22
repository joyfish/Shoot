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
    //设置背景颜色
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
        //构造方法
        DropDownList(Label* label, Size size);
        
        
        //析构函数
        ~DropDownList();
        
        
        //创建实例对象方法
        static DropDownList* create(Label* label, Size size);
        
        
        //获取当前选中label的string
        std::string getString();
        
        
        //获取当前选中的index
        int getSelectedIndex();
        
        
        //设置选中index
        void setSelectedIndex(int index);
        
        void onEnter();
        
        //void registerWithTouchDispatcher();
        
        virtual bool onTouchBegan(Touch *touch, Event *event);
        
        //创建以menu item 并添加一个label覆盖到上面
        void addLabel(Label* label);
        
        
        //选中下拉列表后
        void onSelected(Ref* sender);
        
        
        //关闭下拉列表框
        void onClose();
    
        
        
    private:
        Menu* mainMenu;  //下拉列表选项的集合
        Label* showLabel;  //显示选中的结果
        std::vector<Label*> selectLabels;  //下拉列表label
        std::vector<LayerColor*> bgLayers; //用于设置 背景
        bool isShowMenu;  //是否显示了下拉列表
        int lastSelectedIndex;  //选中下拉列表的index
        
    public:
        std::function<void(int)> onSelectedChanged;
    };
}
NS_CC_END

#endif /* defined(__Shooting__DropDownList__) */
