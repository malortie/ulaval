#ifndef PRIMITIVE_CUBE_HPP__
#define PRIMITIVE_CUBE_HPP__

namespace framework
{ 

// TEXTURELESS PRIMITIVE CUBE

class Primitive_Cube : public irr::scene::ISceneNode
{
	irr::core::aabbox3d<irr::f32> Box;
	irr::video::S3DVertex Vertices[8];
	irr::u16 Indices[36];
	irr::video::SMaterial Material[6];

public:
	Primitive_Cube(
		irr::scene::ISceneNode* parent,
		irr::scene::ISceneManager* mgr, 
		irr::s32 id = -1, 
		const irr::core::vector3df& position = irr::core::vector3df(0, 0, 0),
		const irr::core::vector3df& rotation = irr::core::vector3df(0, 0, 0),
		const irr::core::vector3df& scale	 = irr::core::vector3df(1.0f, 1.0f, 1.0f))
		: irr::scene::ISceneNode(parent, mgr, id, position, rotation, scale)
	{
		for (size_t i = 0; i < 6; i++)
		{
			Material[i].Wireframe = false;
			Material[i].Lighting = false;
		}

		Material[0].AmbientColor  = 
		Material[0].DiffuseColor  = 
		Material[0].EmissiveColor =
		Material[0].SpecularColor = irr::video::SColor(255, 255, 0, 0);

		Material[1].AmbientColor  = 
		Material[1].DiffuseColor  = 
		Material[1].EmissiveColor =
		Material[1].SpecularColor = irr::video::SColor(255, 0, 255, 0);

		Material[2].AmbientColor  = 
		Material[2].DiffuseColor  = 
		Material[2].EmissiveColor =
		Material[2].SpecularColor = irr::video::SColor(255, 0, 0, 255);

		Material[3].AmbientColor  = 
		Material[3].DiffuseColor  = 
		Material[3].EmissiveColor =
		Material[3].SpecularColor = irr::video::SColor(255, 255, 0, 255);

		Material[4].AmbientColor  = 
		Material[4].DiffuseColor  = 
		Material[4].EmissiveColor =
		Material[4].SpecularColor = irr::video::SColor(255, 255, 255, 0);

		Material[5].AmbientColor  = 
		Material[5].DiffuseColor  = 
		Material[5].EmissiveColor =
		Material[5].SpecularColor = irr::video::SColor(255, 0, 255, 255);


		irr::f32 xhalf, yhalf, zhalf;
		xhalf = scale.X * 0.5f;
		yhalf = scale.Y * 0.5f;
		zhalf = scale.Z * 0.5f;

		Vertices[0] = irr::video::S3DVertex(-xhalf, -yhalf, -zhalf,	0, 0, 0, Material[0].DiffuseColor, 0, 0);
		Vertices[1] = irr::video::S3DVertex(-xhalf, -yhalf, zhalf,	0, 0, 0, Material[1].DiffuseColor, 0, 0);
		Vertices[2] = irr::video::S3DVertex(-xhalf, yhalf, -zhalf,	0, 0, 0, Material[2].DiffuseColor, 0, 0);
		Vertices[3] = irr::video::S3DVertex(-xhalf, yhalf, zhalf,	0, 0, 0, Material[3].DiffuseColor, 0, 0);
		Vertices[4] = irr::video::S3DVertex(xhalf, -yhalf, -zhalf,	0, 0, 0, Material[4].DiffuseColor, 0, 0);
		Vertices[5] = irr::video::S3DVertex(xhalf, -yhalf, zhalf,	0, 0, 0, Material[5].DiffuseColor, 0, 0);
		Vertices[6] = irr::video::S3DVertex(xhalf, yhalf, -zhalf,	0, 0, 0, Material[6].DiffuseColor, 0, 0);
		Vertices[7] = irr::video::S3DVertex(xhalf, yhalf, zhalf,	0, 0, 0, Material[7].DiffuseColor, 0, 0);

		Indices[0]  = 0;	Indices[1]  = 6;	Indices[2]  = 4;
		Indices[3]  = 0;	Indices[4]  = 2;	Indices[5]  = 6;
		Indices[6]  = 0;	Indices[7]  = 3;	Indices[8]  = 2;
		Indices[9]  = 0;	Indices[10] = 1;	Indices[11] = 3;
		Indices[12] = 2;	Indices[13] = 7;	Indices[14] = 6;
		Indices[15] = 2;	Indices[16] = 3;	Indices[17] = 7;
		Indices[18] = 4;	Indices[19] = 6;	Indices[20] = 7;
		Indices[21] = 4;	Indices[22] = 7;	Indices[23] = 5;
		Indices[24] = 0;	Indices[25] = 4;	Indices[26] = 5;
		Indices[27] = 0;	Indices[28] = 5;	Indices[29] = 1;
		Indices[30] = 1;	Indices[31] = 5;	Indices[32] = 7;
		Indices[33] = 1;	Indices[34] = 7;	Indices[35] = 3;

		Box.reset(Vertices[0].Pos);
		for (irr::s32 i = 1; i < 36; ++i)
			Box.addInternalPoint(Vertices[i].Pos);
	}

