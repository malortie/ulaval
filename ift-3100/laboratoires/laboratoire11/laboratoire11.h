#ifndef LABORATOIRE11_H__
#define LABORATOIRE11_H__

class Laboratoire11 : public Laboratoire
{

protected:
	enum LightSlot
	{
		LIGHT_SLOT_OMNI			= ELT_POINT,
		LIGHT_SLOT_SPOT			= ELT_SPOT,
		LIGHT_SLOT_DIRECTIONAL	= ELT_DIRECTIONAL,
	};

	enum NodeSlot
	{
		NODE_SLOT_CUBE		= 0,
		NODE_SLOT_TORUS		= 1,
		NODE_SLOT_SPHERE	= 2,

		NODE_SLOT_COUNT,
	};

	ICameraSceneNode *camera;

	ILightSceneNode** lights[ELT_COUNT];
	size_t rowsize;

	IMeshSceneNode* nodes[NODE_SLOT_COUNT];
	vector3df positions[NODE_SLOT_COUNT];
	quaternion orientations[NODE_SLOT_COUNT];
	SMaterial materials[NODE_SLOT_COUNT];

	ISceneNodeAnimator* animators[ELT_COUNT];

	IGUIStaticText* guicamera;
	irr::core::stringw textcamera;

public:
	Laboratoire11();
	Laboratoire11(SAppContext& context, const bool allDrivers = true);


	virtual const char* getName() const	{ return "Eclairage"; }
	virtual const int	getID() const	{ return 11; }

	virtual void createScene(ISceneManager* smgr);
	virtual void drawScene(IVideoDriver* driver);
	virtual void clearScene();

	virtual void createGui(IGUIEnvironment* env);
	virtual void drawGui(IGUIEnvironment* env);
	virtual void clearGui();

	virtual void drawHelpers(IVideoDriver* driver);

	virtual void preBeginScene();

	virtual IEventReceiver* createEventReceiver(SAppContext& context) const;

private:

	void				setupPositions();
	void				setupOrientations();
	void				setupNodes();
	void				setupMaterials();

	void				updateNodes();
	void				updateLights();

	ILightSceneNode*	getLight(const int slot, int index);
	void				setLight(const int slot, int index, ILightSceneNode* light);
	ILightSceneNode*	setLight(const int slot, int index, const E_LIGHT_TYPE& type);

	E_LIGHT_TYPE		getLightType(const int slot, int index);
	void				setLightType(const int slot, int index, const E_LIGHT_TYPE& type);

	void				setLightData(const int slot, int index, const SLight& data);
	const SLight&		getLightData(const int slot, int index) const;

	virtual void		setupLights(const size_t rowsize = 2);
	virtual void		clearLights();


};


#endif // LABORATOIRE11_H__