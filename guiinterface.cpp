

class iGui{
	int width;
	int height;
	public:
		virtual bool drawbackground(Map m)=0;
		virtual void drawobject(Data d)=0; //flyweight
	 	virtual int[] keyevent()=0;//1. param= keycode ; 2. param=jatekos szam
		
};


