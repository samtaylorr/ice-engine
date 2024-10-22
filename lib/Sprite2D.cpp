#include <Sprite2D.hpp>
#include <Settings.hpp>
#include <Input.hpp>
#include <iostream>

Sprite2D::Sprite2D(std::shared_ptr<LWindow> window, Scene &subject, const std::string &fileName) : Component(subject)
{
    sprite = new LTexture(window, subject, fileName);
}

Sprite2D::~Sprite2D()
{
    delete sprite;
}