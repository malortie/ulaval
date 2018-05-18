#ifndef BASIC_CAMERA_INPUT_EVENT_RECEIVER_H__
#define BASIC_CAMERA_INPUT_EVENT_RECEIVER_H__


class BasicCameraInputEventReceiver : public MyEventReceiver
{
	bool	keystates[KEY_KEY_CODES_COUNT];
	int		buttonstates;

public:
	BasicCameraInputEventReceiver(SAppContext& context) : MyEventReceiver(context)
	{
	}

protected:

	virtual void onKeyInputEvent(const SEvent::SKeyInput& event)
	{
		if (IsKeyDown(KEY_KEY_Z))
		{
			ICameraSceneNode* camera = context->device->getSceneManager()->getActiveCamera();
			ICursorControl* cursorcontrol = context->device->getCursorControl();
			
			if (camera && cursorcontrol)
			{
				camera->setInputReceiverEnabled(!camera->isInputReceiverEnabled());
				cursorcontrol->setVisible(!camera->isInputReceiverEnabled());
			}
		}
	}
};

#endif // BASIC_CAMERA_INPUT_EVENT_RECEIVER_H__