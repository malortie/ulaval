#include <precompiled.h>
#include <laboratoire01.h>

Laboratoire01::Laboratoire01() : Laboratoire()
{
	this->vertexbuffer = nullptr;
	this->indexbuffer = nullptr;
}

Laboratoire01::Laboratoire01(SAppContext& context, const bool allDrivers) : Laboratoire(context, allDrivers)
{
	this->vertexbuffer = nullptr;
	this->indexbuffer = nullptr;
}

void Laboratoire01::createScene(ISceneManager* smgr)
{
	mat.Wireframe = false;
	mat.Lighting = false;
	mat.AmbientColor = mat.DiffuseColor = mat.EmissiveColor = mat.SpecularColor = 0xffffffff;


	memset(vertices, 0, sizeof(vertices));
	memset(indices, 0, sizeof(indices));

	vertices[0] = { 5, -3, 0, 0, 0, 0, 0xffff0000, 0, 0};
	vertices[1] = { -5, -3, 0, 0, 0, 0, 0xff00ff00, 0, 0 };
	vertices[2] = { 0, 5, 0, 0, 0, 0, 0xff0000ff, 0, 0 };

	indices[0] = 0;
	indices[1] = 1;
	indices[2] = 2;

	static CVertexBuffer svertexbuffer(EVT_STANDARD);
	this->vertexbuffer = &svertexbuffer;

	static CIndexBuffer sindexbuffer(EIT_16BIT);
	this->indexbuffer = &sindexbuffer;

	vertexbuffer->reallocate(3);

	vertexbuffer->push_back(vertices[0]);
	vertexbuffer->push_back(vertices[1]);
	vertexbuffer->push_back(vertices[2]);

	vertexbuffer->setDirty();

	indexbuffer->reallocate(3);

	indexbuffer->push_back(indices[0]);
	indexbuffer->push_back(indices[1]);
	indexbuffer->push_back(indices[2]);

	indexbuffer->setDirty();

	ICameraSceneNode* camera = smgr->addCameraSceneNode(0, vector3df(0,0,-10), vector3df(0,0,0));
	camera->setInputReceiverEnabled(false);
}

void Laboratoire01::drawScene(IVideoDriver* driver)
{
	driver->setMaterial(mat);
	driver->setTransform(ETS_WORLD, IdentityMatrix);
	driver->drawVertexPrimitiveList(
		vertexbuffer->pointer(),
		vertexbuffer->size(),
		indexbuffer->pointer(),
		1,
		vertexbuffer->getType(),
		EPT_TRIANGLES,
		indexbuffer->getType());

}

void Laboratoire01::clearScene()
{

}