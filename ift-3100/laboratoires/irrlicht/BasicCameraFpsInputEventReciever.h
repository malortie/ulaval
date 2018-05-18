#ifndef BASIC_CAMERA_FPS_INPUT_EVENT_RECEIVER_H__
#define BASIC_CAMERA_FPS_INPUT_EVENT_RECEIVER_H__


class BasicCameraFpsInputEventReceiver : public BasicCameraInputEventReceiver
{
	bool	keystates[KEY_KEY_CODES_COUNT];
	int		buttonstates;

public:
	BasicCameraFpsInputEventReceiver(SAppContext& context) : BasicCameraInputEventReceiver(context)
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
				camera->remove();
				camera = smgr->addCameraSceneNodeFPS(parent, 100.0f, 0.1f, id);
				smgr->setActiveCamera(camera);
			}
		}
	}
};

#endif // BASIC_CAMERA_FPS_INPUT_EVENT_RECEIVER_H__