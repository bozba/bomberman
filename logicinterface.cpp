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
	Player getPlayer(int pid);
	Data checkstate(Player* p);
	Coordiante change(Coordinate c,movedirection md);
	vector<Data> setstate(Player* p,movedirection md,Event ev1,Event ev2);
	vector<Data> moveleft(int pid);
	vector<Data> moveright(int pid);
	vector<Data> moveup(int pid);
	vector<Data> movedown(int pid);
	vector<Data> bombshit(int pid);
	vector<Data> spec_powerup_use(int pid);
	bool walkable(Coordinate& c,Player* p);
	Data createData(int pid,movedirection md,Coordinate c,movedirection frommd);
	public:
	Logic(Map m,unsigned int playernumber=1,int monsternumber=3,int time=0);
	vector<Data> processevent(int keycode[]);
	vector<Data> event_update();
};


Logic::Logic(Map m,unsigned int playernumber,int monsternumber,int time){
	map=m;
	timer=time;
	for(unsigned int i=1,i<=playernumber,i++){
		player.push_back(new Player(m.player_coordinate(i),i);
	}
}

Player* Logic::getPlayer(int pid){
	for(unsigned int i=0;i<players.size();i++){
		if(players[i].getid()==pid){
			Player* p=players[i];
			return p;
		}
	}
	return null;
}

Coordinate Logic::change(Coordinate c,movedirection md){
	switch(md){
		case Player::movedirection.LEFT:{
			c.increasex();
			break;
		}
		case Player::movedirection.RIGHT: {
			c.decreasex();
			break;
		}
		case Player::movedirection.UP: {
			c.decreasey();
			break;
		}
		case Player::movedirection.DOWN: {
			c.increasey();
			break;
		}
		default:{
			break;
		}
	}
	return c;
}

vector<Data> Logic::setstate(Player* p,movedirection md,Event ev1,Event ev2){
	vector<Data> ret;
	Coordinate tmp=p.getCoordiante();
	if(p.mt==Player::movedirection.STAND){ //akkor most nyomta le a gombot
		tmp.change(tmp,md);
		if(map.cointainpoint(tmp)){ //ha letezik a mezo
			if(walkable(map.getfieldtype(tmp)){ //ha jarhato
				p.mt=Player::movedirection.LEFT;
				p.setCoordinate(tmp);
				Data dt(ev1,tmp,pid);
				ret.push_back(dt);
				return ret;
			}
		}
	}
	else if(p.mt==md){ //akkor msot kellett, hogy felengedje
		p.mt=Player::movedirection.STAND;
		Data dt(ev2,tmp,pid);
		ret.push_back(dt);
		return ret;
	}
	return ret;
}

vector<Data> Logic::moveleft(int pid){
	Player* p=getPlayer(pid);
	if(p==null){
		// valami, ha elofordulhat, le kell kezelni majd
	}
	return chackstate(p,movedirection.LEFT,Event.MLEFT,Event.SLEFT);
}

vector<Data> Logic::moveup(int pid){
	Player* p=getPlayer(pid);
	if(p==null){
		// valami, ha elofordulhat, le kell kezelni majd
	}
	return chackstate(p,movedirection.UP,Event.MUP,Event.SUP);
}

vector<Data> Logic::moveright(int pid){
	Player* p=getPlayer(pid);
	if(p==null){
		// valami, ha elofordulhat, le kell kezelni majd
	}
	return chackstate(p,movedirection.RIGHT,Event.MRIGHT,Event.SRIGHT);
}

vector<Data> Logic::movedown(int pid){
	Player* p=getPlayer(pid);
	if(p==null){
		// valami, ha elofordulhat, le kell kezelni majd
	}
	return chackstate(p,movedirection.DOWN,Event.MDOWN,Event.SDOWN);
}

vector<Data> Logic::bombshit(int pid){
	Player* p=getPlayer(pid);
	if(p==null){
		// valami, ha elofordulhat, le kell kezelni majd
	}
	Bomb b(p.getCoordinate(),p.getSOD(),
	objects.push_back(b);
	Data tmp(Event.BOMB,p.getCoordinate(),pid);
	vector<Data> ret;
	ret.push_back(tmp);
	return ret;
}

vector<Data> Logic::spec_powerup_use(int pid){
	//meg semmi, de e miatt kellett a vector<data>
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

Data Logic::createData(int pid,movedirection md,Coordinate c,movedirection frommd){
	if(frommd!=movedirection.STAND){
		if(md==movedirection.STAND){
			switch(frommd){
				case movedirection.LEFT: return Data(Event.SLEFT,c,pid);
				case movedirection.RIGHT: return Data(Event.SRIGHT,c,pid);
				case movedirection.UP: return Data(Event.SUP,c,pid);
				case movedirection.DOWN: return Data(Event.SDOWN,c,pid);
			}
		}
	}
	else{
		switch(md){
			case movedirection.LEFT: return Data(Event.MLEFT,c,pid);
			case movedirection.RIGHT: return Data(Event.MRIGHT,c,pid);
			case movedirection.UP: return Data(Event.MUP,c,pid);
			case movedirection.DOWN: return Data(Event.MDOWN,c,pid);
		}
	}
}

Data Logic::checkstate(Player* p){
	vector<Data> ret;
	movedirecton movedir=movedirection.STAND;
	if(p.mt!=Player.movedirection.Stand){
		Coordinate tmp=checkstate(p);
		if(map.containpoint(tmp)){
			if(!walkable(tmp)){
				movedir=p.mt;
				p.mt=Player::movedirection.STAND;
				tmp=p.getCoordinate();
			}
		}
		else{
			movedir=p.mt;
			p.mt=movedirection.STAND;
			tmp=p.getCoordiante();
		}
		p.setCoordiante(tmp);
		return createData(p.getid(),p.mt,tmp,movedir);
	}
}

vector<Data> Logic::event_update(){
	vector<Data> ret;
	for(int i=0;i<players.size();i++){
		ret.push_back(checkstate(players[i]));
	}
	for(int i=0;i<objects.size();i++){
		///meg kell még írni
	}
}

