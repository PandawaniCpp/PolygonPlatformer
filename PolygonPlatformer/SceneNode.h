#pragma once
#include <memory>
#include <assert.h>
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

class SceneNode : public sf::Sprite {

public:
    typedef std::shared_ptr<SceneNode> Ptr;

    SceneNode (b2World* world = nullptr);
    
    void attachChild (Ptr child);
    SceneNode::Ptr detachChild (const SceneNode& node);


    virtual void update (sf::Time dt,b2World* world=nullptr);
    virtual void updateCurrent (sf::Time dt, b2World* world = nullptr);
    virtual void draw (sf::RenderTarget& target)const;
    virtual void drawCurrent (sf::RenderTarget& target) const;
    b2Body* myBody;
protected:
    std::vector<Ptr> mChildren;
    SceneNode* mParent;
};