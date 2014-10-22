//
//  HWindow.h
//  Shooting
//
//  Created by wilford on 14-10-14.
//
//

#ifndef __Shooting__HWindow__
#define __Shooting__HWindow__


#include "ScreenFit.h"
#include "HWindowsHelper.h"
#include "IHWindow.h"
#include "HWindowsManager.h"
#include "HGloba.h"

using namespace std;
using namespace ui;


//使用注意：
//1 继承 HWindow 无特殊需要的话用WINDOW_SHOW(__T__) 或者 WINDOW_SINGTON_SHOW(__T__)(需要自己定义static __T__* instance;) 重写自定义静态show(Node* node)方法
//2 在init编写界面初始化内容
//3 给m_tips赋值，它是加载Json获得的界面根Layout(注：它的子集必须命名给"bg"，它是弹出界面的实际背景)
//4 调用closeWindow关闭界面
//5 在代码中使用__T__::show(node,data)开启界面


//弹出通用窗口声明
#define WINDOW_SHOW(__T__) \
static __T__* show(Node* node,void* data=NULL)\
{ \
__T__* instance = new __T__(); \
instance -> m_node = node;\
instance->init(data);\
instance->showWindow();\
return instance;\
}\
void init(void* data);\

//弹出单列窗口声明
#define WINDOW_SINGTON_SHOW(__T__) \
static __T__* show(Node* node,void* data=nullptr) \
{ \
if(instance == nullptr){\
instance = new __T__(); \
instance -> m_node = node;\
instance->init(data);\
instance->showWindow();\
}\
return instance;\
}\
\
virtual void close() override{\
HWindow::close();\
instance = nullptr;\
log("__T__ Close");\
}\
static __T__* S(){return instance;}\
\
void init(void* data);\


enum WINDOW_ANIM{
    WINDOW_ANIM_TOP,
    WINDOW_ANIM_RIGHT,
    WINDOW_ANIM_LEFT,
    WINDOW_ANIM_BOTTOM,
    WINDOW_ANIM_NONE
};

class HWindow :public IHWindow{
public:
    function<void()> onWindowIn;//添加界面自动进入之后的回调时间
    function<void()> onWindowClosed;//添加界面关闭之后的回调事件（用于处理界面完全关闭后才进行的事务）
    
    //重写它来开启窗口
    virtual void showWindow();
    //窗口关闭时会被调用
    virtual void close() override;
    //设置弹出窗口是否可用
    void setTocuhEnable(bool enabled);
    
    virtual void update(float dt) override
    {
        IHWindow::update(dt);
    }
    
    //关闭窗口的时候请调用它
    void closeWindow();
    
    HWindow();
    ~HWindow();
    
protected:
    
    
    //打开界面时播放的动画，重写它来自定义，动画播放完调用onStartAnimOver,重写时需要自己添加监听，否则界面将无事件监听
    virtual void startAnim();

    virtual void onStartAnimOver();
    
    //关闭界面时播放的动画，重写它来自定义，动画播放完回调onCloseAnimOver,重写时需要自己添加监听，否则无法关闭界面
    virtual void endAnim();
    
    //关闭窗口动画结束一定要调用这个方法来正式关闭窗口
    void onCloseAnimOver();
    
    virtual void onClose();
    
    //设置界面进入的动画
    void setAnimType(WINDOW_ANIM anim_type){
        m_anim_type = anim_type;
    }
    
    
    //窗口对象
    bool m_autoCenter;
    Widget* m_tips;
    //窗口所在的Node
    Node* m_node;
    //window的帮助类
    HWindowsHelper* m_windowsHelper;
    
    
private:
    
    WINDOW_ANIM m_anim_type;
};




#endif /* defined(__Shooting__HWindow__) */
