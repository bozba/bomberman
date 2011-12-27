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
//	bool walkable(Coordinate& c,Player* p);
	Data createData(int pid,movedirection md,Coordinate c,movedirection frommd);
	vector<Data> endofexpl(int index);
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


//getPlayer: visszaadja a pid-edik playert ..
Player* Logic::getPlayer(int pid){
	for(unsigned int i=0;i<players.size();i++){
		if(players[i].getid()==pid){
			Player* p=players[i];
			return p;
		}
	}
	return null;
}

//annak a függvényében, hogy milyen mozgásirány van változtatja a megadott koordinátát (egy mezővel a megadott irányba) és visszaadja az új koordinátát
Coordinate Logic::change(Coordinate c,movedirection md){
	switch(md){
		case movedirection.LEFT:{
			c.increasex();
			break;
		}
		case movedirection.RIGHT: {
			c.decreasex();
			break;
		}
		case movedirection.UP: {
			c.decreasey();
			break;
		}
		case movedirection.DOWN: {
			c.increasey();
			break;
		}
		default:{
			break;
		}
	}
	return c;
}

//beállítja az adott játékos mozgását
vector<Data> Logic::setstate(Player* p,movedirection md,Event ev1,Event ev2){
	vector<Data> ret; //az eventek amik majd a guinak kellenek
	Coordinate tmp=p.getCoordinate(); //a jatekos pozicioja
	if(p.mt==movedirection.STAND){ //akkor most nyomta le a gombot
		tmp.change(tmp,md); //jatekos koordinatajabol a mozgasiranyanak megfeleloen megvaltoztatott koordinatat ad vissza
		if(map.cointainpoint(tmp)){ //ha ez letezo mezo
			if(map.walkable(tmp){ //ha jarhato
				p.mt=md; //a jatekos mozgasiranya a megfelelo lesz amig fel nem engedi a gombot
				map.setfieldtype(FieldType.BLANK,p.getCoordinate()); //az a mezo amit elhagy ures lesz (kiveve ha lerakott egy bombat...:S ah, meg kell oldani..)
				p.setCoordinate(tmp); //jatekos pozicioja az uj koordinata lesz
				map.setplayer(tmp,pid); //lasd map.h
				Data dt(ev1,tmp,pid); //a guinak kuldendo valtozast hozza létre
				ret.push_back(dt); 
				return ret;
			}
		}
	}
	else if(p.mt==md){ //akkor msot kellett, hogy felengedje
		p.mt=Player::movedirection.STAND; //felengedte igy megall a karaktere
		Data dt(ev2,tmp,pid);
		ret.push_back(dt);
		return ret;
	}
	return ret;
}

//balramozgas eseten meghivando
vector<Data> Logic::moveleft(int pid){
	Player* p=getPlayer(pid);
	if(p==null){
		// valami, ha elofordulhat, le kell kezelni majd
	}
	return setstate(p,movedirection.LEFT,Event.MLEFT,Event.SLEFT);
}

//fel mozgas eseten
vector<Data> Logic::moveup(int pid){
	Player* p=getPlayer(pid);
	if(p==null){
		// valami, ha elofordulhat, le kell kezelni majd
	}
	return setstate(p,movedirection.UP,Event.MUP,Event.SUP);
}

//jobbra mozgas
vector<Data> Logic::moveright(int pid){
	Player* p=getPlayer(pid);
	if(p==null){
		// valami, ha elofordulhat, le kell kezelni majd
	}
	return setstate(p,movedirection.RIGHT,Event.MRIGHT,Event.SRIGHT);
}

//balra mozgas
vector<Data> Logic::movedown(int pid){
	Player* p=getPlayer(pid);
	if(p==null){
		// valami, ha elofordulhat, le kell kezelni majd
	}
	return setstate(p,movedirection.DOWN,Event.MDOWN,Event.SDOWN);
}

//bomba lerakasa
vector<Data> Logic::bombshit(int pid){
	Player* p=getPlayer(pid);
	if(p==null){
		// valami, ha elofordulhat, le kell kezelni majd
	}
	Bomb b(p.getCoordinate(),p.getSOD());
	objects.push_back(b);
	Data tmp(Event.BOMB,p.getCoordinate(),pid);
	vector<Data> ret;
	ret.push_back(tmp);
	return ret;
}


//nem tudom, mik lesznek, madj a vegen lehet vele szorakozni ha az alap mar mukszik
vector<Data> Logic::spec_powerup_use(int pid){
	//meg semmi, de e miatt kellett a vector<data>
}

//ha billentyu event torteneik, elnyomas vagy felengedes, akkor ez hivodik meg
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
			std::cout<<"h?!"<<std::endl; //ide nem lephet be
		}
	}
}


