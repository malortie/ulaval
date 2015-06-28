#ifndef HELPER_AXIS_3D_HPP__
#define HELPER_AXIS_3D_HPP__


namespace framework
{
class Helper_Axis3D : public irr::scene::ISceneNode
{
	irr::core::aabbox3d<irr::f32> Box;
	irr::video::S3DVertex Vertices[3];
	irr::video::SMaterial Material[3];

public:
	Helper_Axis3D(
		irr::scene::ISceneNode* parent,
		irr::scene::ISceneManager* mgr, 
		irr::s32 id = -1, 
		const irr::core::vector3df& position = irr::core::vector3df(0, 0, 0),
		const irr::core::vector3df& rotation = irr::core::vector3df(0, 0, 0),
		const irr::core::vector3df& scale	= irr::core::vector3df(1.0f, 1.0f, 1.0f),
		const irr::video::SColor& xcolor = irr::video::SColor(255, 255, 0, 0), 
		const irr::video::SColor& ycolor = irr::video::SColor(255, 0, 255, 0), 
		const irr::video::SColor& zcolor = irr::video::SColor(255, 0, 0, 255))
		: irr::scene::ISceneNode(parent, mgr, id, position, rotation, scale)
	{
		for (size_t i = 0; i < 3; i++)
		{
			Material[i].Wireframe = false;
			Material[i].Lighting = false;
		}

		Material[0].AmbientColor  = 
		Material[0].DiffuseColor  = 
		Material[0].EmissiveColor =
		Material[0].SpecularColor = xcolor;

		Material[1].AmbientColor  = 
		Material[1].DiffuseColor  = 
		Material[1].EmissiveColor =
		Material[1].SpecularColor = ycolor;

		Material[2].AmbientColor  = 
		Material[2].DiffuseColor  = 
		Material[2].EmissiveColor =
		Material[2].SpecularColor = zcolor;

		Vertices[0] = irr::video::S3DVertex(scale.X, 0, 0, 0, 0, 0, xcolor, 0, 0);
		Vertices[1] = irr::video::S3DVertex(0, scale.Y, 0, 0, 0, 0, ycolor, 0, 0);
		Vertices[2] = irr::video::S3DVertex(0, 0, scale.Z, 0, 0, 0, zcolor, 0, 0);

		Box.reset(Vertices[0].Pos);
		for (irr::s32 i = 1; i<3; ++i)
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
		//irr::u16 indices[] = { 0,2,3, 2,1,3, 1,0,3, 2,0,1 };
		irr::video::IVideoDriver* driver = SceneManager->getVideoDriver();

		driver->setTransform(irr::video::ETS_WORLD, AbsoluteTransformation);

		irr::core::vector3df pos = getPosition();

		for (size_t i = 0; i < 3; i++)
		{
			driver->setMaterial(Material[i]);
			driver->draw3DLine(pos, pos + Vertices[i].Pos, Material[i].EmissiveColor);
		}

		//driver->drawVertexPrimitiveList(&Vertices[0], 4, &indices[0], 4, irr::video::EVT_STANDARD, irr::scene::EPT_TRIANGLES, irr::video::EIT_16BIT);
	}

	virtual const irr::core::aabbox3d<irr::f32>& getBoundingBox() const
	{
		return Box;
	}

	virtual irr::u32 getMaterialCount() const
	{
		return 3;
	}

	virtual irr::video::SMaterial& getMaterial(irr::u32 i)
	{
		return Material[i];
	}
};

}



#endif // HELPER_AXIS_3D_HPP__