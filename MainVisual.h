#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "KDTree.h"
#include "KDNode.h"

class MainVisual : public cocos2d::Layer
{
public:
    cocos2d::DrawNode* drawNode;
    cocos2d::DrawNode* line;
    cocos2d::Label* text;
    cocos2d::Size winSize;
    
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    void drawPoint(KDNode* tree, KDNode* parent = NULL);
    
    // implement the "static create()" method manually
    CREATE_FUNC(MainVisual);
};

#endif // __HELLOWORLD_SCENE_H__
