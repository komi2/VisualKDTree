//
//  KDTree.cpp
//  VisualKDTree
//
//  Created by shuhei_komino on 2014/11/20.
//
//

#include "KDTree.h"

void KDTree::build(std::vector<Vec2> vecList, KDNode*& tree, int crtDep)
{
    int dep = crtDep+1;
    
    if(vecList.size() == 0) {
        return;
    }
    
    else {
        bool isRight;
        std::vector<Vec2> RIGHT, LEFT;
        
        // Get median
        Vec2 M = this->getMedian(vecList, dep % 2);
        
        if(tree == NULL) {
            tree = new KDNode;
            tree->depth = dep;
            tree->vec2 = M;
            tree->left = NULL; tree->right = NULL;
        }
        
        // divide data to right and left from median
        for(int i=0; i<vecList.size(); i++) {
            if(dep % 2 == 0) {
                isRight = (M.y < vecList[i].y);
            } else {
                isRight = (M.x < vecList[i].x);
            }
            
            if(isRight) {
                RIGHT.push_back(vecList[i]);
            } else {
                LEFT.push_back(vecList[i]);
            }
        }

        CCLOG("MEDIAN = (%f, %f)", M.x, M.y);
//        for(int j=0; j<RIGHT.size(); j++) {
//            CCLOG("RIGHT = (%f, %f)", RIGHT[j].x, RIGHT[j].y);
//        }
        
        this->build(RIGHT, tree->right, tree->depth);
        this->build(LEFT, tree->left, tree->depth);
    }
}

Vec2 KDTree::getMedian(std::vector<Vec2>& vecList, int num)
{
    int last = (int) vecList.size()-1;
    
    // sort
    this->qsort(vecList, 0, last, num);
    
    // median
    Vec2 M = vecList[last / 2];
    
    // delete median data
    vecList.erase(std::remove(vecList.begin(), vecList.end(), M), vecList.end());
    
    return M;
}

Vec2 KDTree::med3(Vec2 x, Vec2 y, Vec2 z, int num)
{
    int a, b, c;
    
    if(num == 0) {
        a = x.y; b = y.y; c = z.y;
    } else {
        a = x.x; b = y.x; c = z.x;
    }
    
    if (a < b) {
        if(b < c) return y;
        else if(c < a) return x;
        else return z;
    } else {
        if(c < b) return y;
        else if(a < c) return x;
        else return z;
    }
}

void KDTree::qsort(std::vector<Vec2>& vecList, int left, int right, int num)
{
    if (left < right) {
        int i = left, j = right;
        Vec2 tmp, pivot = this->med3(vecList[i], vecList[i + (j - i) / 2], vecList[j], num);
        
        while (1) {
            if(num == 0) {
                while (vecList[i].y < pivot.y) i++;
                while (pivot.y < vecList[j].y) j--;
            } else {
                while (vecList[i].x < pivot.x) i++;
                while (pivot.x < vecList[j].x) j--;
            }

            if (i >= j) break;
            tmp = vecList[i];
            vecList[i] = vecList[j];
            vecList[j] = tmp;
            i++; j--;
        }
        
        this->qsort(vecList, left, i - 1, num);
        this->qsort(vecList, j + 1, right, num);
    }
}