enum
{
	WALK = 0,
	JUMP,
	DOWN
};

class Personaje : public Object
{
public:
	//variables
	int state;
	int dir;
	float vel;
	float grabity;
	int old_dir;
	bool coll;
	int old_x;
	int old_y;
	//funciones
	Personaje();
	~Personaje();
	const void action();
	void walk();
	void jump();
	void collision();
};

Personaje::Personaje()
{
	this->y = 150;
	this->x = 80;
	this->fps = 3;
	this->set_sprite("characters_left");
	this->w = 64;
	this->h = 64;
	this->setCollision(64, 64, 0, 0);
	this->state = WALK;
	this->dir = 0;
	this->vel = 1;
	grabity = 0;
	this->dir = 0;
	this->old_dir = 0;
	this->coll = false;
}

const void Personaje::action()
{
	old_x = this->x;
	old_y = this->y;

	switch (state)
	{
	case WALK:
		this->walk();
		break;
	case JUMP:
	case DOWN:
		this->walk();
		break;
	}
	animated(dir);
	draw_text(lienzo, 0, 0, 0x00000, (to_string(dir) + to_string(old_dir) + to_string(state)).c_str());
}

void Personaje::walk()
{
	int mov_h = key[KEY_A] - key[KEY_D];
	fps = 20;

	if (mov_h == -1)
	{
		x -= vel;
		if (state != JUMP)
			dir = 1;
	}
	else if (mov_h == 1)
	{
		x += vel;
		if (state != JUMP)
			dir = 0;
	}

	if (!mov_h)
	{
		//dir == 0 ? dir = 2 : dir = 1;
	}

	if (grabity > 0)
		dir = 4;

	if (grabity > 0 and this->index == 3)
		this->fps = 0;

	jump();
	collision();
	y += grabity;
}

Personaje::~Personaje()
{
}

void Personaje::jump()
{
	if (key[KEY_SPACE])
	{
		grabity = -2;
		state = JUMP;
		this->dir = 4;
		this->index = 0;
	}

	if (grabity > 0)
		grabity -= 0.02;
	else if (grabity < 0)
		grabity += 0.02;

	if (grabity > -0.02f and grabity < 0.02f)
	{
		state = WALK;
	}
}

void Personaje::collision()
{

	if (dir != 4)
		this->old_dir = this->dir;

	for (list<Object *>::iterator it = instancias.begin(); it != instancias.end(); it++)
	{
		Object *obj = *it;

		if (rect_coll(obj))
		{

			if (this->iscollH() and y + collH > obj->y)
			{
				this->x = old_x;
				this->coll = true;
			}

			if (this->iscollV() and this->state == WALK)
			{
				this->coll = true;
				this->y = old_y;
				rect_coll(obj);
				if (this->iscollV())
					grabity = 0;
			}
		}
		else if (!coll and this->state == WALK)
		{
			grabity = 1;
		}
	}
	this->coll = false;
}
