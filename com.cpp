

class Commun{
	iGui gui;
	iLogic logic;
	iServer server;
	iClient client;	
	public:
		Commun(iGui g);
		Commun(iGui g,iServer s);
		Commun(iGui g,iClient c);
		void keyevent(int[] keycode);
		void change(Data d);
		bool startmap(Map m);
		bool startserver(Map m);
		
};


//ezt küldjük a guinak, ebből tudja, hogy hol mi történt és kivel (ha a pid nem 0)
class Data{
	public:
	Event e;
	Coordinate c;
	int player_id;
	Data(Event ev,Coordiante c_,int pid=0):e(ev),c(c_),player_id(pid){}
};

//milyen eventek történhetnek gui szempontból, a stopokból nem biztos, hogy kell külön 4 fajta
enum Event {MLEFT,MRIGHT,MUP,MDOWN,SLEFT,SRIGHT,SUP,SDOWN,DIE,BOMB,EXPL_CENTER,EXPL_HOR,EXPL_VER,WALL_DES,B_POWUP_APP,SOD_POWUP_APP,PLAYER_DIE,MONSTER_DIE};
