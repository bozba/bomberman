#include <cmath>
#include <vector>


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
	void setCoordinate(Coordiante& c_){
		c=c_;
	}
};


class Explosion: public Object{
	unsigned int timer;
	public:
	Explosion(Coordiante& c_,unsigned int t=3):c(c_),timer(t){}
	Data enofexpl(Map& m);
	bool tick(){
		timer--;
		return timer<=0;	
	}
};

Data Explosion::endofexpl(Map& m){
	
}

class Player: public Creature{
	unsigned int number_of_bombs;
	unsigned int size_of_detonation;
	public:
		Player(Coordinate& c_,std::string n,int pid,int nob=1,int sod=1):Creature(c_,n,pid),number_of_bombs(nob),size_of_detonation(sod){}
		Player(Coordinate& c_,nt pid,int nob=1,int sod=1):Object(c_),player_id(pid),number_of_bombs(nob),size_of_detonation(sod){}
		int getSOD(){
			return size_of_detonation;
		}
		void setSOD(unsigned int i){
			if(i<1){
				size_of_detonation=1;
			}
			else if(i>10){
				size_of_detonation=10;
			}
			else{
				size_of_detonation=i;
			}
		}
};

class Bomb: public Object{
	unsigned int size_of_detonation;
	unsigned int timer;
	Data powerupmaker(Map& m,vector<Data>& ret,const Coordinate& c);
	bool expl(Map& m,vector<Data>& ret,const Coordinate& tc,vector<Object>& ov);
	public:
		Bomb(Coordinate& c_,unsigned int sod,unsigned int timer=5):Object(c_),size_of_detonation(sod){}
		bool reducetime();
		vector<Data> kababoom(Map& m,vector<Object>& ov);
};

Data Bomb::powerupmaker(Map& m,const Coordinate& c){
	srand(time(NULL)); //lehet majd ki kell rakni a mainbe, vagy valahova, hogy minden rand elött fusson le
	int rnd=rand()%10+1;
	if(rnd==4){
		rnd=rand()%2; //most egyelőre scak két powerup van, de lehet itt is olyan, hogy több esélye van ennek, mint annak...
		if(rnd==0){
			m.setfieldtype(FieldType.PU_PB,c);
			return Data(Event.B_POWUP_APP,c);
		}
		else{
			m.setfieldtype(FieldType.PU_PSOD,c);
			return Data(Event.SOD_POWUP_APP,c);
		}
	}
	return Data(Event.WALL_DES,c);
}

//megnezi, hogy az adott koordinataju mezo felrobbanthato-e es terjedhet-e tovabba  robbanas, true ha igen, false ha nem..
bool Bomb::expl(Map& m,vector<Data>& ret,const Coordinate& tc,Event ex,vector<Object>& ov){
	if(m.containspoint(tc)){
		if(!m.walkable(tc)){
			if(m.getfieldtype(tc)==FieldType.DWALL){
				//ret.push_back(Data(Event.WALL_DES,tc));
				ret.push_back(powerupmaker(m,tc));
				//m.setfieldtype(FieldType.EXPL,tc); ... ezt még meg kell csinálni objektumként, hogy kezelje :S
				return false;
			}
			else if(m.getfieldtype(tc)==FieldType.NDWALL){
				return false;
			}
			else{
				int pid=0;
				switch(m.getfieldtype(tc)){
					case FieldType.PLAYER_ONE:pid=1;break;
					case FieldType.PLAYER_TWO:pid=2;break;
					case FieldType.PLAYER_THREE:pid=3;break;
					case FieldType.PLAYER_FOUR:pid=4;break;
					default:break;
				}
				if(pid!=0){
					ret.push_back(Data(ex,tc));
					ret.push_back(Data(Event.PLAYER_DIE,tc,pid));
					//m.setfieldtype(FieldType.EXPL,tc); 
				}
			}
		}
		else{
			if(m.getfieldtype(tc)==PU_PB || m.getfieldtype(tc)==PU_PSOD){
				ret.push_back(Data(Event.BEC_BLANK,tc));
				//m.setfieldtype(FieldType.EXPL,tc);
			}
		}
	}
	else{
		return false;
	}
	return true;
}

bool Bomb::reducetime(){
	timer--;
	return timer<=0;
}

//bomba felrobbanasakor torteno eveneteket szabja meg 
vector<Data> Bomb::kababoom(Map& m,vector<Object>& ov){ //kezdetleges, lehet madj rajta finomítani, ha van ötlet, pl szálakkal, és akkor nincs csúszás, vagy hasonló
	vector<Data> ret;
	ret.push_back(Data(Event.EXPL_CENTER,*c));
	for(int i=1;i<=4;i++){
		for(int j=1;j<=size_of_detonation;j++){
		Coordinate tc=(*this.c);
			if(i%2==0){
				tc.increasex(pow(1,i-3); //ha i 2 akkor balra, ha 4 akkor jobbra nézi
				if(!expl(m,ret,tc,Event.EXPL_HOR)){
					break;
				}
			}
			else{ //fel es lefele vizsgalata
				tc.increasy(1,i-2); //ha i 1 akkor felfele, ha 3 akkor lefele
				if(!expl(m,ret,tc,Event.EXPL_VER){
					break;
				}
			}
		}
	}
	return ret;
}



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
