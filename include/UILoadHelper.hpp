#pragma once

#include<lua5.3/lua.hpp>
#include<string>
#include<map>
#include"UIFactory.hpp"

namespace PW
{
    class UILoadHelper
    {
    public:
        UILoadHelper();
        virtual ~UILoadHelper();
    public:
        bool loadUIFromLuaFile(std::string path);

        void run(void * window=nullptr);
    private:
        lua_State * L=nullptr;
    };

    inline UILoadHelper::UILoadHelper()
    {
        L=luaL_newstate();
        luaL_openlibs(L);
    }

    inline UILoadHelper::~UILoadHelper()
    {
        if(L)
        {
            lua_close(L);
        }
    }

    inline bool UILoadHelper::loadUIFromLuaFile(std::string path)
    {
        if(luaL_dofile(L,path.c_str())==1)
        {
            return false;
        }

        return true;
    }

    inline void UILoadHelper::run(void *context)
    {
        if(context==nullptr)
        {
            return;
        }

        lua_getglobal(L,"initialize");
        if(!lua_istable(L,-1))
        {
            return;
        }
        UIFactory factory(context);

        auto index=lua_gettop(L);
        lua_pushnil(L);
        while(lua_next(L,index)!=0)
        {
            if(!lua_istable(L,-1))
            {
                continue;
            }
            auto index=lua_gettop(L);
            lua_pushnil(L);
            std::map<std::string,std::string> map;
            while(lua_next(L,index))
            {
                map.insert(std::pair<std::string,std::string>(
                               lua_tostring(L,-2),
                               lua_tostring(L,-1))
                           );
                lua_pop(L,1);
            }
            auto it=map.find("type");
            if(it!=map.end())
            {
                factory.create(it->second,map);
            }

            lua_pop(L,1);
        }
        lua_pop(L,1);
    }
}
