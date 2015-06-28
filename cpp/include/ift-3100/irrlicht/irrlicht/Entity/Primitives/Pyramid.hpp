#ifndef PRIMITIVE_PYRAMID_HPP__
#define PRIMITIVE_PYRAMID_HPP__

namespace framework
{

class Primitive_Pyramid : public irr::scene::ISceneNode
{
	irr::core::aabbox3d<irr::f32> Box;
	irr::video::S3DVertex Vertices[5];
	irr::u16 Indices[9];
	irr::video::SMaterial Material;

public:
	Primitive_Pyramid(
		irr::scene::ISceneNode* parent,
		irr::scene::ISceneManager* mgr, 
		irr::s32 id = -1, 
		const irr::core::vector3df& position = irr::core::vector3df(0, 0, 0),
		const irr::core::vector3df& rotation = irr::core::vector3df(0, 0, 0),
		const irr::core::vector3df& scale	 = irr::core::vector3df(1.0f, 1.0f, 1.0f),
		const irr::video::SMaterial& material = irr::video::IdentityMaterial)
		: irr::scene::ISceneNode(parent, mgr, id, position, rotation, scale)
	{
		Material = material;

		irr::f32 xhalf, yhalf, zhalf;
		xhalf = scale.X * 0.5f;
		yhalf = scale.Y * 0.5f;
		zhalf = scale.Z * 0.5f;

#if 0
		Vertices[0] = irr::video::S3DVertex(0, yhalf, 0,				0, 0, 0, Material.DiffuseColor, 0, 0);
		Vertices[1] = irr::video::S3DVertex(xhalf, -yhalf, zhalf,		0, 0, 0, Material.DiffuseColor, 0, 0);
		Vertices[2] = irr::video::S3DVertex(-xhalf, -yhalf, zhalf,		0, 0, 0, Material.DiffuseColor, 0, 0);
		Vertices[3] = irr::video::S3DVertex(-xhalf, -yhalf, -zhalf,		0, 0, 0, Material.DiffuseColor, 0, 0);
		Vertices[4] = irr::video::S3DVertex(xhalf, -yhalf, -zhalf,		0, 0, 0, Material.DiffuseColor, 0, 0);
#else
		Vertices[0] = irr::video::S3DVertex(0, yhalf, 0,				0, 0, 0, irr::video::SColor(255, 255, 0, 0), 0, 0);
		Vertices[1] = irr::video::S3DVertex(xhalf, -yhalf, zhalf,		0, 0, 0, irr::video::SColor(255, 0, 255, 0), 0, 0);
		Vertices[2] = irr::video::S3DVertex(-xhalf, -yhalf, zhalf,		0, 0, 0, irr::video::SColor(255, 0, 0, 255), 0, 0);
		Vertices[3] = irr::video::S3DVertex(-xhalf, -yhalf, -zhalf,		0, 0, 0, irr::video::SColor(255, 255, 0, 255), 0, 0);
		Vertices[4] = irr::video::S3DVertex(xhalf, -yhalf, -zhalf,		0, 0, 0, irr::video::SColor(255, 255, 255, 0), 0, 0);
#endif

		Indices[0]  = 0;	Indices[1]  = 1;	Indices[2]  = 4;
		Indices[3]  = 3;	Indices[4]  = 2;	
		
		Indices[5]  = 1;	Indices[6] = 2;		Indices[7] = 4;
		Indices[8]  = 3;

		Box.reset(Vertices[0].Pos);
		for (irr::s32 i = 1; i < 5; ++i)
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
		driver->setMaterial(Material);

		driver->drawVertexPrimitiveList(
			&Vertices[0], 
			5,
			&Indices[0], 
			4, 
			irr::video::E_VERTEX_TYPE::EVT_STANDARD, 
			irr::scene::E_PRIMITIVE_TYPE::EPT_TRIANGLE_FAN, 
			irr::video::E_INDEX_TYPE::EIT_16BIT);

		driver->drawVertexPrimitiveList(
			&Vertices[0],
			5,
			&Indices[5],
			2, 
			irr::video::E_VERTEX_TYPE::EVT_STANDARD,
			irr::scene::E_PRIMITIVE_TYPE::EPT_TRIANGLE_STRIP,
			irr::video::E_INDEX_TYPE::EIT_16BIT);
	}

