#include<UIWindow.h>
#include<cocos2d.h>

namespace PW
{
    std::map<std::string,UIWindowProperty> UIWindow::mKeys;

    void UIWindow::setWindowSize(Vec2 value)
    {
        auto director=static_cast<cocos2d::Director *>(this->mContext);
        director->getOpenGLView()->setFrameSize(value.x(),value.y());
    }

    void UIWindow::setWindowTitle(std::string value)
    {
        /*
        auto director=static_cast<cocos2d::Director *>(this->mContext);
        director->getOpenGLView()->setViewName(value);
        */
    }

    void UIWindow::setWindowRenderRect(Vec2 value)
    {
        auto director=static_cast<cocos2d::Director *>(this->mContext);
        director->getOpenGLView()->setDesignResolutionSize(value.x(),value.y(),ResolutionPolicy::SHOW_ALL);
    }
}


