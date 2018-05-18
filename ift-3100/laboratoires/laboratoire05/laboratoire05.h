#ifndef LABORATOIRE05_H__
#define LABORATOIRE05_H__

class Laboratoire05 : public Laboratoire
{
protected:
	vector3df startpos, endpos;
	float durationS, durationMs;
	float angle, anglegap;
	float sineangle;

	float startTime, lastTime, elapsedTime;
	float timeDelta;
	float movementElapsedTime;

	float startFov, endFov;
	float currentFov, idealFov;

	ISceneNodeAnimator* animator;
	IGUIStaticText* guiAngle;

	stringw textAngle;

	vector3df* nodePositions;
	IMeshSceneNode** nodes;
	size_t nodeCount;
	float nodeAngle;
	size_t loopcount;
	size_t loopmeshcount;

public:
	Laboratoire05();
	Laboratoire05(SAppContext& context, const bool allDrivers = true);


	virtual const char* getName() const	{ return "Effet vertigo"; }
	virtual const int	getID() const	{ return 1; }

	virtual void createScene(ISceneManager* smgr);
	virtual void drawScene(IVideoDriver* driver);
	virtual void clearScene();

	virtual void createGui(IGUIEnvironment* env);
	virtual void drawGui(IGUIEnvironment* env);
	virtual void clearGui();

	virtual IEventReceiver* createEventReceiver(SAppContext& context) const;
};


#endif // LABORATOIRE05_H__