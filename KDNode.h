//
//  KDNode.h
//  VisualKDTree
//
//  Created by shuhei_komino on 2014/11/20.
//
//

#ifndef VisualKDTree_KDNode_h
#define VisualKDTree_KDNode_h

#include "cocos2d.h"

class KDNode
{
public:
    int depth;
    cocos2d::Vec2 vec2;
    cocos2d::Vec2 point;
    KDNode* left;
    KDNode* right;
};

#endif