	virtual const irr::core::aabbox3d<irr::f32>& getBoundingBox() const
	{
		return Box;
	}

	virtual irr::u32 getMaterialCount() const
	{
		return 1;
	}

	virtual irr::video::SMaterial& getMaterial(irr::u32 i)
	{
		return Material;
	}

};











class Primitive_PyramidTextured : public irr::scene::ISceneNode
{
	irr::core::aabbox3d<irr::f32> Box;
	irr::video::S3DVertex Vertices[16];
	irr::u16 Indices[16];
	irr::video::SMaterial Material[5];

public:

	enum FaceSlot
	{
		Front,
		Back,
		Left,
		Right,
		Base,
	};

	Primitive_PyramidTextured(
		irr::scene::ISceneNode* parent,
		irr::scene::ISceneManager* mgr, 
		irr::s32 id = -1, 
		const irr::core::vector3df& position = irr::core::vector3df(0, 0, 0),
		const irr::core::vector3df& rotation = irr::core::vector3df(0, 0, 0),
		const irr::core::vector3df& scale	 = irr::core::vector3df(1.0f, 1.0f, 1.0f),
		const irr::video::SMaterial& frontMaterial = irr::video::IdentityMaterial,
		const irr::video::SMaterial& backMaterial  = irr::video::IdentityMaterial,
		const irr::video::SMaterial& leftMaterial  = irr::video::IdentityMaterial,
		const irr::video::SMaterial& rightMaterial = irr::video::IdentityMaterial,
		const irr::video::SMaterial& baseMaterial  = irr::video::IdentityMaterial)
		: irr::scene::ISceneNode(parent, mgr, id, position, rotation, scale)
	{
		SetupMaterials(frontMaterial, backMaterial, leftMaterial, rightMaterial, baseMaterial);

		SetupVertices(position, rotation, scale);

		SetupIndices();

		ComputeBoundingBox(Vertices, 16);
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
		driver->drawIndexedTriangleList(&Vertices[0], 16, &Indices[0], 1);

		driver->setMaterial(Material[1]);
		driver->drawIndexedTriangleList(&Vertices[0], 16, &Indices[3], 1);

		driver->setMaterial(Material[2]);
		driver->drawIndexedTriangleList(&Vertices[0], 16, &Indices[6], 1);

		driver->setMaterial(Material[3]);
		driver->drawIndexedTriangleList(&Vertices[0], 16, &Indices[9], 1);

		driver->setMaterial(Material[4]);
		driver->drawVertexPrimitiveList(
			&Vertices[0],
			16,
			&Indices[12],
			2,
			irr::video::E_VERTEX_TYPE::EVT_STANDARD,
			irr::scene::E_PRIMITIVE_TYPE::EPT_TRIANGLE_STRIP,
			irr::video::E_INDEX_TYPE::EIT_16BIT);
	}

	virtual const irr::core::aabbox3d<irr::f32>& getBoundingBox() const
	{
		return Box;
	}

	virtual irr::u32 getMaterialCount() const
	{
		return 5;
	}

	virtual irr::video::SMaterial& getMaterial(irr::u32 i)
	{
		return Material[i];
	}

	bool SetFaceTexture(const size_t index, const irr::video::SMaterial& material)
	{
		if (index < 0 || index >= 5)
			return false;

		Material[index] = material;

		return true;
	}

	void SetupMaterials(
		const irr::video::SMaterial& front, 
		const irr::video::SMaterial& back,
		const irr::video::SMaterial& left,
		const irr::video::SMaterial& right,
		const irr::video::SMaterial& base)
	{
		SetFaceTexture(FaceSlot::Front, front);
		SetFaceTexture(FaceSlot::Back,  back);
		SetFaceTexture(FaceSlot::Left,  left);
		SetFaceTexture(FaceSlot::Right, right);
		SetFaceTexture(FaceSlot::Base,  base);
	}

