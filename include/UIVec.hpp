#pragma once

namespace PW
{
    class Vec2
    {
    public:
        Vec2(float x,float y)
        {
            this->setX(x);
            this->setY(y);
        }

    public:
        float x()
        {
            return this->mX;
        }

        void setX(float value)
        {
            this->mX=value;
        }

        float y()
        {
            return this->mY;
        }

        void setY(float value)
        {
            this->mY=value;
        }

    private:
        float mX=0.0f,mY=0.0f;
    };
}
