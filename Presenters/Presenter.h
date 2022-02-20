#pragma once

class Presenter
{
public:
    virtual void present() const = 0;
    virtual ~Presenter() = default;
};