	void SetupVertices(
		const irr::core::vector3df& position, 
		const irr::core::vector3df& rotation, 
		const irr::core::vector3df& scale)
	{
		irr::f32 xhalf, yhalf, zhalf;
		xhalf = scale.X * 0.5f;
		yhalf = scale.Y * 0.5f;
		zhalf = scale.Z * 0.5f;

		// Front face.
		Vertices[0] = irr::video::S3DVertex(0, yhalf, 0,				0, 0, 0, Material[0].DiffuseColor, .5f, 0);
		Vertices[1] = irr::video::S3DVertex(xhalf, -yhalf, zhalf,		0, 0, 0, Material[0].DiffuseColor, 0, 1);
		Vertices[2] = irr::video::S3DVertex(-xhalf, -yhalf, zhalf,		0, 0, 0, Material[0].DiffuseColor, 1, 1);

		// Back face.
		Vertices[3] = irr::video::S3DVertex(0, yhalf, 0,				0, 0, 0, Material[1].DiffuseColor, .5f, 0);
		Vertices[4] = irr::video::S3DVertex(-xhalf, -yhalf, -zhalf,		0, 0, 0, Material[1].DiffuseColor, 0, 1);
		Vertices[5] = irr::video::S3DVertex(xhalf, -yhalf, -zhalf,		0, 0, 0, Material[1].DiffuseColor, 1, 1);

		// Left face.
		Vertices[6] = irr::video::S3DVertex(0, yhalf, 0,				0, 0, 0, Material[2].DiffuseColor, .5f, 0);
		Vertices[7] = irr::video::S3DVertex(-xhalf, -yhalf, zhalf,		0, 0, 0, Material[2].DiffuseColor, 0, 1);
		Vertices[8] = irr::video::S3DVertex(-xhalf, -yhalf, -zhalf,		0, 0, 0, Material[2].DiffuseColor, 1, 1);

		// Right face.
		Vertices[9] = irr::video::S3DVertex(0, yhalf, 0,				0, 0, 0, Material[3].DiffuseColor, .5f, 0);
		Vertices[10] = irr::video::S3DVertex(xhalf, -yhalf, -zhalf,		0, 0, 0, Material[3].DiffuseColor, 0, 1);
		Vertices[11] = irr::video::S3DVertex(xhalf, -yhalf, zhalf,		0, 0, 0, Material[3].DiffuseColor, 1, 1);

		// Bottom face.
		Vertices[12]  = irr::video::S3DVertex(xhalf, -yhalf, zhalf,		0, 0, 0, Material[4].DiffuseColor, 0, 0);
		Vertices[13] = irr::video::S3DVertex(-xhalf, -yhalf, zhalf,		0, 0, 0, Material[4].DiffuseColor, 1, 0);
		Vertices[14] = irr::video::S3DVertex(-xhalf, -yhalf, -zhalf,	0, 0, 0, Material[4].DiffuseColor, 1, 1);
		Vertices[15] = irr::video::S3DVertex(xhalf, -yhalf, -zhalf,		0, 0, 0, Material[4].DiffuseColor, 0, 1);

	}

	void SetupIndices()
	{
		Indices[0]  = 0;	Indices[1]  = 2;	Indices[2]  = 1;
		Indices[3]  = 3;	Indices[4]  = 5;	Indices[5]  = 4;
		
		Indices[6]  = 6;	Indices[7]   = 8;	Indices[8]   = 7;
		Indices[9]  = 9;	Indices[10]  = 11;	Indices[11]  = 10;

		Indices[12]  = 12;	Indices[13]  = 13;	Indices[14]  = 15; Indices[15]  = 14;
	}

	void ComputeBoundingBox(irr::video::S3DVertex* vertices, const size_t vertexCount)
	{
		Box.reset(vertices[0].Pos);
		for (irr::u32 i = 1; i < vertexCount; ++i)
			Box.addInternalPoint(vertices[i].Pos);
	}

};

}




#endif // PRIMITIVE_PYRAMID_HPP__