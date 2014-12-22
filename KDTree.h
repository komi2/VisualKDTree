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

USING_NS_CC;

class KDTree
{
public:
    std::vector<cocos2d::Vec2> vecList;
    
    int depth = 0;

    // Build a blanced tree
    void build(std::vector<Vec2> vecList, KDNode*& tree, int crtDep = -1);
    
    // Insert new data
    void insert(KDNode*& tree, Vec2 newData, int dep = -1);
    
    Vec2 getMedian(std::vector<Vec2>& vecList, int num);
    Vec2 med3(Vec2 x, Vec2 y, Vec2 z, int num);
    
    void qsort(std::vector<Vec2>& vecList, int left, int right, int num);
    
    //TODO
    // nns
    // delete
};

#endif
