#ifndef PRIMITIVE_SKYBOX_HPP__
#define PRIMITIVE_SKYBOX_HPP__

namespace framework
{ 

//
// SKYBOX
//

class Primitive_Skybox : public irr::scene::ISceneNode
{
	irr::core::aabbox3d<irr::f32> Box;
	irr::video::S3DVertex Vertices[24];
	irr::u16 Indices[36];

	irr::video::ITexture* textures[6];
	irr::video::SMaterial Material[6];

public:

	enum SkyboxSlot
	{
		Front,
		Back,
		Left,
		Right,
		Top,
		Bottom,
	};

	Primitive_Skybox(
		const irr::io::path& front,
		const irr::io::path& back,
		const irr::io::path& left,
		const irr::io::path& right,
		const irr::io::path& top,
		const irr::io::path& bottom,
		irr::scene::ISceneNode* parent,
		irr::scene::ISceneManager* mgr,
		irr::s32 id = -1,
		const irr::core::vector3df& position = irr::core::vector3df(0, 0, 0),
		const irr::core::vector3df& rotation = irr::core::vector3df(0, 0, 0),
		const irr::core::vector3df& scale = irr::core::vector3df(1.0f, 1.0f, 1.0f))
		: irr::scene::ISceneNode(parent, mgr, id, position, rotation, scale)
	{
		SetupMaterials(front, back, left, right, top, bottom);

		SetupVertices(position, rotation, scale);

		SetupIndices();

		ComputeBoundingBox(Vertices, sizeof(Vertices));
	}

	Primitive_Skybox(
		const irr::core::stringc& front,
		const irr::core::stringc& back,
		const irr::core::stringc& left,
		const irr::core::stringc& right,
		const irr::core::stringc& top,
		const irr::core::stringc& bottom,
		const irr::io::path& absolutePath = "",
		irr::scene::ISceneNode* parent = 0,
		irr::scene::ISceneManager* mgr = 0,
		irr::s32 id = -1,
		const irr::core::vector3df& position = irr::core::vector3df(0, 0, 0),
		const irr::core::vector3df& rotation = irr::core::vector3df(0, 0, 0),
		const irr::core::vector3df& scale = irr::core::vector3df(1.0f, 1.0f, 1.0f))
		: irr::scene::ISceneNode(parent, mgr, id, position, rotation, scale)
	{
		SetupMaterials(front, back, left, right, top, bottom, absolutePath);

		SetupVertices(position, rotation, scale);

		SetupIndices();

		ComputeBoundingBox(Vertices, sizeof(Vertices));
	}

