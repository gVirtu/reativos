
class Rectangle {
	double x, y;
	int w, h;
	int speed;
	int state;
	Uint64 maxMoveTime;
	Uint64 moveTime;
	SDL_Rect r;

	public:

	Rectangle() {
		x = y = 0.0;
		w = h = speed = moveTime = state = 0;
		maxMoveTime = moveTime = 0;
		r = {0, 0, 0, 0};
	}

	Rectangle(int xx, int yy, int ww, int hh, int s, Uint64 mT, int iState) {
		x = (double) xx;
		y = (double) yy;
		w = ww; h = hh;
		speed = s;
		maxMoveTime = mT;
		moveTime = maxMoveTime;
		state = iState;
		r.x = xx; r.y = yy; r.w = ww; r.h = hh;
	}
	
	void move(double dx, double dy, double frameDelta) {
		x += dx * frameDelta; 
		y += dy * frameDelta;

		r.x = (int) x; r.y = (int) y;
	}

	SDL_Rect* getSDLRect() {
		return &r;
	}

	int getState() {
		return state;
	}

	void setState(int newState) {
		state = newState;
	}

	int getSpeed() {
		return speed;
	}

	void setSpeed(int val) {
		speed = val;
	}

	Uint64 getMoveTime() {
		return moveTime;
	}

	void resetMoveTime() {
		moveTime = maxMoveTime;
	}

	void decrementMoveTime(Uint64 amount) {
		if (moveTime > amount)
			moveTime -= amount;
		else moveTime = 0;
	}
};