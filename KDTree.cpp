//
//  KDTree.cpp
//  VisualKDTree
//
//  Created by shuhei_komino on 2014/11/20.
//
//

#include "KDTree.h"

USING_NS_CC;

void KDTree::construct(Vec2 vec2, KDNode*& tree, int crtDep)
{
    bool isRight;
    
    // Set Node
    if(tree == NULL) {
        tree = new KDNode;
        tree->depth = crtDep + 1;
        tree->vec2 = vec2;
        tree->left = NULL; tree->right = NULL;
        
    } else {
        if(tree->right == NULL || tree->left == NULL) {
            depth = tree->depth;
        }
        
        if(depth % 2 == 0) {
            isRight = (vec2.y > tree->vec2.y);
        } else {
            isRight = (vec2.x > tree->vec2.x);
        }
        
        // Right
        if(isRight) {
            if(tree->right != NULL) {
                depth++;
                this->construct(vec2, tree->right, tree->depth);
                return;
            }
            this->construct(vec2, tree->right, tree->depth);
        }
        
        // Left
        else {
            if(tree->right != NULL) {
                depth++;
                this->construct(vec2, tree->left, tree->depth);
                return;
            }
            this->construct(vec2, tree->left, tree->depth);
        }
    }
}