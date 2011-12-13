
class Coordinate{
    private:
    unsigned int x;
    unsigned int y;
    friend bool operator==(Coordinate &a,Coordinate &b);
    friend ostream &operator<<(ostream &out,Coordinate &c);
    public:
    Coordinate(unsigned int X,unsigned int Y){
        x=X;
        y=Y;
    }
	void increasex(unsigned int i=1){
		x+=i;
	}
	void decreasex(unsigned int i=1){
		x-=i;
	}
	void increasey(unsigned int i=1){
		y+=i;
	}
	void decreasey(unsigned int i=1){
		y-=i;
	}
};

bool operator==(Coordinate &a,Coordinate &b){
    return(a.x==b.x && a.y==b.y);
}

ostream &operator<<(ostream &out,Coordinate &c){
    out<<'('<<c.x<<';'<<c.y<<')';
    return out;
}

class Object{
	Coordinate* c;
	public:
	Object(Coordinate& c_):c(c_){}
	Coordinate getCoordiante(){
		return (*c);
	}
	void setCoordinate(Coordiante* c_){
		c=c_;
	}
};

class Player: public Creature{
	unsigned int number_of_bombs;
	unsigned int size_of_detonation;
	public:
		Player(Coordinate& c_,std::string n,int pid,int nob=1,int sod=1):Creature(c_,n,pid),number_of_bombs(nob),size_of_detonation(sod){}
		Player(Coordinate& c_,nt pid,int nob=1,int sod=1):Object(c_),player_id(pid),number_of_bombs(nob),size_of_detonation(sod){}

};

class Bomb: public Object{
	unsigned int size_of_detonation;
	unsigned int timer;
	public:
		Bomb(Coordinate& c_,unsigned int sod,unsigned int timer=3):Object(c_),size_of_detonation(sod){}
		int reducetime();
};

class Creature: public Object{
	std::string name;
	unsigned int player_id;
	public:
		enum movedirection {LEFT,RIGHT,UP,DOWN,STAND};
		movedirection md;
		Creature(Coordinate& c_,std::string n,int pid):Object(c_),name(n),player_id(pid){
			md=movedirection.STAND;
		}
		void setName(string nm);
		int getid();
};

int Creature::getid(){
	return player_id;
}

void Creature::setName(string nm){
	name=nm;
}
