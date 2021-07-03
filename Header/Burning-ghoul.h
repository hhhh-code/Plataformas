class Burning_ghoul: public Object
{
private:
    float grabity;
public:
    Burning_ghoul(/* args */);
    ~Burning_ghoul();
    const void action();
    void collision();
};

Burning_ghoul::Burning_ghoul(/* args */)
{
    this->set_sprite("burning-ghoul");
    this->w = 47;
    this->h = 47;
    this->fps = 10;
    this->grabity = 0;
}

Burning_ghoul::~Burning_ghoul()
{
}

const void Burning_ghoul::action(){
    this->animated(0);
    collision();
	y+=grabity;
}

void Burning_ghoul::collision(){
	
	for (list<Object *>::iterator it = instancias.begin(); it != instancias.end(); it++)
	{
		Object* obj = *it; 
		if(rect_coll(obj) and this->id != obj->id)
		{
			grabity = 0;	
			break;		
		}else
			grabity = 1;
	}
	
}
