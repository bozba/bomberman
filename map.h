#ifindef _map_h_include
#define _map_h_include

#include <iostream>
#include <map>
#include <Coordinate>

class maptype{
	public:
	const int maxplayer;
	const string gametype; //lehetne int is...
	maptype(int maxplr=4,string gt="Normal"):maxplayer(mayplr),gametype(gt){}
};

class Map{
    map<Coordinate,FieldType> fields;
    unsigned int height;
    unsigned int width;
	maptype mt;
    public:
    enum FieldType {BLANK,PLAYER_ONE,PLAYER_TWO,PLAYER_THREE,PLAYER_FOUR,BOMB,DWALL,NDWALL,PU_PB,PU_PSOD,EXPL};

    Map(map<Coordinate,FieldType> f,int h,int w): fields(f), height(h), width(w){
    }

    Map(Map m){
        this.fields=m.fields;
        this.height=m.height;
        this.width=m.width;
    }

	Coordinate* player_coordinate(unsigned int& pid);

	bool containpoint(Coordinate& c){
		return (fields.find(c)!=null);
	}

	FieldType getfieldtype(Coordinate c){
		if(containpoint(c)){
			return fields.find(c)->second;
		}
		else{
			//lekezelés
		}
	}
	
	void setfieldtype(FieldType ft,Coordinate c){
		if(containpont(c)){
			fields.find(c)->second=ft;
		}
	}

	bool walkable(Coordinate& c){
		f(getfieldtype(c)==FieldType.BLANK || map.getfieldtype(c)==FieldType.PU_PB || map.getfieldtype(c)==PU_PSOD){
			return true;
		}
		return false;
	}
	

	void setplayer(Coordiante& c,Player* p);
};


Coordinate* Map::player_coordinate(unsigned int& pid){
	if(mt.maxplayer>=pid){
		switch(pid){
		case 1:{
			for(fields::iterator it = fields.begin();it != fields.end();it++){
				if(it->second==FieldType.PLAYER_ONE){
					return &(it->first);
				}
			}
		}
		case 2:{
			for(fields::iterator it = fields.begin();it != fields.end();it++){
				if(it->second==FieldType.PLAYER_TWO){
					return &(it->first);
				}
			}
		}
		case 3:{
			for(fields::iterator it = fields.begin();it != fields.end();it++){
				if(it->second==FieldType.PLAYER_THREE){
					return &(it->first);
				}
			}
		}
		case 4:{
			for(fields::iterator it = fields.begin();it != fields.end();it++){
				if(it->second==FieldType.PLAYER_FOUR){
					return &(it->first);
				}
			}
		}
		default:{ //nem lephet be szerintem...
			return null;
		}
		}
	}
	else{
		return null;
	}
}


//beallitja az adott mezore az adott idvel rendelekzo jatekost
void Map::setplayer(Coordiante& c,Player* p){
	switch(*p.getid()){
		case 1:fields.find(c)->second=FieldType.PLAYER_ONE;break;
		case 2:fields.find(c)->second=FieldType.PLAYER_TWO;break;
		case 3:fields.find(c)->second=FieldType.PLAYER_THREE;break;
		case 4:fields.find(c)->second=FieldType.PLAYER_FOUR;break;
		default:break;
	}
}



#endif