	virtual void OnRegisterSceneNode()
	{
		if (IsVisible)
			SceneManager->registerNodeForRendering(this);

		irr::scene::ISceneNode::OnRegisterSceneNode();
	}

	virtual void render()
	{
		irr::video::IVideoDriver* driver = SceneManager->getVideoDriver();

		driver->setTransform(irr::video::ETS_WORLD, AbsoluteTransformation);

		driver->setMaterial(Material[0]);
		driver->drawIndexedTriangleList(&Vertices[0], 8, &Indices[0], 2);

		driver->setMaterial(Material[1]);
		driver->drawIndexedTriangleList(&Vertices[0], 8, &Indices[6], 2);

		driver->setMaterial(Material[2]);
		driver->drawIndexedTriangleList(&Vertices[0], 8, &Indices[12], 2);

		driver->setMaterial(Material[3]);
		driver->drawIndexedTriangleList(&Vertices[0], 8, &Indices[18], 2);

		driver->setMaterial(Material[4]);
		driver->drawIndexedTriangleList(&Vertices[0], 8, &Indices[24], 2);

		driver->setMaterial(Material[5]);
		driver->drawIndexedTriangleList(&Vertices[0], 8, &Indices[30], 2);
	}

	virtual const irr::core::aabbox3d<irr::f32>& getBoundingBox() const
	{
		return Box;
	}

	virtual irr::u32 getMaterialCount() const
	{
		return 6;
	}

