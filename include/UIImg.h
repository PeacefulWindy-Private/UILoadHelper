#pragma once
#include<UIVec.hpp>
#include<string>
#include<map>
#include"UIObject.hpp"
#include<cstdlib>

namespace PW
{
    enum UIImgProperty
    {
        UIImg_Src,
        UIImg_ImgX,
        UIImg_ImgY,
        UIImg_ImgWidth,
        UIImg_ImgHeight,
        UIImg_X,
        UIImg_Y,
        UIImg_Width,
        UIImg_Height
    };

    class UIImg:public UIObject
    {
    public:
        UIImg(void *context,void * scene);
        virtual ~UIImg();

    public:
        void loadFromMap(std::map<std::string,std::string> &map);

    private:
        void * create(std::string &path,Vec4 &rect);
        void setPosition(void * ptr,Vec2 pos);
        void setSize(void * ptr,Vec2 size);

        void add(void * context,void * ptr);

    private:
        static void initializeKeys(std::map<std::string, UIImgProperty>&);

    private:
        void * mContext=nullptr;
        void * mScene=nullptr;
        static std::map<std::string,UIImgProperty> mKeys;
    };

    inline UIImg::UIImg(void *context,void * scene)
    {
        this->mScene=scene;
        this->mContext=context;

        if(this->mKeys.empty())
        {
            UIImg::initializeKeys(UIImg::mKeys);
        }
    }

    inline UIImg::~UIImg(){}

    inline void UIImg::loadFromMap(std::map<std::string, std::string> &map)
    {
        Vec4 imgRect(0.0f,0.0f,0.0f,0.0f);
        Vec4 rect(0.0f,0.0f,0.0f,0.0f);
        std::string src="";

        for (auto it=map.begin();it!=map.end();++it)
        {
            auto iter=this->mKeys.find(it->first);
            if(iter==this->mKeys.end())
                continue;

            switch(iter->second)
            {
            case UIImg_Src:
                src=it->second;
                break;
            case UIImg_ImgX:
                imgRect.setX(static_cast<float>(std::atof(it->second.c_str())));
                break;
            case UIImg_ImgY:
                imgRect.setY(static_cast<float>(std::atof(it->second.c_str())));
                break;
            case UIImg_ImgWidth:
                imgRect.setZ(static_cast<float>(std::atof(it->second.c_str())));
                break;
            case UIImg_ImgHeight:
                imgRect.setW(static_cast<float>(std::atof(it->second.c_str())));
                break;
            case UIImg_X:
                rect.setX(static_cast<float>(std::atof(it->second.c_str())));
                break;
            case UIImg_Y:
                rect.setY(static_cast<float>(std::atof(it->second.c_str())));
                break;
            case UIImg_Width:
                rect.setZ(static_cast<float>(std::atof(it->second.c_str())));
                break;
            case UIImg_Height:
                rect.setW(static_cast<float>(std::atof(it->second.c_str())));
                break;
            }
        }
        if(src == "")
        {
            return;
        }

        auto ptr=this->create(src,imgRect);
        if(ptr==nullptr)
            return;

        this->setPosition(ptr,Vec2(rect.x(),rect.y()));
        this->setSize(ptr,Vec2(rect.z(),rect.w()));
        this->add(this->mScene,ptr);
    }

    inline void UIImg::initializeKeys(std::map<std::string,UIImgProperty> &keys)
    {
        keys.insert(std::pair<std::string,UIImgProperty>("src",UIImg_Src));
        keys.insert(std::pair<std::string,UIImgProperty>("imgX",UIImg_ImgX));
        keys.insert(std::pair<std::string,UIImgProperty>("imgY",UIImg_ImgY));
        keys.insert(std::pair<std::string,UIImgProperty>("imgWidth",UIImg_ImgWidth));
        keys.insert(std::pair<std::string,UIImgProperty>("imgHeight",UIImg_ImgHeight));
        keys.insert(std::pair<std::string,UIImgProperty>("x",UIImg_X));
        keys.insert(std::pair<std::string,UIImgProperty>("y",UIImg_Y));
        keys.insert(std::pair<std::string,UIImgProperty>("width",UIImg_Width));
        keys.insert(std::pair<std::string,UIImgProperty>("height",UIImg_Height));
    }
}
