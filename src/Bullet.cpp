#include "Bullet.h"

using namespace godot;

void Bullet::_register_methods()
{
    register_method("_process", &Bullet::_process, GODOT_METHOD_RPC_MODE_DISABLED);
    register_method("_ready", &Bullet::_ready, GODOT_METHOD_RPC_MODE_DISABLED);
    register_method("_init", &Bullet::_init, GODOT_METHOD_RPC_MODE_DISABLED);
    register_method("_on_body_entered", &Bullet::_on_body_entered, GODOT_METHOD_RPC_MODE_DISABLED);
    register_method("_on_VisibilityNotifier2D_screen_exited", &Bullet::_on_VisibilityNotifier2D_screen_exited, GODOT_METHOD_RPC_MODE_DISABLED);
    register_property<Bullet, int64_t>("direction", &Bullet::direction, 1, GODOT_METHOD_RPC_MODE_SYNC);
}

Bullet::Bullet()
{

}

Bullet::~Bullet()
{

}

void Bullet::_init()
{
    direction = 1;
}

void Bullet::_ready()
{
    set_as_toplevel(true);

    // NOTE : This is already connected in the editor so this is unnecessary
    //connect("body_entered", this, "_on_body_entered");
}

void Bullet::_process(float delta)
{
    Vector2 position = get_position();
    position.x += direction * SPEED * delta;
    set_position(position);
}

void Bullet::_on_body_entered(PhysicsBody2D* body)
{
    if(body->is_a_parent_of(this))
    {
        return;
    }

    if(!body->is_in_group("players"))
    {
        return;
    }

    body->call("damage", DAMAGE);
    queue_free();
}

void Bullet::_on_VisibilityNotifier2D_screen_exited()
{
    queue_free();
}
