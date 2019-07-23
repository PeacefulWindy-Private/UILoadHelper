#pragma once
#include<map>
#include<string>
#include"UIWindow.h"

namespace PW
{
    enum UIFaceoryProduct
    {
        UI_WINDOW,
    };

    class UIFactory
    {
    public:
        UIFactory(void * context=nullptr);

    public:
        void create(std::string,std::map<std::string,std::string>&);

    private:
        static void initializeProductList(std::map<std::string,UIFaceoryProduct>&);
        static std::map<std::string,UIFaceoryProduct> sProductList;
        void * mContext=nullptr;
    };

    std::map<std::string,UIFaceoryProduct> UIFactory::sProductList;

    inline UIFactory::UIFactory(void * context)
    {
        if(this->sProductList.empty())
        {
            UIFactory::initializeProductList(UIFactory::sProductList);
        }

        this->mContext=context;
    }

    inline void UIFactory::create(std::string type,std::map<std::string,std::string>& map)
    {
        if(this->mContext==nullptr)
            return;

        auto it=UIFactory::sProductList.find(type);
        if(it==UIFactory::sProductList.end())
            return;

        UIObject * obj=nullptr;

        switch(it->second)
        {
        case UI_WINDOW:
            obj=new UIWindow(this->mContext);
            break;
        }
        obj->loadFromMap(map);
        delete obj;
        obj=nullptr;
    }

    inline void UIFactory::initializeProductList(std::map<std::string, UIFaceoryProduct> &list)
    {
        list.insert(std::pair<std::string,UIFaceoryProduct>("window",UI_WINDOW));
    }

}