//a guinak visszakuldendo event.. lehet majd meg egyszerusiteni...
Data Logic::createData(int pid,movedirection md,Coordinate c,movedirection frommd){
	if(frommd!=movedirection.STAND){ //ha a frommd stand azt akkor küldöm ha mozgasban van a karakter, szóval ha nem stand akkor az azt jelenti, hgoy megallt
		if(md==movedirection.STAND){ //de azert megnezem, hatha valamit elbasztam ...
			switch(frommd){ //nem biztos, hogy szükség van erre , sőt esélyes, hogy felesleges..
				case movedirection.LEFT: return Data(Event.SLEFT,c,pid);
				case movedirection.RIGHT: return Data(Event.SRIGHT,c,pid);
				case movedirection.UP: return Data(Event.SUP,c,pid);
				case movedirection.DOWN: return Data(Event.SDOWN,c,pid);
			}
		}
	}
	else{ //tehat mozgasban van
		switch(md){
			case movedirection.LEFT: return Data(Event.MLEFT,c,pid);
			case movedirection.RIGHT: return Data(Event.MRIGHT,c,pid);
			case movedirection.UP: return Data(Event.MUP,c,pid);
			case movedirection.DOWN: return Data(Event.MDOWN,c,pid);
		}
	}
}


//a logika minden egyes time ticknel ellenorzi, hogy mozognak-e a karakterek, es ha igen akkor mozgatja oket egy mezot (nyilvan a player lenyomva tartja a gombot)
Data Logic::checkstate(Player* p){
	vector<Data> ret;
	movedirecton movedir=movedirection.STAND;
	if(p.mt!=movedir){ //ha nem all, vagyis a player nyomva tartja a gombot
		Coordinate tmp=change(p.getCoordinate(),p.mt);
		if(map.containpoint(tmp)){ //ugyanaz mint a gombeventes fv-ben
			if(!map.walkable(tmp)){
				movedir=p.mt;
				p.mt=movedirection.STAND; //nem jarhato, a playert megallitja a regi mezon
				tmp=p.getCoordinate();
			}
			else{
				p.setCoordiante(tmp); //mozog, playert atrakja az uj mezore, movedir marad stand (ok: lasd createData-nal)
			}
		}
		else{
			movedir=p.mt;
			p.mt=movedirection.STAND;
			tmp=p.getCoordiante();
		}
		return createData(p.getid(),p.mt,tmp,movedir);
	}
	//meg kene oldani, hogy mit kuldjon vissza, ha all a player, nem kene neki semmit se, de ugye valamit var mert kulonben behal a program ... gondolom
	return;
}


vector<Data> Logic::endofexpl(int index){
	
}

// ez az amit a logica timetickenkent meghiv, ellenorzi a playereket, es ha kell mozgatja illetve a bombak idejet valtoztatja, vagy felrobbantja oket
// ha fal felrobban megnezi, hgoy keeletkezik-e powerup, stb
// mas dolgok meg lehetnek itt, most nem jut eszembe
vector<Data> Logic::event_update(){
	vector<Data> ret;
	for(int i=0;i<players.size();i++){
		ret.push_back(checkstate(players[i]));
	}
	for(int i=0;i<objects.size();i++){
		if(typeid(objects[i].name())=="Bomb"){
			if((Bomb)objects[i].reducetime()){
				vector<Data> tmp=(Bomb)objects[i].kababoom(map,objects);
				ret.insert(ret.end(),tmp.begin(),tmp.end());
			}
		}
		if(typeid(objects[i].name())=="Explosion"){
			if((Explosion)objects[i].tick()){
				vector<Data> tmp=;
				ret.insert(ret.end(),tmp.begin(),tmp.end());
			}
		}
	}
}

