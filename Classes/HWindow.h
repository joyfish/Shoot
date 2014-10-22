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


//ʹ��ע�⣺
//1 �̳� HWindow ��������Ҫ�Ļ���WINDOW_SHOW(__T__) ���� WINDOW_SINGTON_SHOW(__T__)(��Ҫ�Լ�����static __T__* instance;) ��д�Զ��徲̬show(Node* node)����
//2 ��init��д�����ʼ������
//3 ��m_tips��ֵ�����Ǽ���Json��õĽ����Layout(ע�������Ӽ�����������"bg"�����ǵ��������ʵ�ʱ���)
//4 ����closeWindow�رս���
//5 �ڴ�����ʹ��__T__::show(node,data)��������


//����ͨ�ô�������
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

//�������д�������
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
    function<void()> onWindowIn;//��ӽ����Զ�����֮��Ļص�ʱ��
    function<void()> onWindowClosed;//��ӽ���ر�֮��Ļص��¼������ڴ��������ȫ�رպ�Ž��е�����
    
    //��д������������
    virtual void showWindow();
    //���ڹر�ʱ�ᱻ����
    virtual void close() override;
    //���õ��������Ƿ����
    void setTocuhEnable(bool enabled);
    
    virtual void update(float dt) override
    {
        IHWindow::update(dt);
    }
    
    //�رմ��ڵ�ʱ���������
    void closeWindow();
    
    HWindow();
    ~HWindow();
    
protected:
    
    
    //�򿪽���ʱ���ŵĶ�������д�����Զ��壬�������������onStartAnimOver,��дʱ��Ҫ�Լ���Ӽ�����������潫���¼�����
    virtual void startAnim();

    virtual void onStartAnimOver();
    
    //�رս���ʱ���ŵĶ�������д�����Զ��壬����������ص�onCloseAnimOver,��дʱ��Ҫ�Լ���Ӽ����������޷��رս���
    virtual void endAnim();
    
    //�رմ��ڶ�������һ��Ҫ���������������ʽ�رմ���
    void onCloseAnimOver();
    
    virtual void onClose();
    
    //���ý������Ķ���
    void setAnimType(WINDOW_ANIM anim_type){
        m_anim_type = anim_type;
    }
    
    
    //���ڶ���
    bool m_autoCenter;
    Widget* m_tips;
    //�������ڵ�Node
    Node* m_node;
    //window�İ�����
    HWindowsHelper* m_windowsHelper;
    
    
private:
    
    WINDOW_ANIM m_anim_type;
};




#endif /* defined(__Shooting__HWindow__) */
