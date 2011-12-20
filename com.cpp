

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

class Data{
	public:
	Event e;
	Coordinate c;
	int player_id;
	Data(Event ev,Coordiante c_,int pid=0):e(ev),c(c_),player_id(pid){}
};

enum Event {MLEFT,MRIGHT,MUP,MDOWN,SLEFT,SRIGHT,SUP,SDOWN,DIE,BOMB,EXPL_CENTER,EXPL_R,EXPL_L,EXPL_UP,EXPL_DOWN,WALL_DES,B_POWUP_APP,SOD_POWUP_APP}

