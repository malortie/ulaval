#ifndef LABORATOIRE07_H__
#define LABORATOIRE07_H__

class Laboratoire07 : public Laboratoire
{

	std::vector<polynomial> polynomes;
	vector3df*		positions;
	ISceneNode**	nodes;
	size_t			nodecount;

	float spline_frequency;

	float spline_amplitude_xy,	
		  spline_amplitude_xz;

	float interval_start, 
		  interval_end;


public:
	Laboratoire07();
	Laboratoire07(SAppContext& context, const bool allDrivers = true);


	virtual const char* getName() const	{ return "Courbes et surfaces"; }
	virtual const int	getID() const	{ return 1; }

	virtual void createScene(ISceneManager* smgr);
	virtual void drawScene(IVideoDriver* driver);
	virtual void clearScene();

	virtual void drawHelpers(IVideoDriver* driver);

	virtual IEventReceiver* createEventReceiver(SAppContext& context) const;

	void	setupPositions();

};


#endif // LABORATOIRE01_H__