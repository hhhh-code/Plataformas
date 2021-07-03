class Background : public Object
{
private:
    /* data */
public:
    Background(/* args */);
    ~Background();
    const void action();
};

Background::Background(/* args */)
{
    this->set_sprite("background");
    this->depth = 159;
}

Background::~Background()
{
    
}

const void Background::action(){
    stretch_sprite(lienzo, this->sprite, this->x, this->y, SCREEN_W, SCREEN_H);
}
