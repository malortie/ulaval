#include <precompiled.h>
#include <laboratoire11.h>

Laboratoire11::Laboratoire11() : Laboratoire()
{
	rowsize = 2;
}

Laboratoire11::Laboratoire11(SAppContext& context, const bool allDrivers) : Laboratoire(context, allDrivers)
{
	rowsize = 2;
}

void Laboratoire11::preBeginScene()
{
	camera = smgr->getActiveCamera();
}

void Laboratoire11::createScene(ISceneManager* smgr)
{
	setupMaterials();

	setupLights(1);

	setupPositions();

	setupOrientations();

	setupNodes();

	lights[LIGHT_SLOT_DIRECTIONAL][0]->setRotation(vector3df(-35, -25, 12));

	camera = smgr->addCameraSceneNodeMaya(0, 500.0f, 200.0f, 0.0f, -1, 20.0f);
	camera->setTarget(vector3df(0,0,0));
	camera->setInputReceiverEnabled(true);


	animators[0] = smgr->createFlyCircleAnimator(vector3df(0, 0, 0), 100.0f, 0.0001f, vector3df(1, 0, 0));
	lights[0][0]->addAnimator(animators[0]);
	animators[0]->animateNode(lights[0][0], this->timer->getRealTime());

	animators[1] = smgr->createFlyCircleAnimator(vector3df(0, 0, 0), 100.0f, 0.0001f, vector3df(0, 1, 0));
	lights[1][0]->addAnimator(animators[1]);
	animators[1]->animateNode(lights[1][0], this->timer->getRealTime());

	animators[2] = smgr->createFlyCircleAnimator(vector3df(0,0,0), 100.0f, 0.0001f, vector3df(0, 0, 1));
	lights[2][0]->addAnimator(animators[2]);
	animators[2]->animateNode(lights[2][0], this->timer->getRealTime());

	IMesh* mesh = smgr->getGeometryCreator()->createPlaneMesh(dimension2df(60.0f, 60.0f));
	IMeshSceneNode* floor =  smgr->addMeshSceneNode(mesh, smgr->getRootSceneNode(), -1,  vector3df(0, -15, 0));
	mesh->drop();
	floor->getMaterial(0).Lighting = false;
}

void Laboratoire11::drawScene(IVideoDriver* driver)
{
	updateLights();

	updateNodes();
}

void Laboratoire11::clearScene()
{
	clearLights();
}

IGUIStaticText* guilevel = nullptr;

void Laboratoire11::createGui(IGUIEnvironment* env)
{
	Laboratoire::createGui(env);
	guilevel = env->addStaticText(L"", recti(0, 0, 256, fontsize.Height), false, true, env->getRootGUIElement(), -1, false);

	guicamera = env->addStaticText(textcamera.c_str(), recti(0, 0, 256, fontsize.Height * 12), false, true, env->getRootGUIElement(), -1, false);
}

void Laboratoire11::drawGui(IGUIEnvironment* env)
{
	Laboratoire::drawGui(env);

	vector3df spherepos = nodes[NODE_SLOT_SPHERE]->getPosition();

	float dist = camera->getPosition().getDistanceFrom(spherepos);
	float expdist = ceil(exp(dist));
	int levelCount = 8;

	int level = (int)((dist < 64.0f) ? (levelCount - (int)((dist * 6.0f) / 64.0f)) : 2);

	stringw s = "Level: ";
	s += level;
	guilevel->setText(s.c_str());
	guilevel->setRelativePosition(position2di(0, 0));

	unsigned int rw, rh;
	float viewportHeight = (float)driver->getViewPort().getHeight();

	vector3df v;
	v = camera->getPosition();

	textcamera = "Camera position: (";
	textcamera += v.X;
	textcamera += ",\t";
	textcamera += v.Y;
	textcamera += ",\t";
	textcamera += v.Z;
	textcamera += ")\n";

	rw = env->getSkin()->getFont()->getDimension(textcamera.c_str()).Width;

	v = camera->getViewMatrix().getRotationDegrees();

	textcamera += "Camera rotation: (";
	textcamera += v.X;
	textcamera += ",\t";
	textcamera += v.Y;
	textcamera += ",\t";
	textcamera += v.Z;
	textcamera += ")\n\n";

	textcamera += "Camera pitch(rad): ";
	textcamera += v.X;
	textcamera += "\n";
	textcamera += "Camera pitch(deg): ";
	textcamera += degToRad(v.X);
	textcamera += "\n\n";

	textcamera += "Camera yaw(rad): ";
	textcamera += v.Y;
	textcamera += "\n";
	textcamera += "Camera yaw(deg): ";
	textcamera += degToRad(v.Y);
	textcamera += "\n\n";

	textcamera += "Camera roll(rad): ";
	textcamera += v.Z;
	textcamera += "\n";
	textcamera += "Camera roll(deg): ";
	textcamera += degToRad(v.Z);
	textcamera += "\n\n";

	rh = (fontsize.Height * 12);

	recti r;
	r.UpperLeftCorner = dimension2di(0, 0);
	r.LowerRightCorner = dimension2di(rw, rh);

	float relativeY = (float)rh * (1.0f / viewportHeight);

	guicamera->setRelativePositionProportional(rectf(0, .95f - relativeY, 1, 1));

	guicamera->setOverrideColor(0xff00ff00);
	guicamera->setText(textcamera.c_str());

}

