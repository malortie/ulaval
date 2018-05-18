#ifndef BASIC_CAMERA_ORBIT_INPUT_EVENT_RECEIVER_H__
#define BASIC_CAMERA_ORBIT_INPUT_EVENT_RECEIVER_H__


class BasicCameraOrbitInputEventReceiver : public BasicCameraInputEventReceiver
{

public:
	BasicCameraOrbitInputEventReceiver(SAppContext& context) : BasicCameraInputEventReceiver(context)
	{
	}

protected:

	virtual void onKeyInputEvent(const SEvent::SKeyInput& event)
	{
		BasicCameraInputEventReceiver::onKeyInputEvent(event);

		if (IsKeyDown(KEY_KEY_C))
		{
			ISceneManager* smgr = context->device->getSceneManager();
			ICameraSceneNode* camera = smgr->getActiveCamera();
			
			if (camera)
			{
				int id = camera->getID();
				ISceneNode* parent = camera->getParent();
				matrix4 transform = camera->getRelativeTransformation();

				camera->remove();
				camera = smgr->addCameraSceneNodeMaya();
				smgr->setActiveCamera(camera);
				camera->getRelativeTransformation().setTranslation(transform.getTranslation());
				camera->getRelativeTransformation().setScale(transform.getScale());
				camera->getRelativeTransformation().setRotationDegrees(transform.getRotationDegrees());
			}
		}
	}
};

#endif // BASIC_CAMERA_ORBIT_INPUT_EVENT_RECEIVER_H__