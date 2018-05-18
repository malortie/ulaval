#include <precompiled.h>
#include <laboratoire07.h>

Laboratoire07::Laboratoire07() : Laboratoire()
{
	polynomes.push_back(polynomial{ 1.0f, -6.0f, 2.0f, });
	polynomes.push_back(polynomial{ 2.0f, -8.0f, 9.0f });

	spline_frequency		= 0.0f;
	spline_amplitude_xy		= 0.0f;
	spline_amplitude_xz		= 0.0f;

	interval_start			= 0.0f;
	interval_end			= 0.0f;

	this->nodes				= nullptr;
	this->positions			= nullptr;

}

Laboratoire07::Laboratoire07(SAppContext& context, const bool allDrivers) : Laboratoire(context, allDrivers)
{
	polynomes.push_back(polynomial{ 1.0f, -6.0f, 2.0f });
	polynomes.push_back(polynomial{ 2.0f, -8.0f, 9.0f });

	spline_frequency		= 0.0f;
	spline_amplitude_xy		= 0.0f;
	spline_amplitude_xz		= 0.0f;

	interval_start			= 0.0f;
	interval_end			= 0.0f;

	this->nodes				= nullptr;
	this->positions			= nullptr;
}

void Laboratoire07::createScene(ISceneManager* smgr)
{
	setupPositions();

	smgr->addCubeSceneNode(0.1f);

	ICameraSceneNode* camera = smgr->addCameraSceneNodeFPS(0, 100.0f, 0.05f);
	camera->setInputReceiverEnabled(false);
}

void Laboratoire07::drawScene(IVideoDriver* driver)
{

}

void Laboratoire07::clearScene()
{
	for (size_t i = 0; i < nodecount; i++) {
		if (nodes[i])
			nodes[i]->remove();
	}

	delete [] nodes;
	delete [] positions;
}

void Laboratoire07::drawHelpers(IVideoDriver* driver)
{
	driver->setTransform(ETS_WORLD, IdentityMatrix);

	vector3df* p1 = &positions[0];
	vector3df* p2 = &positions[1];

	size_t colorfrequency = (int)((float)255.0f / (float)nodecount);

	SMaterial mat;
	mat.Lighting = false;
	mat.Wireframe = false;

	for (size_t i = 0; i < nodecount; i++){

		driver->setMaterial(mat);

		mat.AmbientColor =
		mat.DiffuseColor =
		mat.EmissiveColor =
		mat.SpecularColor = SColor(255, i * colorfrequency, 255 - (i * colorfrequency), 0);

		driver->draw3DLine(*(p1++), *(p2++), mat.EmissiveColor);
	}
}


IEventReceiver* Laboratoire07::createEventReceiver(SAppContext& context) const
{
	static BasicCameraFpsInputEventReceiver receiver(context);
	return &receiver;
}


void Laboratoire07::setupPositions()
{
	spline_frequency		= 0.5f;
	spline_amplitude_xy		= 0.0001f;
	spline_amplitude_xz		= 0.01f;

	interval_start			= -50.0f;
	interval_end			= 50.0f;

	float domain = fabs(interval_end - interval_start);

	nodecount = (int)(domain * fabs(spline_frequency));
	float invfrequency = domain / (float)nodecount;

	this->nodes = new ISceneNode*[nodecount + 1];
	this->positions = new vector3df[nodecount + 1];

	size_t i;
	for (i = 0; i < nodecount; i++)
		this->nodes[i] = nullptr;

	polynomial* p_xy = &this->polynomes.at(0);
	polynomial* p_xz = &this->polynomes.at(1);

	float x1, y1, x2, y2, z1, z2;

	float x = this->interval_start;

	size_t position_index = 1;

	for (i = 0; i < nodecount; i++)
	{
		x1 = x + i * invfrequency;
		x2 = x + (i + 1) * invfrequency;

		y1 = p_xy->evaluate(x1)*spline_amplitude_xy;
		y2 = p_xy->evaluate(x2)*spline_amplitude_xy;

		z1 = p_xz->evaluate(x1)*spline_amplitude_xz;
		z2 = p_xz->evaluate(x2)*spline_amplitude_xz;

		vector3df p1 = vector3df(x1, y1, z1);
		vector3df p2 = vector3df(x2, y2, z2);

		this->positions[i]	= p1;
		this->positions[i + 1]		= p2;
	}

	for (i = 0; i < nodecount; i++)
	{
		vector3df* p1 = &positions[i];
		vector3df* p2 = &positions[i + 1];

		//nodes[i]	 = smgr->addSphereSceneNode(1, 8, 0, -1, *p1);
		//nodes[i + 1] = smgr->addSphereSceneNode(1, 8, 0, -1, *p2);
	}
}