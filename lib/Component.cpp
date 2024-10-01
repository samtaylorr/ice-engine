#include "Component.h"

Component::Component(Scene &subject) : scene_(subject)
{
    this->Enable();
}

void Component::Disable() {
    this->scene_.Detach(this);
}

void Component::Enable() {
    this->scene_.Attach(this);
};

void Component::RecieveMessage(const MESSAGES &enumerator)
{
    switch(enumerator)
    {
        case SCENE_START:
            this->Start();
            break;
        case SCENE_UPDATE:
            this->Update();
            break;
    }
}