#pragma once

#include <Godot.hpp>
#include <Area2D.hpp>
#include <PhysicsBody2D.hpp>

namespace godot
{

class Bullet : public Area2D
{
    GODOT_CLASS(Bullet, Area2D)

public:
    static void _register_methods();

    Bullet();
    ~Bullet();

    void _init();
    void _ready();

    void _process(float delta);

    void _on_body_entered(PhysicsBody2D* body);
    void _on_VisibilityNotifier2D_screen_exited();

    int64_t direction;

private:
    const unsigned int SPEED = 1500;
    const unsigned int DAMAGE = 15;
};

}
