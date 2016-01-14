#pragma once

class GameObject
{
public:

	GameObject();
	~GameObject();

	virtual void draw() = 0;
	virtual void update() = 0;
	virtual void clean() = 0;

private:


};
