/* Only a concept of a class.*/

#pragma once
#include <memory>
#include <assert.h>
#include <SFML/Graphics.hpp>

class SceneNode : public sf::Sprite {

public:
    typedef std::shared_ptr<SceneNode> Ptr;

    SceneNode ();
    
    void attachChild (Ptr child);
    SceneNode::Ptr detachChild (const SceneNode& node);


    virtual void update (sf::Time dt);
    virtual void updateCurrent (sf::Time dt);
    virtual void draw (sf::RenderTarget& target)const;
    virtual void drawCurrent (sf::RenderTarget& target) const;

protected:
    std::vector<Ptr> mChildren;
    SceneNode* mParent;
};