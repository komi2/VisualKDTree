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
    
    if(vecList.size() == 0 || tree != NULL) {
        return;
    }
    
    else {
        std::vector<Vec2> RIGHT, LEFT;
        
        // Get median
        Vec2 M = this->getMedian(vecList, dep % 2);
        
        // Create node
        tree = new KDNode;
        tree->depth = dep;
        tree->vec2 = M;
        tree->left = NULL; tree->right = NULL;
        
        // divide data to right and left from median
        this->divideNode2LR(vecList, LEFT, RIGHT, M, dep);
        
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

void KDTree::divideNode2LR(std::vector<Vec2>& S, std::vector<Vec2>& L, std::vector<Vec2>& R, Vec2 M, int dep)
{
    bool isRight;
    
    for(int i=0; i<S.size(); i++) {
        if(dep % 2 == 0) {
            isRight = (M.y < S[i].y);
        } else {
            isRight = (M.x < S[i].x);
        }
        
        if(isRight) {
            R.push_back(S[i]);
        } else {
            L.push_back(S[i]);
        }
    }
}

void KDTree::insert(KDNode*& tree, Vec2 newData, int dep)
{
    bool isRight;
    
    // Set new data
    if(tree == NULL) {
        tree = new KDNode;
        tree->depth = ++dep;
        tree->vec2 = newData;
        tree->left = NULL; tree->right = NULL;
    }
    
    else {
        if(tree->depth == 0) {
            isRight = (tree->vec2.y < newData.y);
        } else {
            isRight = (tree->vec2.x < newData.x);
        }
        
        if(isRight) {
            this->insert(tree->right, newData, tree->depth);
        } else {
            this->insert(tree->left, newData, tree->depth);
        }
    }
}

void KDTree::deleteNode(KDNode*& tree, Vec2 node)
{
    if(tree == NULL) return;
    
    // Whether deleted
    if(tree->vec2.x == node.x && tree->vec2.y == node.y) {
        
        if(tree->left == NULL && tree->right == NULL) {
            tree = NULL;
        }
        
        else {
            std::vector<Vec2> vecList, L, R;
            collectLowerNode(tree, vecList);
            
            // Refresh
            tree->right = NULL;
            tree->left = NULL;
            tree->vec2 = this->getMedian(vecList, tree->depth);
            
            this->divideNode2LR(vecList, L, R, tree->vec2, tree->depth);
            
            // Re build
            this->build(L, tree->left, tree->depth);
            this->build(R, tree->right, tree->depth);
        }
    }
    
    // Re search
    else {
        this->deleteNode(tree->left, node);
        this->deleteNode(tree->right, node);
    }
}

void KDTree::collectLowerNode(KDNode*& tree, std::vector<Vec2>& vecList)
{
    if(tree->left != NULL) {
        vecList.push_back(tree->left->vec2);
        collectLowerNode(tree->left, vecList);
        tree->left = NULL;
    }
    
    if(tree->right != NULL) {
        vecList.push_back(tree->right->vec2);
        collectLowerNode(tree->right, vecList);
        tree->right = NULL;
    }
}




