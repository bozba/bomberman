

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
	Coordinate c;
	int player_id;
	Event e;
};

class Event{
	
};

