class Block : public Object
{
private:
    /* data */
public:
    Block(/* args */);
    ~Block();
    const void action();
};

Block::Block(/* args */)
{
    this->id = "Block";
    this->set_sprite("block");
    this->w = 32;
    this->h = 32;
    this->depth = 2;
}

Block::~Block() 
{
}

const void Block::action(){
    this->draw();
}