	virtual irr::video::SMaterial& getMaterial(irr::u32 i)
	{
		return Material[i];
	}

};


//
// TEXTURED PRIMITIVE CUBE
//

class Primitive_CubeTextured : public irr::scene::ISceneNode
{
	irr::core::aabbox3d<irr::f32> Box;
	irr::video::S3DVertex Vertices[24];
	irr::u16 Indices[36];
	irr::video::SMaterial Material[6];

public:
	Primitive_CubeTextured(
		irr::scene::ISceneNode* parent,
		irr::scene::ISceneManager* mgr, 
		irr::s32 id = -1, 
		const irr::core::vector3df& position		= irr::core::vector3df(0, 0, 0),
		const irr::core::vector3df& rotation		= irr::core::vector3df(0, 0, 0),
		const irr::core::vector3df& scale			= irr::core::vector3df(1.0f, 1.0f, 1.0f),
		const irr::video::SMaterial& frontMaterial	= irr::video::IdentityMaterial,
		const irr::video::SMaterial& leftMaterial	= irr::video::IdentityMaterial,
		const irr::video::SMaterial& backMaterial	= irr::video::IdentityMaterial,
		const irr::video::SMaterial& rightMaterial	= irr::video::IdentityMaterial,
		const irr::video::SMaterial& topMaterial	= irr::video::IdentityMaterial,
		const irr::video::SMaterial& bottomMaterial = irr::video::IdentityMaterial)
		: irr::scene::ISceneNode(parent, mgr, id, position, rotation, scale)
	{
		Material[0] = frontMaterial;
		Material[1] = leftMaterial;
		Material[2] = backMaterial;
		Material[3] = rightMaterial;
		Material[4] = topMaterial;
		Material[5] = bottomMaterial;

		irr::f32 xhalf, yhalf, zhalf;
		xhalf = scale.X * 0.5f;
		yhalf = scale.Y * 0.5f;
		zhalf = scale.Z * 0.5f;

		// Front face.
		Vertices[0] = irr::video::S3DVertex(xhalf, -yhalf, zhalf,			0, 0, 0, Material[0].DiffuseColor, 0, 1);
		Vertices[1] = irr::video::S3DVertex(-xhalf, yhalf, zhalf,			0, 0, 0, Material[0].DiffuseColor, 1, 0);
		Vertices[2] = irr::video::S3DVertex(-xhalf, -yhalf, zhalf,			0, 0, 0, Material[0].DiffuseColor, 1, 1);
		Vertices[3] = irr::video::S3DVertex(xhalf, yhalf, zhalf,			0, 0, 0, Material[0].DiffuseColor, 0, 0);

		// Left face
		Vertices[4] = irr::video::S3DVertex(-xhalf, -yhalf, zhalf,			0, 0, 0, Material[1].DiffuseColor, 0, 1);
		Vertices[5] = irr::video::S3DVertex(-xhalf, yhalf, -zhalf,			0, 0, 0, Material[1].DiffuseColor, 1, 0);
		Vertices[6] = irr::video::S3DVertex(-xhalf, -yhalf, -zhalf,			0, 0, 0, Material[1].DiffuseColor, 1, 1);
		Vertices[7] = irr::video::S3DVertex(-xhalf, yhalf, zhalf,			0, 0, 0, Material[1].DiffuseColor, 0, 0);

		// Backface
		Vertices[8] = irr::video::S3DVertex(-xhalf, -yhalf, -zhalf,			0, 0, 0, Material[2].DiffuseColor, 0, 1);
		Vertices[9] = irr::video::S3DVertex(xhalf, yhalf, -zhalf,			0, 0, 0, Material[2].DiffuseColor, 1, 0);
		Vertices[10] = irr::video::S3DVertex(xhalf, -yhalf, -zhalf,			0, 0, 0, Material[2].DiffuseColor, 1, 1);
		Vertices[11] = irr::video::S3DVertex(-xhalf, yhalf, -zhalf,			0, 0, 0, Material[2].DiffuseColor, 0, 0);

		//Right face
		Vertices[12] = irr::video::S3DVertex(xhalf, -yhalf, -zhalf,			0, 0, 0, Material[3].DiffuseColor, 0, 1);
		Vertices[13] = irr::video::S3DVertex(xhalf, yhalf, zhalf,			0, 0, 0, Material[3].DiffuseColor, 1, 0);
		Vertices[14] = irr::video::S3DVertex(xhalf, -yhalf, zhalf,			0, 0, 0, Material[3].DiffuseColor, 1, 1);
		Vertices[15] = irr::video::S3DVertex(xhalf, yhalf, -zhalf,			0, 0, 0, Material[3].DiffuseColor, 0, 0);

		// Top face
		Vertices[16] = irr::video::S3DVertex( xhalf, yhalf,  zhalf,			0, 0, 0, Material[4].DiffuseColor, 0, 1);
		Vertices[17] = irr::video::S3DVertex(-xhalf, yhalf, -zhalf,			0, 0, 0, Material[4].DiffuseColor, 1, 0);
		Vertices[18] = irr::video::S3DVertex(-xhalf, yhalf,  zhalf,			0, 0, 0, Material[4].DiffuseColor, 1, 1);
		Vertices[19] = irr::video::S3DVertex( xhalf, yhalf, -zhalf,			0, 0, 0, Material[4].DiffuseColor, 0, 0);

		// Bottom face
		Vertices[20] = irr::video::S3DVertex( xhalf, -yhalf, -zhalf,		0, 0, 0, Material[5].DiffuseColor, 0, 1);
		Vertices[21] = irr::video::S3DVertex(-xhalf, -yhalf,  zhalf,		0, 0, 0, Material[5].DiffuseColor, 1, 0);
		Vertices[22] = irr::video::S3DVertex(-xhalf, -yhalf, -zhalf,		0, 0, 0, Material[5].DiffuseColor, 1, 1);
		Vertices[23] = irr::video::S3DVertex( xhalf, -yhalf,  zhalf,		0, 0, 0, Material[5].DiffuseColor, 0, 0);

		Indices[0]  =  0; Indices[1]  =  1;	Indices[2]  =  2;
		Indices[3]  =  0; Indices[4]  =  3;	Indices[5]  =  1;

		Indices[6]  =  4; Indices[7]  =  5; Indices[8]  =  6;
		Indices[9]  =  4; Indices[10] =  7; Indices[11] =  5;

		Indices[12] =  8; Indices[13] =  9; Indices[14] = 10;
		Indices[15] =  8; Indices[16] = 11; Indices[17] =  9;

		Indices[18] = 12; Indices[19] = 13; Indices[20] = 14;
		Indices[21] = 12; Indices[22] = 15; Indices[23] = 13;

		Indices[24] = 16; Indices[25] = 17; Indices[26] = 18;
		Indices[27] = 16; Indices[28] = 19; Indices[29] = 17;

		Indices[30] = 20; Indices[31] = 21; Indices[32] = 22;
		Indices[33] = 20; Indices[34] = 23; Indices[35] = 21;

		Box.reset(Vertices[0].Pos);
		for (irr::s32 i = 1; i < 24; ++i)
			Box.addInternalPoint(Vertices[i].Pos);
	}

	virtual void OnRegisterSceneNode()
	{
		if (IsVisible)
			SceneManager->registerNodeForRendering(this);

		irr::scene::ISceneNode::OnRegisterSceneNode();
	}

	virtual void render()
	{
		irr::video::IVideoDriver* driver = SceneManager->getVideoDriver();

		driver->setTransform(irr::video::ETS_WORLD, AbsoluteTransformation);

		for (size_t i = 0; i < 6; i++)
		{
			driver->setMaterial(Material[i]);
			driver->drawIndexedTriangleList(&Vertices[0], 24, &Indices[i * 6], 2);
		}
	}

	virtual const irr::core::aabbox3d<irr::f32>& getBoundingBox() const
	{
		return Box;
	}

	virtual irr::u32 getMaterialCount() const
	{
		return 6;
	}

	virtual irr::video::SMaterial& getMaterial(irr::u32 i)
	{
		return Material[i];
	}

};





}

#endif // PRIMITIVE_CUBE_HPP__