#include "Component.hpp"

void Scene::Attach(Component *observer) 
{
    list_observers_.push_back(observer);
}
void Scene::Detach(Component *observer) 
{
    list_observers_.remove(observer);
}
void Scene::Notify() 
{
    std::list<Component *>::iterator iterator = list_observers_.begin();
    while (iterator != list_observers_.end()) {
      (*iterator)->RecieveMessage(message_);
      ++iterator;
    }
}
void Scene::CreateMessage(MESSAGES message) 
{
    this->message_ = message;
    Notify();
}