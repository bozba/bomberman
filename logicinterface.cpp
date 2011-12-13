#include <vector>
#include <iostream>
#include <object.cpp>

class iLogic{
	Map map;
	int timer;
	vector<Player*> players;
	virtual std::string generate();
	vector<Object> objects;
	public:
		virtual vector<Data> processevent(int keycode[])=0; //ha event
		//jatekos mozgas (elinditas, lezaras)
		//bomba lerakas
		//power up felhasznalas
		//pause game
		//game settings
	//	vector<Object> virtual bombdetonation()=0;
		virtual vector<Data> event_update()=0; //egyebkent update palya
		//folyamatos mozgas(jatekos es szorny)
		//bomba robbanasig ido elteles allitasa
		//bomba robbanas
	
};


class Logic: public iLogic{
	vector<Data> moveleft(int pid);
	vector<Data> moveright(int pid);
	vector<Data> moveup(int pid);
	vector<Data> movedown(int pid);
	vector<Data> bombshit(int pid);
	vector<Data> spec_powerup_use(int pid);
	bool walkable(Coordinate& c,Player* p);
	public:
	Logic(Map m,unsigned int playernumber=1,int monsternumber=3,int time=0);
	vector<Data> processevent(int keycode[]);
	vector<Data> event_update();
};


Logic::Logic(Map m,unsigned int playernumber=1,int monsternumber=3,int time=0){
	map=m;
	timer=time;
	for(unsigned int i=1,i<=playernumber,i++){
		player.push_back(new Player(m.player_coordinate(i),i);
	}
}

vector<Data> Logic::moveleft(int pid){
	vector<Data> ret;
	Player* p=null;
	for(unsigned int i=0;i<players.size();i++){
		if(players[i].getid()==pid){
			p=players[i];
			break;
		}
	}
	if(p==null){
		// valami, ha elofordulhat, le kell kezelni majd
	}
	Coordinate tmp=p.getCoordiante();
	if(p.mt==Player::movedirection.STAND){ //akkor most nyomta le a gombot
		tmp.incrasex();
		if(map.cointainpoint(tmp)){ //ha letezik a mezo
			if(walkable(map.getfieldtype(tmp)){
				p.mt=Player::movedirection.LEFT;
				Data dt(
				ret.push_back(dt);
			}
		}
	}
}



vector<Data> Logic::proccessevent(int keycode[]){
	switch(keycode[0]){
		case 1:{ //1 helyére majd a megfelelő keycode... többinél hasonlóan
			return moveleft(keycode[1]);
		}
		case 2:{
			return moveup(keycode[1]);
		}
		case 3:{
			return moveright(keycode[1]);
		}
		case 4:{
			return movedown(keycode[1]);
		}
		case 5:{
			return bombshit(keycode[1]);
		}
		case 6:{
			return spec_powerup_use(keycode[1]);
		}
		default:{
			std::cout<<"h?!"<<std::endl;
		}
	}
}

