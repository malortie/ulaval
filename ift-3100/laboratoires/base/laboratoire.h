#ifndef LABORATOIRE_H__
#define LABORATOIRE_H__

#define LABORATOIRE_ASSERT_MESSAGE( _id, _name, _msg ) "Assertion failed: " ## "Laboratoire: " ## _STRINGIZE( _name ) ## "#" ## #_id ## " " ## _msg
#define LABORATOIRE_ASSERT_MESSAGE2( _msg ) LABORATOIRE_ASSERT_MESSAGE( this->getID(),  this->getName(), _msg )

struct IContextProvider;

class Laboratoire : public IContextProvider
{

protected:
	IrrlichtDevice*		device;
	ISceneManager*		smgr;
	IVideoDriver*		driver;
	IGUIEnvironment*	env;
	IFileSystem*		fs;
	ITimer*				timer;

	bool				initiated;

	SceneInfo			sceneInfo;
	IEventReceiver*		receiver;

	float				frameDeltaTime;
	unsigned int		lastFrameTime;
	int					numFramesPerSecond;

	dimension2du		fontsize;

private:
	IGUIStaticText*		guifps;
	rect<s32>			rectfps;
	irr::core::stringw	textfps;

	MyEventReceiver*	receiver_type_provider;


public:

	Laboratoire() : IContextProvider()
	{
		this->device = nullptr;
		this->smgr = nullptr;
		this->driver = nullptr;
		this->env = nullptr;
		this->fs = nullptr;
		this->timer = nullptr;

		this->receiver = nullptr;
		this->receiver_type_provider = nullptr;

		this->initiated = false;
	}

	Laboratoire(SAppContext& context, const bool allDrivers = true) : IContextProvider(context)
	{

		if (context.device)
		{
			this->device = context.device;
			this->smgr = context.device->getSceneManager();
			this->driver = context.device->getVideoDriver();
			this->env = context.device->getGUIEnvironment();
			this->fs = context.device->getFileSystem();
			this->timer = context.device->getTimer();
		}
		else
		{
			this->context = nullptr;
			this->initiated = init(allDrivers);
		}
	}

	bool init(bool allDrivers = true)
	{
		if (initiated)
			return false;

#ifdef _DEBUG
		ENABLE_MSC_CRT_RUNTIME_HEAP_INSPECTION();
#endif

		static SAppContext scontext;

		if (!this->context)
		{
			E_DRIVER_TYPE driverType = (allDrivers)
				? driverChoiceConsole(allDrivers)
				: EDT_OPENGL;

			if (driverType == EDT_COUNT)
				return false;

			this->device = createDevice(driverType);
			if (!this->device)
				return false;

			this->device->setResizable(true);

			this->smgr		= this->device->getSceneManager();
			this->driver	= this->device->getVideoDriver();
			this->env		= this->device->getGUIEnvironment();
			this->fs		= this->device->getFileSystem();
			this->timer		= this->device->getTimer();

			scontext.device = this->device;
			this->context = &scontext;
		}
		
		IEventReceiver* Receiver = createEventReceiver(scontext);
		if (Receiver)
		{
			this->receiver = Receiver;
			this->device->setEventReceiver(Receiver);
			receiver_type_provider = static_cast<MyEventReceiver*>(Receiver);
		}

		if (Receiver && this->device)
			this->initiated = true;

		return true;
	}

