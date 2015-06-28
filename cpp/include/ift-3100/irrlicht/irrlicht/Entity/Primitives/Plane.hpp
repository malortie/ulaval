#ifndef PRIMITIVE_PLANE_HPP__
#define PRIMITIVE_PLANE_HPP__

namespace framework
{

class Primitive_Plane : public irr::scene::ISceneNode
{
	irr::core::aabbox3d<irr::f32> Box;
	irr::video::S3DVertex Vertices[4];
	irr::u16 Indices[6];
	irr::video::SMaterial Material;

public:
	Primitive_Plane(
		irr::scene::ISceneNode* parent,
		irr::scene::ISceneManager* mgr, 
		irr::s32 id = -1, 
		const irr::core::vector3df& position		= irr::core::vector3df(0, 0, 0),
		const irr::core::vector3df& rotation		= irr::core::vector3df(0, 0, 0),
		const irr::core::vector3df& scale			= irr::core::vector3df(1.0f, 1.0f, 1.0f),
		const irr::video::SMaterial& material		= irr::video::IdentityMaterial)
		: irr::scene::ISceneNode(parent, mgr, id, position, rotation, scale)
	{
		Material = material;

		irr::f32 xhalf, yhalf, zhalf;
		xhalf = scale.X * 0.5f;
		yhalf = scale.Y * 0.5f;
		zhalf = scale.Z * 0.5f;

		// Front face.
		Vertices[0] = irr::video::S3DVertex(xhalf, -yhalf, 0,			0, 0, 0, Material.DiffuseColor, 0, 1);
		Vertices[1] = irr::video::S3DVertex(-xhalf, yhalf, 0,			0, 0, 0, Material.DiffuseColor, 1, 0);
		Vertices[2] = irr::video::S3DVertex(-xhalf, -yhalf, 0,			0, 0, 0, Material.DiffuseColor, 1, 1);
		Vertices[3] = irr::video::S3DVertex(xhalf, yhalf, 0,			0, 0, 0, Material.DiffuseColor, 0, 0);


		Indices[0]  =  0; Indices[1]  =  1;	Indices[2]  =  2;
		Indices[3]  =  0; Indices[4]  =  3;	Indices[5]  =  1;

		Box.reset(Vertices[0].Pos);
		for (irr::u32 i = 1; i < 24; ++i)
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
		driver->drawIndexedTriangleList(&Vertices[0], 4, &Indices[0], 2);
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

}

#endif // PRIMITIVE_PLANE_HPP__