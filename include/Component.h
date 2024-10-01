#include <Messages.h>
#include <list>

#ifndef COMPONENT_H_
#define COMPONENT_H_

class Scene;

class Component {
public:
    Component(Scene &subject); 
    virtual void Start(){};
    virtual void Update(){};
    void RecieveMessage(const MESSAGES &enumerator);
private:
    void Disable();
    void Enable();
    
    Scene &scene_;
    static int static_number_;
    int number_;
};

class Scene {
 public:
  virtual ~Scene(){};
  void Attach(Component *observer);
  void Detach(Component *observer);
  void CreateMessage(MESSAGES message);
  void Notify();

  std::list<Component*> list_observers_;
  MESSAGES message_; 
  static int static_number_;
};

#endif