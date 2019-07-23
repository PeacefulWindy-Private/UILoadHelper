#pragma once

#include<UIVec.hpp>
#include<string>
#include<map>
#include"UIObject.hpp"

namespace PW
{
    enum UIWindowProperty
    {
        UIWindow_Width,
        UIWindow_Height,
        UIWindow_Title,
        UIWindow_RenderWidth,
        UIWindow_RenderHeight,
    };

    class UIWindow:public UIObject
    {
    public:
        UIWindow(void *context);
        virtual ~UIWindow(){}

    public:
        void loadFromMap(std::map<std::string,std::string> &map);

    public:
        void setWindowSize(Vec2 value);
        void setWindowTitle(std::string value);
        void setWindowRenderRect(Vec2 value);

    private:
        static void initializeKeys(std::map<std::string, UIWindowProperty>&);

    private:
        void * mContext=nullptr;
        static std::map<std::string,UIWindowProperty> mKeys;
    };

    inline UIWindow::UIWindow(void *context)
    {
        this->mContext=context;
        if(this->mKeys.empty())
        {
            UIWindow::initializeKeys(UIWindow::mKeys);
        }
    }

    inline void UIWindow::loadFromMap(std::map<std::string, std::string> &map)
    {
        Vec2 size(0.0f,0.0f);
        Vec2 renderSize(0.0f,0.0f);
        for (auto it=map.begin();it!=map.end();++it)
        {
            auto iter=this->mKeys.find(it->first);
            if(iter==this->mKeys.end())
                continue;

            switch(iter->second)
            {
            case UIWindow_Width:
                size.setX(static_cast<float>(atoi(it->second.c_str())));
                break;
            case UIWindow_Height:
                size.setY(static_cast<float>(atof(it->second.c_str())));
                break;
            case UIWindow_Title:
                this->setWindowTitle(it->second);
                break;
            case UIWindow_RenderWidth:
                renderSize.setX(static_cast<float>(atoi(it->second.c_str())));
                break;
            case UIWindow_RenderHeight:
                renderSize.setY(static_cast<float>(atof(it->second.c_str())));
                break;
            }
        }
        this->setWindowSize(size);
        this->setWindowRenderRect(size);
    }

    inline void UIWindow::initializeKeys(std::map<std::string,UIWindowProperty> &keys)
    {
        keys.insert(std::pair<std::string,UIWindowProperty>("width",UIWindow_Width));
        keys.insert(std::pair<std::string,UIWindowProperty>("height",UIWindow_Height));
        keys.insert(std::pair<std::string,UIWindowProperty>("title",UIWindow_Title));
        keys.insert(std::pair<std::string,UIWindowProperty>("renderWidth",UIWindow_RenderWidth));
        keys.insert(std::pair<std::string,UIWindowProperty>("renderHeight",UIWindow_RenderHeight));
    }
}