void Laboratoire11::clearGui()
{
	Laboratoire::clearGui();

	guicamera->remove();
}

void Laboratoire11::drawHelpers(IVideoDriver* driver)
{
	driver->setTransform(ETS_WORLD, IdentityMatrix);

	aabbox3df bounds(this->lights[0][0]->getPosition());
	bounds.MaxEdge += vector3df(1, 1, 1);
	bounds.MinEdge += vector3df(-1, -1, -1);

	driver->setMaterial(materials[0]);
	driver->draw3DBox(bounds);

	bounds = aabbox3df(this->lights[1][0]->getPosition());
	bounds.MaxEdge += vector3df(1, 1, 1);
	bounds.MinEdge += vector3df(-1, -1, -1);

	driver->setMaterial(materials[1]);
	driver->draw3DBox(bounds);

	bounds = aabbox3df(this->lights[2][0]->getPosition());
	bounds.MaxEdge += vector3df(1, 1, 1);
	bounds.MinEdge += vector3df(-1, -1, -1);

	driver->setMaterial(materials[2]);
	driver->draw3DBox(bounds);
}


IEventReceiver* Laboratoire11::createEventReceiver(SAppContext& context) const
{
	static BasicCameraOrbitInputEventReceiver receiver(context);
	return &receiver;
}

ILightSceneNode* Laboratoire11::getLight(const int slot, int index)
{
	return lights[slot][index];
}
void Laboratoire11::setLight(const int slot, int index, ILightSceneNode* light)
{
	lights[slot][index] = light;
}

ILightSceneNode* Laboratoire11::setLight(const int slot, int index, const E_LIGHT_TYPE& type)
{
	ILightSceneNode** light = &lights[slot][index];
	(*light) = smgr->addLightSceneNode();
	(*light)->setLightType(type);

	return (*light);
}

E_LIGHT_TYPE Laboratoire11::getLightType(const int slot, int index)
{
	return lights[slot][index]->getLightType();
}

void Laboratoire11::setLightType(const int slot, int index, const E_LIGHT_TYPE& type)
{
	lights[slot][index]->setLightType(type);
}

void Laboratoire11::setupLights(const size_t rowsize)
{
	this->rowsize = rowsize;

	size_t i, j;
	vector3df origin(0);

	for (i = 0; i < ELT_COUNT; i++){
		lights[i] = new ILightSceneNode*[rowsize];
		for (j = 0; j < rowsize; j++){
			lights[i][j] = smgr->addLightSceneNode(0, origin, SColorf(0xffffff), 1.0f, -1);
			lights[i][j]->setLightType(*(E_LIGHT_TYPE*)&i);
		}
	}
}

void Laboratoire11::clearLights()
{
	size_t i, j;
	ILightSceneNode** light;

	for (i = 0; i < ELT_COUNT; i++) 
	{
		if (lights[i])
		{
			for (j = 0; j < this->rowsize; j++) 
			{
				light = &lights[i][j];
				if (*light) 
				{
					(*light)->remove();
					(*light) = nullptr;
				}
			}

			delete [] lights[i];
			lights[i] = nullptr;
		}
	}
}

void Laboratoire11::setupPositions()
{
	this->positions[0] = vector3df(-5, 10, 0);
	this->positions[1] = vector3df(0, -5, 10);
	this->positions[2] = vector3df(10, 0, -5);
}

