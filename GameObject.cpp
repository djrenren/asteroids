#include "GameObject.h"

GameObject::GameObject(shared_ptr<Transform> t, Model* m, string texture) : transform(t), model(m), textureFile(texture)
{
	rigidBody = RigidBody{ {0,0,0}, {0,0,0}, 1 };
	collider = Collider::Colliderless;
}

GameObject::GameObject(shared_ptr<Transform> t, Model * m, string texture, RigidBody & r): transform(t), model(m), textureFile(texture), rigidBody(r)
{
	collider = Collider::Colliderless;
}

GameObject::GameObject(shared_ptr<Transform> t, Model * m, string texture, RigidBody & r, Collider c) : 
	transform(t), model(m), textureFile(texture), rigidBody(r), collider(c)
{

}

GameObject::GameObject()
{
}
