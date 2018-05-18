#include <precompiled.h>
#include <laboratoire05.h>

Laboratoire05::Laboratoire05() : Laboratoire()
{
	startpos.set(0, 0, 0);
	endpos.set(0, 0, -10);
	durationS = 5.0f;
	durationMs = durationS * 1e+3f;
	angle = 0.0f;
	anglegap = 0.0f;
	movementElapsedTime = 0.0f;

	startFov	= PI / 2.5f;
	endFov		= PI * (1.0f / 8.0f);

	nodeCount = 0;

	nodes = nullptr;
}

Laboratoire05::Laboratoire05(SAppContext& context, const bool allDrivers) : Laboratoire(context, allDrivers)
{
	startpos.set(0, 0, 0);
	endpos.set(0, 0, -10);
	durationS = 5.0f;
	durationMs = durationS * 1e+3f;
	angle = 0.0f;
	anglegap = 0.0f;
	movementElapsedTime = 0.0f;

	startFov	= PI / 2.5f;
	endFov		= PI * (1.0f / 8.0f);

	nodeCount = 0;

	nodes = nullptr;
}

void Laboratoire05::createScene(ISceneManager* smgr)
{
	
	loopcount = 20;
	loopmeshcount = 40;
	float loopFrequency = 2.0f;
	float twoPI = (2 * PI);
	float angleGap = twoPI / (float)loopmeshcount;
	float cycleAngle = 0.0f;
	float cycleGap = loopFrequency / (float)loopmeshcount;

	nodeCount = loopcount * loopmeshcount;
	nodes = new IMeshSceneNode*[nodeCount];
	nodePositions = new vector3df[nodeCount];

	size_t index = 0;

	vector3df loopStartPos = vector3df(0,0,-10.0f);
	size_t i, j;
	for (i = 0; i < loopcount; i++)
	{
		cycleAngle = 0.0f;

		for (j = 0; j < loopmeshcount; j++)
		{
			float c, s;
			c = cosf(cycleAngle);
			s = sinf(cycleAngle);

			nodePositions[index] = vector3df(
				loopStartPos.X + c,
				loopStartPos.Y + s,
				loopStartPos.Z + (cycleGap * j) + (i * loopFrequency));
				//loopStartPos.Z + (cycleGap * cycleAngle) + (i * loopFrequency));

			nodes[index] = smgr->addCubeSceneNode(0.08f, 0, -1,
				nodePositions[index],
				vector3df(0, 0, 0));
			smgr->getMeshManipulator()->setVertexColors(nodes[index]->getMesh(), SColor(255, 255, 0, 0));
			nodes[index]->setMaterialFlag(EMF_LIGHTING, false);

			index++;

			cycleAngle += angleGap;
		}
	}


	ICameraSceneNode* camera = smgr->addCameraSceneNode(0, startpos, vector3df(0,0,1));
	camera->setInputReceiverEnabled(false);
	camera->setFOV(startFov);


	animator = smgr->createFlyStraightAnimator(startpos, endpos, (unsigned int)durationMs, false, false);
	camera->addAnimator(animator);
	animator->animateNode(camera, this->timer->getRealTime());


	startTime	= static_cast<float>(timer->getTime());
	lastTime	= startTime;
	timeDelta	= 0.0f;
	elapsedTime = 0.0f;
	lastTime	= startTime;
	movementElapsedTime = 0.0f;
}