void Laboratoire11::setupOrientations()
{
	this->orientations[0] = quaternion().fromAngleAxis(0, vector3df(1, 1, 0).normalize());
	this->orientations[1] = quaternion().fromAngleAxis(0, vector3df(0, 1, 1).normalize());
	this->orientations[2] = quaternion().fromAngleAxis(0, vector3df(1, 0, 1).normalize());
}

void Laboratoire11::setupNodes()
{
	vector3df euler;
	memset(&euler, 0, sizeof(euler));

	nodes[NODE_SLOT_CUBE] = smgr->addCubeSceneNode(10.0f);
	nodes[NODE_SLOT_TORUS] = smgr->addCubeSceneNode(10.0f);
	nodes[NODE_SLOT_SPHERE] = smgr->addSphereSceneNode(5.0f, 32);

	size_t i, j;
	for (i = 0; i < NODE_SLOT_COUNT; i++) {
		orientations[i].toEuler(euler);

		nodes[i]->setPosition(positions[i]);
		nodes[i]->setRotation(euler);
		nodes[i]->setMaterialFlag(EMF_LIGHTING, true);

		for (j = 0; j < nodes[i]->getMaterialCount(); j++)
			nodes[i]->getMaterial(j) = materials[i];
	}
}

void Laboratoire11::setupMaterials()
{
	materials[0].AmbientColor = 0x8C0000;
	materials[0].DiffuseColor = 0xFF0000;
	materials[0].EmissiveColor = 0xff540404;
	materials[0].SpecularColor = 0x25ffffff;
	materials[0].Shininess = 0.5f;

	materials[1].AmbientColor = 0xff084500;
	materials[1].DiffuseColor = 0xff2CCC16;
	materials[1].EmissiveColor = 0xff0C2B08;
	materials[1].SpecularColor = 0x45ffffff;
	materials[1].Shininess = 0.5f;

	materials[2].AmbientColor = 0xff007371;
	materials[2].DiffuseColor = 0xff0CF5F1;
	materials[2].EmissiveColor = 0xff104746;
	materials[2].SpecularColor = 0x05ffffff;
	materials[2].Shininess = 0.5f;
}

float angle1 = 0.0f;

void Laboratoire11::updateNodes()
{
	vector3df spherepos = nodes[NODE_SLOT_SPHERE]->getPosition();

	float dist = camera->getPosition().getDistanceFrom(spherepos);
	float expdist = ceil(exp(dist));
	int levelCount = 8;

	int level = (int)((dist < 64.0f) ? (levelCount - (int)((dist * 6.0f) / 64.0f)) : 2);

	nodes[NODE_SLOT_SPHERE]->remove();
	nodes[NODE_SLOT_SPHERE] = smgr->addSphereSceneNode(5.0f, 4*level, 0, -1, spherepos);
	nodes[NODE_SLOT_SPHERE]->getMaterial(0) = materials[2];

	angle1 += 1.0f;

	if (angle1 > 90)
		angle1 -= -180;

	float radAngle = degToRad(angle1);
	float c = cosf(radAngle);
	float s = sinf(radAngle);

	vector3df saxis = vector3df(s, c, c).normalize();
	vector3df daxis = vector3df(c, s, s).normalize();

	CMatrix4<float> mat, rot;
	rot = mat.buildRotateFromTo(saxis, daxis);
	
	this->nodes[0]->setRotation(rot.getRotationDegrees());

	saxis = vector3df(s, c, s).normalize();
	daxis = vector3df(c, s, c).normalize();

	rot = mat.buildRotateFromTo(saxis, daxis);
	this->nodes[1]->setRotation(rot.getRotationDegrees());

	saxis = vector3df(s, s, c).normalize();
	daxis = vector3df(c, c, s).normalize();

	rot = mat.buildRotateFromTo(saxis, daxis);
	this->nodes[2]->setRotation(rot.getRotationDegrees());
}

void Laboratoire11::updateLights()
{
	vector3df lightdir = lights[LIGHT_SLOT_DIRECTIONAL][0]->getPosition();
	lightdir = -lightdir.normalize();

	lights[LIGHT_SLOT_DIRECTIONAL][0]->setRotation(vector3df(radToDeg(acosf(lightdir.X)), radToDeg(asinf(lightdir.Y)), radToDeg(1 - acosf(lightdir.Z))));
}