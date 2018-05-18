#ifndef LABORATOIRE01_H__
#define LABORATOIRE01_H__

class Laboratoire01 : public Laboratoire
{
	IVertexBuffer*	vertexbuffer;
	IIndexBuffer*	indexbuffer;
	SMaterial		mat;
	S3DVertex		vertices[3];
	unsigned short	indices[3];

public:
	Laboratoire01();
	Laboratoire01(SAppContext& context, const bool allDrivers = true);


	virtual const char* getName() const	{ return "Bonjour triangle"; }
	virtual const int	getID() const	{ return 1; }

	virtual void createScene(ISceneManager* smgr);
	virtual void drawScene(IVideoDriver* driver);
	virtual void clearScene();
};


#endif // LABORATOIRE01_H__