void Laboratoire05::drawScene(IVideoDriver* driver)
{
	float currentTime = static_cast<float>(timer->getTime());
	timeDelta			= currentTime - lastTime;
	elapsedTime			= currentTime - startTime;

	static bool inverseFovScale = true;

	if (movementElapsedTime > 0.0f && animator->hasFinished()){
		ISceneNodeAnimator* node = this->animator->createClone(smgr->getActiveCamera(), smgr);
		node->drop();

		inverseFovScale = !inverseFovScale;

		if (!inverseFovScale)
			animator = smgr->createFlyStraightAnimator(startpos, endpos, (unsigned int)durationMs, false, false);
		else
			animator = smgr->createFlyStraightAnimator(endpos, startpos, (unsigned int)durationMs, false, false);

		smgr->getActiveCamera()->addAnimator(animator);
		this->animator->animateNode(smgr->getActiveCamera(), timer->getTime());
		movementElapsedTime = 0.0f;
	}


	movementElapsedTime += timeDelta;

	const float radiandelta = fabs(endFov - startFov);

	float elapsedTimeS = elapsedTime * 1e-3f;
	float invDurationS = 1.0f / (float)durationS;
	float movementElapsedTimeS = movementElapsedTime * 1e-3f;

	float t = ((movementElapsedTimeS * radiandelta) * invDurationS);
	angle = t;

	idealFov = t *1.01f;

	if (!inverseFovScale)
	{
		currentFov = fabs(startFov - t);
		smgr->getActiveCamera()->setFOV(currentFov);
	}
	else
	{
		currentFov = fabs((endFov + t));
		smgr->getActiveCamera()->setFOV(currentFov);
	}


	lastTime = currentTime;

	nodeAngle += 4.0f;

	if (nodeAngle > 180.0f)
		nodeAngle -= 360.0f;

	static bool inverseCosine = false;

	size_t index = 0;
	for (size_t l = 0; l < loopcount; l++){

		inverseCosine = !inverseCosine;

		for (size_t i = 0; i < loopmeshcount; i++){

			nodes[index]->setRotation(vector3df(
				nodes[index]->getRotation().X,
				nodes[index]->getRotation().Y,
				nodes[index]->getRotation().Z + 1));



			float c = cosf(degToRad(nodeAngle));
			float s = sinf(degToRad(nodeAngle));

			float scaleX = 0.005f, scaleY = 0.005f;

			vector3df p = nodePositions[index];
			if (!inverseCosine) {
				p.X += (((i % 2) == 0) ? c * scaleX : -c * scaleX);
				p.Y += (((i % 2) == 0) ? s * scaleY : -s * scaleY);
			}
			else {
				p.X += (((i % 2) == 0) ? -c * scaleX : c * scaleX);
				p.Y += (((i % 2) == 0) ? -s * scaleY : s * scaleY);
			}

			nodes[index]->setPosition(p);

			index++;
		}
	}

	inverseCosine = false;
}

void Laboratoire05::clearScene()
{
	delete[] nodePositions;
	nodePositions = nullptr;

	for (size_t i = 0; i < nodeCount; i++)
	{
		nodes[i]->remove();
		nodes[i] = nullptr;
	}

	delete [] nodes;
	nodes = nullptr;
}

void Laboratoire05::createGui(IGUIEnvironment* env)
{
	Laboratoire::createGui(env);

	guiAngle = env->addStaticText(L"", recti(0, 0, 256, fontsize.Height), false, true, env->getRootGUIElement(), -1, false);
}

void Laboratoire05::drawGui(IGUIEnvironment* env)
{
	Laboratoire::drawGui(env);

	textAngle = "Angle(rad): ";
	textAngle += angle;
	textAngle += "\n";
	textAngle += "Angle(deg): ";
	textAngle += radToDeg(angle);
	textAngle += "\n";
	textAngle += "Start Fov(rad): ";
	textAngle += startFov;
	textAngle += "\n";
	textAngle += "End Fov(rad): ";
	textAngle += endFov;
	textAngle += "\n";
	textAngle += "Current Fov(rad): ";
	textAngle += currentFov;
	textAngle += "\n";
	textAngle += "Ideal Fov(rad): ";
	textAngle += idealFov;
	textAngle += "\n";


	int numLines = 6;
	float rh = static_cast<float>(fontsize.Height * numLines);

	recti r;
	r.UpperLeftCorner = dimension2di(0, 0);
	r.LowerRightCorner = dimension2di(256, (unsigned int)rh);

	float relativeY = (float)rh * (1.0f / driver->getViewPort().getHeight());

	guiAngle->setRelativePositionProportional(rectf(0, .95f - relativeY, 1, 1));

	guiAngle->setOverrideColor(0xff00ff00);
	guiAngle->setText(textAngle.c_str());

}

void Laboratoire05::clearGui()
{
	Laboratoire::clearGui();

	guiAngle->remove();
}

IEventReceiver* Laboratoire05::createEventReceiver(SAppContext& context) const
{
	static BasicCameraInputEventReceiver receiver(context);
	return &receiver;
}