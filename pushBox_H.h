class pushBox{
	private:
	int xP;
	int yP;
	unsigned char zn;
	chtype ozn;

	public:
	void levList(int*, int*, int*, int, int, int);
	void palette();
	void Level(int);
	void Play(int);
  	void HOME(int);
	void clear_lev();
	void isclear();
	void printCount(int, int);
};
