//
//  KDTree.h
//  VisualKDTree
//
//  Created by shuhei_komino on 2014/11/20.
//
//

#ifndef VisualKDTree_KDTree_h
#define VisualKDTree_KDTree_h

#include "cocos2d.h"
#include "KDNode.h"

class KDTree
{
public:
    std::list<cocos2d::Vec2> vecList;
    
    int depth = 0;

    // Construct a tree
    void construct(cocos2d::Vec2 vec2, KDNode*& tree, int crtDep = -1);
    
    
    //TODO
    // insert
    // nns
    // balancing
    // delete
};

#endif
