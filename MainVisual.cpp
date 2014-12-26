#include "MainVisual.h"

USING_NS_CC;

Scene* MainVisual::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = MainVisual::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool MainVisual::init()
{
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    winSize = Director::getInstance()->getWinSize();
    KDTree* kdtree = new KDTree;
    KDNode* tree = NULL;

    // Test data
    kdtree->vecList.push_back(Vec2(4, 2));
    kdtree->vecList.push_back(Vec2(14, 5));
    kdtree->vecList.push_back(Vec2(5, 8));
    kdtree->vecList.push_back(Vec2(7, 7));
    kdtree->vecList.push_back(Vec2(2, 18));
    kdtree->vecList.push_back(Vec2(11, 3));
    kdtree->vecList.push_back(Vec2(13, 12));

    // Create random data
//    for(int i=0; i<31; i++) {
//        kdtree->vecList.push_back(Vec2(arc4random() % 100 + 1, arc4random() % 100 + 1));
//    }
    
    // Building of tree
    kdtree->build(kdtree->vecList, tree);
    
    // Insert new data
    Vec2 newData = Vec2(8, 6);
    kdtree->insert(tree, newData);
    
    // Delete a node
    kdtree->deleteNode(tree, Vec2(11, 3));
    
    // Draw Point
    drawNode = DrawNode::create();
    line = DrawNode::create();
    this->drawPoint(tree);
    
    this->addChild(line, 0);
    this->addChild(drawNode, 1);
    
    
    return true;
}

void MainVisual::drawPoint(KDNode* tree, KDNode* parent)
{
    if(tree == NULL) {
        return;
    }
    else {
        int d = tree->depth + 1;
        
        // Set point
        if(parent == NULL) {
            tree->point.x = winSize.width / 2;
            tree->point.y = winSize.height - 60;
        }
        else {
            tree->point.y = parent->point.y - 140;
            if(tree == parent->left) {
                tree->point.x = parent->point.x - 1940 / pow(d, 2.2);
            } else if(tree == parent->right) {
                tree->point.x = parent->point.x + 1940 / pow(d, 2.2);
            }
            
            // Draw line
            line->drawSegment(parent->point, tree->point, 1, Color4F::WHITE);
        }
        
        Color4F color = (d%2 == 1) ? Color4F::BLUE : Color4F::RED;
        drawNode->drawDot(tree->point, 8, color);
        
        text = Label::createWithSystemFont(
            StringUtils::format("(%i, %i)", (int)tree->vec2.x, (int)tree->vec2.y),
            "Arial",
            26
        );
        text->setPosition(Vec2(tree->point.x+60, tree->point.y));
        this->addChild(text, 2);
        
        this->drawPoint(tree->left, tree);
        this->drawPoint(tree->right, tree);
    }
}
