#pragma once

#include<map>
#include<string>

namespace PW
{
    class UIObject
    {
    public:
        virtual ~UIObject(){}
    public:
        virtual void loadFromMap(std::map<std::string,std::string> &map)=0;
    };
}
