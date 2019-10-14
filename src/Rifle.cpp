#include "Rifle.h"
#include <Timer.hpp>
#include <Input.hpp>
#include <ResourceLoader.hpp>
#include "Bullet.h"

using namespace godot;

void Rifle::_register_methods()
{
    register_method("_process", &Rifle::_process, GODOT_METHOD_RPC_MODE_DISABLED);
    register_method("_ready", &Rifle::_ready, GODOT_METHOD_RPC_MODE_DISABLED);
    register_method("_init", &Rifle::_init, GODOT_METHOD_RPC_MODE_DISABLED);
    register_method("_on_Timer_timeout", &Rifle::_on_Timer_timeout, GODOT_METHOD_RPC_MODE_DISABLED);
    register_method("_shoot", &Rifle::_shoot, GODOT_METHOD_RPC_MODE_SYNC);
}

Rifle::Rifle()
{

}

Rifle::~Rifle()
{

}

void Rifle::_init()
{
    ResourceLoader* resourceLoader = ResourceLoader::get_singleton();
    BulletScene = resourceLoader->load("res://weapons/bullet/Bullet.tscn");
}

void Rifle::_ready()
{
    // NOTE : This is already connected in the editor so this is unnecessary
    //static_cast<Timer*>(get_node("Timer"))->connect("timeout", this, "_on_Timer_timeout");
}

void Rifle::_process(float delta)
{
    if(is_network_master())
    {
        Input* input = Input::get_singleton();
        if(input->is_action_pressed("shoot") &&
           static_cast<Timer*>(get_node("Timer"))->is_stopped())
        {
            rpc("_shoot");
            static_cast<Timer*>(get_node("Timer"))->start();
        }
    }
}

void Rifle::_on_Timer_timeout()
{
    static_cast<Timer*>(get_node("Timer"))->stop();
}

void Rifle::_shoot()
{
    godot::Bullet* bullet = static_cast<godot::Bullet*>(BulletScene->instance());
    add_child(bullet);
    bullet->set_global_position(get_global_position());
    int64_t direction = is_flipped_h() ? -1 : 1;
    bullet->set("direction", direction);
}