	int run()
	{
		if (!initiated)
		{
			this->initiated = init(true);

			if (!initiated)
				return 1;
		}

#ifdef _DEBUG
		_ASSERT_EXPR(initiated, LABORATOIRE_ASSERT_MESSAGE2("was not properly initiated"));
#endif
		createGui(this->env);

		createScene(this->smgr);

		std::memset(&sceneInfo, 0, sizeof(sceneInfo));

		setupScene(sceneInfo);

		preRun();

		std::once_flag run_flag;

		static unsigned int startTime = timer->getTime();
		unsigned int currentTime = startTime;
		this->lastFrameTime = startTime;

		while (device->run())
		{
			currentTime = device->getTimer()->getTime();
		
			std::call_once(run_flag, [&](){ this->onRun(); });

			preBeginScene();

			if (this->driver->beginScene(sceneInfo.backbuffer, sceneInfo.zbuffer, sceneInfo.clearColor))
				onBeginScene();

			postBeginScene();

			preDrawScene();

			drawScene(this->driver);

			this->smgr->drawAll();

			postDrawScene();

			preDrawGui();

			drawGui(this->env);

			this->env->drawAll();

			postDrawGui();

			drawHelpers(this->driver);

			preEndScene();

			if (this->driver->endScene())
				onEndScene();

			postEndScene();

			clearReciever();

			updateDeltaTime(currentTime);
		}

		clearScene();

		clearGui();

		postRun();

		device->drop();

#ifdef _DEBUG
		TERMINATE_MSC_CRT_RUNTIME_HEAP_INSPECTION();
#endif
		return 0;
	}

	virtual const char* getName() const = 0;
	virtual const int	getID() const	= 0;

protected:

	virtual void createScene(ISceneManager* smgr)	= 0;
	virtual void drawScene(IVideoDriver* driver)	= 0;
	virtual void clearScene()	= 0;

	virtual void createGui(IGUIEnvironment* env) 
	{
		textfps = "";

		fontsize = env->getSkin()->getFont()->getDimension(L"a");

		rectfps.UpperLeftCorner  = vector2di(0, 0);
		rectfps.LowerRightCorner = vector2di(fontsize.Width * 64, fontsize.Height * 2);
		guifps = env->addStaticText(textfps.c_str(), rectfps, false, true, env->getRootGUIElement(), -1, false);
	}

	virtual void drawGui(IGUIEnvironment* env)
	{
		int fps = driver->getFPS();

		textfps = L"FPS: ";
		textfps += fps;
		textfps += L"\nDelta time: ";
		textfps += this->frameDeltaTime;

		float relativeY = (fontsize.Height * 2) * (1.0f / (float)driver->getViewPort().getHeight());

		guifps->setRelativePositionProportional(rectf(0, 1.f - relativeY, 1, 1));

		guifps->setOverrideColor(0xff00ff00);
		guifps->setText(textfps.c_str());
	}

	virtual void clearGui()
	{
		guifps->remove();
	}

	virtual void drawHelpers(IVideoDriver* driver)
	{

	}

	const IEventReceiver* getReceiver() const
	{ 
		return receiver; 
	}

	virtual IEventReceiver* createEventReceiver(SAppContext& context) const
	{  
		static MyEventReceiver receiver(context);
		return &receiver;
	}

	virtual void setupScene(SceneInfo& info)
	{
		info.backbuffer		= true;
		info.zbuffer		= true;
		info.clearColor		= 0xff0000fb;
	}

	virtual void preRun(){}

	virtual void postRun(){}

	virtual void preBeginScene(){}

	virtual void postBeginScene(){}

	virtual void preDrawScene(){}

	virtual void postDrawScene(){}

	virtual void preDrawGui(){}

	virtual void postDrawGui(){}

	virtual void preEndScene(){}

	virtual void postEndScene(){}

	virtual void onRun(){}

	virtual void onBeginScene(){}

	virtual void onEndScene(){}


private:
	void updateDeltaTime(unsigned int currentTime)
	{
		this->frameDeltaTime = (float)(currentTime - this->lastFrameTime) / 1000;
		this->lastFrameTime = currentTime;

		unsigned long i = 0;
		while (i++ < 0.6e+7f)
		{

		}
	}

	void clearReciever()
	{
		clearRecieverInput();
	}

	void clearRecieverInput()
	{
		if (typeid(*this->receiver) == typeid(*receiver_type_provider))
		{
			((MyEventReceiver*)receiver)->clear();
		}
	}
};



#endif // LABORATOIRE_H__