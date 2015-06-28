#ifndef HELPER_GRID_HPP__
#define HELPER_GRID_HPP__


namespace framework
{

class Helper_Grid : public irr::scene::ISceneNode
{
	irr::core::aabbox3d<irr::f32> Box;
	irr::core::dimension2d<irr::f32> TileSize;
	irr::core::dimension2d<irr::u32> TileCount;
	irr::video::SMaterial Material;
	irr::video::S3DVertex* Vertices;
	size_t VertexCount;
	bool _initiated;

public:
	Helper_Grid(
		irr::scene::ISceneNode* parent,
		irr::scene::ISceneManager* mgr, 
		irr::s32 id = -1, 
		const irr::core::vector3df& position = irr::core::vector3df(0, 0, 0),
		const irr::core::vector3df& rotation = irr::core::vector3df(0, 0, 0),
		const irr::core::vector3df& scale	 = irr::core::vector3df(1.0f, 1.0f, 1.0f),
		const irr::core::dimension2d<irr::f32>& tileSize  = irr::core::dimension2d<irr::f32>(1, 1),
		const irr::core::dimension2d<irr::u32>& tileCount = irr::core::dimension2d<irr::u32>(8, 8),
		const irr::video::SColor& color = irr::video::SColor(255, 255, 255, 255))
		: irr::scene::ISceneNode(parent, mgr, id, position, rotation, scale)
	{
		SetInitState(false);

		Material.Wireframe = false;
		Material.Lighting = false;
		Material.AmbientColor  = 
		Material.DiffuseColor  = 
		Material.EmissiveColor =
		Material.SpecularColor = color;

		Initialize(position, rotation, scale, tileSize, tileCount, color);
	}

	~Helper_Grid()
	{
		if (Vertices)
		{
			delete[] Vertices;
			Vertices = 0;
		}
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

		irr::core::vector3df pos = getPosition();

		for (size_t i = 0; i <= VertexCount - 2; i += 2)
			driver->draw3DLine(pos + Vertices[i].Pos, pos + Vertices[i + 1].Pos, Material.EmissiveColor);
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

	virtual const irr::core::dimension2d<irr::u32>& getTileCount() const
	{
		return TileCount;
	}

	virtual const irr::core::dimension2d<irr::f32>& getTileSize() const
	{
		return TileSize;
	}

private:

	void Initialize(
		const irr::core::vector3df& position,
		const irr::core::vector3df& rotation,
		const irr::core::vector3df& scale,
		const irr::core::dimension2d<irr::f32>& tileSize,
		const irr::core::dimension2d<irr::u32>& tileCount,
		const irr::video::SColor& color)
	{
		if (SetupVertices(position, rotation, scale, tileSize, tileCount, color))
		{
			ComputeBoundingBox(Vertices, VertexCount);

			SetInitState(true);
		}
		else
		{
			drop();
		}
	}

	void Destroy()
	{
		ClearVertices();

		SetInitState(false);
	}

	void ClearVertices()
	{
		if (Vertices)
		{
			delete[] Vertices;
			Vertices = 0;
		}
	}

	bool SetupVertices(
		const irr::core::vector3df& position,
		const irr::core::vector3df& rotation,
		const irr::core::vector3df& scale,
		const irr::core::dimension2d<irr::f32>& tileSize,
		const irr::core::dimension2d<irr::u32>& tileCount, 
		const irr::video::SColor& color)
	{
		if (Initiated())
		{
			return false;
		}

		TileSize  = tileSize;
		TileCount = tileCount;

		VertexCount = ( 2 * tileCount.Width + 2 * tileCount.Height ) + 4; // 4 -> Add 2 other lines (4 vertices).
		Vertices	= new irr::video::S3DVertex[ VertexCount ];

		irr::f32 halfWidth		= tileSize.Width  * (tileCount.Width  * .5f);
		irr::f32 halfHeight		= tileSize.Height * (tileCount.Height * .5f);

		irr::f32 scalarWidth	= 1.f / tileSize.Width;
		irr::f32 scalarHeight	= 1.f / tileSize.Height;

		size_t i;
		size_t index = 0;

		for (i = 0; i < tileCount.Width + 1; ++i)
		{
			Vertices[index++] = irr::video::S3DVertex((i * scalarWidth) - halfWidth, 0, -halfHeight, 0, 0, 0, color, 0, 0);
			Vertices[index++] = irr::video::S3DVertex((i * scalarWidth) - halfWidth, 0,  halfHeight, 0, 0, 0, color, 0, 0);
		}

		for (i = 0; i < tileCount.Height + 1; ++i)
		{
			Vertices[index++] = irr::video::S3DVertex(-halfWidth, 0, (i * scalarHeight) - halfHeight, 0, 0, 0, color, 0, 0);
			Vertices[index++] = irr::video::S3DVertex( halfWidth, 0, (i * scalarHeight) - halfHeight, 0, 0, 0, color, 0, 0);
		}

		return true;
	}

	void ComputeBoundingBox(irr::video::S3DVertex* vertices, const size_t& vertexCount)
	{
		Box.reset(vertices[0].Pos);
		for (irr::u32 i = 1; i < vertexCount; ++i)
			Box.addInternalPoint(vertices[i].Pos);
	}

	void SetInitState(const bool state)
	{
		_initiated = state;
	}

	const bool& Initiated() const
	{
		return _initiated;
	}

};

}



#endif // HELPER_GRID_HPP__