	Primitive_Skybox(
		const irr::video::SMaterial& front,
		const irr::video::SMaterial& back,
		const irr::video::SMaterial& left,
		const irr::video::SMaterial& right,
		const irr::video::SMaterial& top,
		const irr::video::SMaterial& bottom,
		irr::scene::ISceneNode* parent = 0,
		irr::scene::ISceneManager* mgr = 0,
		irr::s32 id = -1,
		const irr::core::vector3df& position		= irr::core::vector3df(0, 0, 0),
		const irr::core::vector3df& rotation		= irr::core::vector3df(0, 0, 0),
		const irr::core::vector3df& scale			= irr::core::vector3df(1.0f, 1.0f, 1.0f))
		: irr::scene::ISceneNode(parent, mgr, id, position, rotation, scale)
	{
		SetupMaterials(front, back, left, right, top, bottom);

		SetupVertices(position, rotation, scale);

		SetupIndices();

		ComputeBoundingBox(Vertices, sizeof(Vertices));
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

	virtual bool SetSkyboxTexture(const size_t index, const irr::video::SMaterial& material)
	{
		if (index < 0 || index >= 6)
			return false;

		Material[index] = material;

		return true;
	}

	virtual bool SetSkyboxTexture(const size_t index, const irr::io::path& path)
	{
		irr::video::IVideoDriver* driver = SceneManager->getVideoDriver();
		irr::video::ITexture* texture = driver->getTexture(path);

		if (texture)
		{
			irr::video::SMaterial mat = irr::video::IdentityMaterial;
			mat.setFlag(irr::video::EMF_LIGHTING, false);
			mat.setTexture(0, texture);

			return SetSkyboxTexture(index, mat);
		}

		return false;
	}

	virtual void SetupMaterials(
		const irr::core::stringc& front,
		const irr::core::stringc& back,
		const irr::core::stringc& left,
		const irr::core::stringc& right,
		const irr::core::stringc& top,
		const irr::core::stringc& bottom,
		const irr::io::path& path)
	{

		irr::io::IFileSystem* fs = SceneManager->getFileSystem();
		irr::io::path newPath, tempPath, filePath;
		tempPath = path;

		bool textureIsValid = true;
		bool extraSlash = tempPath.lastChar() != '/';
		if (extraSlash)
			tempPath += '/';

		filePath = tempPath + front;

		if (!fs->existFile(front))
		{
			irr::io::path filePath, fileDir, curDir;
			irr::io::SNamedPath fileNamedPath;

			filePath = fs->getAbsolutePath(front);
			fileNamedPath = irr::io::SNamedPath(filePath);

			fileDir = fileNamedPath.getPath();
			curDir = fs->getWorkingDirectory();

			if (fileDir != curDir)
			{
				if (fs->changeWorkingDirectoryTo(fileDir))
				{
					tempPath = fileDir;
					if (extraSlash)
						tempPath += '/';

					filePath = tempPath + front;

					if (fs->existFile(front))
					{
						newPath = fileDir;
					}
					else
						textureIsValid = false;
				}
				else
					textureIsValid = false;
			}
			else
				textureIsValid = false;
		}

		if (!textureIsValid)
			return;

		SetSkyboxTexture(SkyboxSlot::Front,  newPath + front);
		SetSkyboxTexture(SkyboxSlot::Back,   newPath + back);
		SetSkyboxTexture(SkyboxSlot::Left,   newPath + left);
		SetSkyboxTexture(SkyboxSlot::Right,  newPath + right);
		SetSkyboxTexture(SkyboxSlot::Top,    newPath + top);
		SetSkyboxTexture(SkyboxSlot::Bottom, newPath + bottom);
	}

	virtual void SetupMaterials(
		const irr::video::SMaterial& front,
		const irr::video::SMaterial& back,
		const irr::video::SMaterial& left,
		const irr::video::SMaterial& right,
		const irr::video::SMaterial& top,
		const irr::video::SMaterial& bottom)
	{
		SetSkyboxTexture(SkyboxSlot::Front, front);
		SetSkyboxTexture(SkyboxSlot::Back, back);
		SetSkyboxTexture(SkyboxSlot::Left, left);
		SetSkyboxTexture(SkyboxSlot::Right, right);
		SetSkyboxTexture(SkyboxSlot::Top, top);
		SetSkyboxTexture(SkyboxSlot::Bottom, bottom);
	}

	virtual void SetupMaterials(
		const irr::io::path& front,
		const irr::io::path& back,
		const irr::io::path& left,
		const irr::io::path& right,
		const irr::io::path& top,
		const irr::io::path& bottom)
	{
		SetSkyboxTexture(SkyboxSlot::Front, front);
		SetSkyboxTexture(SkyboxSlot::Back, back);
		SetSkyboxTexture(SkyboxSlot::Left, left);
		SetSkyboxTexture(SkyboxSlot::Right, right);
		SetSkyboxTexture(SkyboxSlot::Top, top);
		SetSkyboxTexture(SkyboxSlot::Bottom, bottom);
	}


	virtual void SetupVertices(
		const irr::core::vector3df& position,
		const irr::core::vector3df& rotation,
		const irr::core::vector3df& scale)
	{
		irr::f32 xhalf, yhalf, zhalf;
		xhalf = scale.X * 0.5f;
		yhalf = scale.Y * 0.5f;
		zhalf = scale.Z * 0.5f;

		// Front face.
		Vertices[0] = irr::video::S3DVertex(xhalf, -yhalf, zhalf,			0, 0, 0, Material[0].DiffuseColor, 1, 1); // xhalf, -yhalf, zhalf
		Vertices[1] = irr::video::S3DVertex(-xhalf, yhalf, zhalf,			0, 0, 0, Material[0].DiffuseColor, 0, 0); // -xhalf, yhalf, zhalf
		Vertices[2] = irr::video::S3DVertex(xhalf, yhalf, zhalf,			0, 0, 0, Material[0].DiffuseColor, 1, 0); // -xhalf, -yhalf, zhalf
		Vertices[3] = irr::video::S3DVertex(-xhalf, -yhalf, zhalf,			0, 0, 0, Material[0].DiffuseColor, 0, 1); // xhalf, yhalf, zhalf

		// Backface
		Vertices[4] = irr::video::S3DVertex(-xhalf, -yhalf, -zhalf,			0, 0, 0, Material[2].DiffuseColor, 1, 1); // -xhalf, -yhalf, -zhalf
		Vertices[5] = irr::video::S3DVertex(xhalf, yhalf, -zhalf,			0, 0, 0, Material[2].DiffuseColor, 0, 0); // xhalf, yhalf, -zhalf
		Vertices[6] = irr::video::S3DVertex(-xhalf, yhalf, -zhalf,			0, 0, 0, Material[2].DiffuseColor, 1, 0); //  xhalf, -yhalf, -zhalf
		Vertices[7] = irr::video::S3DVertex(xhalf, -yhalf, -zhalf,			0, 0, 0, Material[2].DiffuseColor, 0, 1); // -xhalf,  yhalf, -zhalf

		// Left face
		Vertices[8] = irr::video::S3DVertex(-xhalf, -yhalf, zhalf,			0, 0, 0, Material[1].DiffuseColor, 1, 1); // -xhalf, -yhalf, zhalf
		Vertices[9] = irr::video::S3DVertex(-xhalf, yhalf, -zhalf,			0, 0, 0, Material[1].DiffuseColor, 0, 0); // -xhalf, yhalf, -zhalf
		Vertices[10] = irr::video::S3DVertex(-xhalf, yhalf, zhalf,			0, 0, 0, Material[1].DiffuseColor, 1, 0); // -xhalf, -yhalf, -zhalf
		Vertices[11] = irr::video::S3DVertex(-xhalf, -yhalf, -zhalf,		0, 0, 0, Material[1].DiffuseColor, 0, 1); // -xhalf, yhalf, zhalf

		//Right face
		Vertices[12] = irr::video::S3DVertex(xhalf, -yhalf, -zhalf,			0, 0, 0, Material[3].DiffuseColor, 1, 1); //  xhalf, -yhalf, -zhalf
		Vertices[13] = irr::video::S3DVertex(xhalf, yhalf, zhalf,			0, 0, 0, Material[3].DiffuseColor, 0, 0); //  xhalf,  yhalf,  zhalf
		Vertices[14] = irr::video::S3DVertex(xhalf, yhalf, -zhalf,			0, 0, 0, Material[3].DiffuseColor, 1, 0); //  xhalf, -yhalf,  zhalf
		Vertices[15] = irr::video::S3DVertex(xhalf, -yhalf, zhalf,			0, 0, 0, Material[3].DiffuseColor, 0, 1); //  xhalf,  yhalf, -zhalf

		// Top face
		Vertices[16] = irr::video::S3DVertex( xhalf, yhalf,  zhalf,			0, 0, 0, Material[4].DiffuseColor, 1, 1); // xhalf, yhalf,  zhalf
		Vertices[17] = irr::video::S3DVertex(-xhalf, yhalf, -zhalf,			0, 0, 0, Material[4].DiffuseColor, 0, 0); // -xhalf, yhalf, -zhalf
		Vertices[18] = irr::video::S3DVertex(xhalf, yhalf, -zhalf,			0, 0, 0, Material[4].DiffuseColor, 1, 0); // -xhalf, yhalf,  zhalf
		Vertices[19] = irr::video::S3DVertex(-xhalf, yhalf, zhalf,			0, 0, 0, Material[4].DiffuseColor, 0, 1); //  xhalf, yhalf, -zhalf

		// Bottom face
		Vertices[20] = irr::video::S3DVertex( xhalf, -yhalf, -zhalf,		0, 0, 0, Material[5].DiffuseColor, 1, 1); // xhalf, -yhalf, -zhalf
		Vertices[21] = irr::video::S3DVertex(-xhalf, -yhalf,  zhalf,		0, 0, 0, Material[5].DiffuseColor, 0, 0); // -xhalf, -yhalf,  zhalf
		Vertices[22] = irr::video::S3DVertex( xhalf, -yhalf,  zhalf,		0, 0, 0, Material[5].DiffuseColor, 1, 0); // -xhalf, -yhalf, -zhalf
		Vertices[23] = irr::video::S3DVertex(-xhalf, -yhalf, -zhalf,		0, 0, 0, Material[5].DiffuseColor, 0, 1); //  xhalf, -yhalf,  zhalf
	}

	virtual void SetupIndices()
	{
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
	}

	void ComputeBoundingBox(irr::video::S3DVertex* vertices, const size_t& vertexCount)
	{
		Box.reset(vertices[0].Pos);
		for (irr::u32 i = 1; i < vertexCount; ++i)
			Box.addInternalPoint(vertices[i].Pos);
	}
};


}

#endif // PRIMITIVE_SKYBOX_HPP__