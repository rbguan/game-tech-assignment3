#pragma once

#include <Godot.hpp>
#include <Sprite.hpp>
#include <Ref.hpp>
#include <PackedScene.hpp>

namespace godot
{

class Rifle : public Sprite
{
    GODOT_CLASS(Rifle, Sprite)

public:
    static void _register_methods();

    Rifle();
    ~Rifle();

    void _init();
    void _ready();

    void _process(float delta);
    void _on_Timer_timeout();
    void _shoot();

private:
    Ref<PackedScene> BulletScene;
};

}
