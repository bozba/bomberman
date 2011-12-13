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
    enum FieldType {BLANK,PLAYER_ONE,PLAYER_TWO,PLAYER_THREE,PLAYER_FOUR,BOMB,DWALL,NDWALL,PU_PB,PU_PSOD};

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



#endif
