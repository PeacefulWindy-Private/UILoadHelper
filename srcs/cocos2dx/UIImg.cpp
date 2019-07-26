#include<UIImg.h>
#include<cocos2d.h>

namespace PW
{
    std::map<std::string,UIImgProperty> UIImg::mKeys;

    void * UIImg::create(std::string &path, PW::Vec4 &rect)
    {
        cocos2d::Sprite *sprite = nullptr;
        if(rect.z() == 0.0f || rect.w() == 0.0f)
        {
            sprite = cocos2d::Sprite::create(path);
        }
        else
        {
            sprite = cocos2d::Sprite::create(path,cocos2d::Rect(rect.x(),rect.y(),rect.z(),rect.w()));
        }
        return sprite;
    }

    void UIImg::setPosition(void *ptr, Vec2 pos)
    {
        auto sprite=static_cast<cocos2d::Sprite *>(ptr);
        sprite->setAnchorPoint(cocos2d::Vec2(0.0f,0.0f));
        sprite->setPosition(pos.x(),pos.y());
    }

    void UIImg::setSize(void *ptr, Vec2 size)
    {
        if(size.x() == 0.0f || size.y() == 0.0f)
            return;

        auto sprite=static_cast<cocos2d::Sprite *>(ptr);
        sprite->setScale(size.x(),size.y());
    }

    void UIImg::add(void * context, void *ptr)
    {
        auto p=static_cast<cocos2d::Scene *>(context);
        auto sprite=static_cast<cocos2d::Sprite *>(ptr);

        p->addChild(sprite);
    }
}


