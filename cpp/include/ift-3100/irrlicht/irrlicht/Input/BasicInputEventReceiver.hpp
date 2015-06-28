#ifndef BASIC_INPUT_EVENT_RECEIVER_HPP__
#define BASIC_INPUT_EVENT_RECEIVER_HPP__

#include "Event/BasicEventReceiver.hpp"

namespace framework
{

enum KeyState
{
	KEY_STATE_FIRST		= 0x0,

	KEY_STATE_NONE		= 0x1,
	KEY_STATE_PRESSED	= 0x2,
	KEY_STATE_RELEASED	= 0x4,
	KEY_STATE_CLEAR		= 0x8,


	KEY_STATE_LAST		= KEY_STATE_RELEASED,
};

enum KeyModifier
{
	KEY_MOD_CONTROL = 0,
	KEY_MOD_SHIFT,

	KEY_MOD_COUNT,
};

class BasicInputEventReceiver : public BasicEventReceiver
{
	using BaseClass = BasicEventReceiver;

	irr::u8 m_keyStates[irr::KEY_KEY_CODES_COUNT];	// Normal keys.
	irr::u8 m_keyModStates[KEY_MOD_COUNT];			// Key modifiers.

public:

	BasicInputEventReceiver() : BaseClass() 
	{
		memset(m_keyStates, 0, sizeof(m_keyStates));
		memset(m_keyModStates, 0, sizeof(m_keyModStates));
	}

	virtual bool OnEvent(const irr::SEvent& event) 
	{ 
		if (event.EventType == irr::EET_KEY_INPUT_EVENT)
		{
			return OnKeyEvent(event.KeyInput);
		}
		else if (event.EventType == irr::EET_MOUSE_INPUT_EVENT)
		{
			return OnMouseEvent(event.MouseInput);
		}
		else if (event.EventType == irr::EET_JOYSTICK_INPUT_EVENT)
		{
			return OnJoystickEvent(event.JoystickEvent);
		}

		return BaseClass::OnEvent(event);
	}

	bool IsKeyDown(const irr::EKEY_CODE key) const
	{
		return ( m_keyStates[key] & KeyState::KEY_STATE_PRESSED ) ?  true: false;
	}

	bool IsKeyUp(const irr::EKEY_CODE key) const
	{
		return ( m_keyStates[key] & KeyState::KEY_STATE_RELEASED ) ? true : false;
	}

	bool IsModifierPressed(const irr::EKEY_CODE key) const
	{
		if (key == irr::EKEY_CODE::KEY_CONTROL  ||
			key == irr::EKEY_CODE::KEY_LCONTROL ||
			key == irr::EKEY_CODE::KEY_RCONTROL)
		{
			return ( m_keyModStates[KeyModifier::KEY_MOD_CONTROL] & KeyState::KEY_STATE_PRESSED ) ? true : false;
		}
		else if (key == irr::EKEY_CODE::KEY_SHIFT  ||
				 key == irr::EKEY_CODE::KEY_LSHIFT ||
				 key == irr::EKEY_CODE::KEY_RSHIFT)
		{
			return ( m_keyModStates[KeyModifier::KEY_MOD_SHIFT] & KeyState::KEY_STATE_PRESSED ) ? true : false;
		}
		else
		{
			return false;
		}
	}

	bool IsModifierUp(const irr::EKEY_CODE key) const
	{
		if (key == irr::EKEY_CODE::KEY_CONTROL  ||
			key == irr::EKEY_CODE::KEY_LCONTROL ||
			key == irr::EKEY_CODE::KEY_RCONTROL)
		{
			return ( m_keyModStates[KeyModifier::KEY_MOD_CONTROL] & KeyState::KEY_STATE_RELEASED ) ? true : false;
		}
		else if (key == irr::EKEY_CODE::KEY_SHIFT  ||
				 key == irr::EKEY_CODE::KEY_LSHIFT ||
				 key == irr::EKEY_CODE::KEY_RSHIFT)
		{
			return ( m_keyModStates[KeyModifier::KEY_MOD_SHIFT] & KeyState::KEY_STATE_RELEASED ) ? true : false;
		}
		else
		{
			return false;
		}
	}

	bool IsControlPressed() const
	{
		return ( m_keyModStates[KeyModifier::KEY_MOD_CONTROL] & KeyState::KEY_STATE_PRESSED ) ? true : false;
	}

	bool IsControlReleased() const
	{
		return ( m_keyModStates[KeyModifier::KEY_MOD_CONTROL] & KeyState::KEY_STATE_RELEASED ) ? true : false;
	}

	bool IsShiftPressed() const
	{
		return ( m_keyModStates[KeyModifier::KEY_MOD_SHIFT] & KeyState::KEY_STATE_PRESSED ) ? true : false;
	}

	bool IsShiftReleased() const
	{
		return ( m_keyModStates[KeyModifier::KEY_MOD_SHIFT] & KeyState::KEY_STATE_RELEASED ) ? true : false;
	}

	virtual void PreEvent()
	{

	}

	virtual void PostEvent()
	{
		Clear();
	}

protected:

	virtual bool OnKeyDown(wchar_t Char, irr::EKEY_CODE Key, bool Shift, bool Control)	= 0;
	virtual bool OnKeyUp(wchar_t Char, irr::EKEY_CODE Key, bool Shift, bool Control)	= 0;

	virtual bool OnLMousePressed(irr::s32 X, irr::s32 Y, irr::f32 Wheel, bool Shift, bool Control )	= 0;
	virtual bool OnLMouseLeftUp(irr::s32 X, irr::s32 Y, irr::f32 Wheel, bool Shift, bool Control)	= 0;

	virtual bool OnRMousePressed(irr::s32 X, irr::s32 Y, irr::f32 Wheel, bool Shift, bool Control)	= 0;
	virtual bool OnRMouseLeftUp(irr::s32 X, irr::s32 Y, irr::f32 Wheel, bool Shift, bool Control)	= 0;

	virtual bool OnMMousePressed(irr::s32 X, irr::s32 Y, irr::f32 Wheel, bool Shift, bool Control)	= 0;
	virtual bool OnMMouseLeftUp(irr::s32 X, irr::s32 Y, irr::f32 Wheel, bool Shift, bool Control)	= 0;

	virtual void Clear()
	{
		ClearKeyInput();
		ClearKeyModInput();
		ClearMouseInput();
		ClearJoystickInput();
	}

private:

	bool OnKeyEvent(const irr::SEvent::SKeyInput& event)
	{
		CheckKeyInput(event.Key, event.PressedDown);

		return (event.PressedDown)
			? OnKeyDown(event.Char, event.Key, event.Shift, event.Control)
			: OnKeyUp(event.Char, event.Key, event.Shift, event.Control);
	}

	bool OnMouseEvent(const irr::SEvent::SMouseInput& event)
	{
		switch (event.Event)
		{
		case irr::EMIE_LMOUSE_PRESSED_DOWN:
		case irr::EMIE_RMOUSE_PRESSED_DOWN:
		case irr::EMIE_MMOUSE_PRESSED_DOWN:
			return OnMouseDown(event);

		case irr::EMIE_LMOUSE_LEFT_UP:
		case irr::EMIE_RMOUSE_LEFT_UP:
		case irr::EMIE_MMOUSE_LEFT_UP:
			return OnMouseUp(event);

		default:
			return false;
		}
	}

	bool OnJoystickEvent(const irr::SEvent::SJoystickEvent& event)
	{
		return false;
	}

	bool OnMouseDown(const irr::SEvent::SMouseInput& event)
	{
		if (event.ButtonStates & irr::EMBSM_LEFT)
		{
			return OnLMousePressed(
				event.X,
				event.Y,
				event.Wheel,
				event.Shift,
				event.Control);
		}
		else if (event.ButtonStates & irr::EMBSM_RIGHT)
		{
			return OnRMousePressed(
				event.X,
				event.Y,
				event.Wheel,
				event.Shift,
				event.Control);
		}
		else if (event.ButtonStates & irr::EMBSM_MIDDLE)
		{
			return OnMMousePressed(
				event.X,
				event.Y,
				event.Wheel,
				event.Shift,
				event.Control);
		}
		else
		{
			return false;
		}
	}

	bool OnMouseUp(const irr::SEvent::SMouseInput& event)
	{
		if (event.ButtonStates & irr::EMBSM_LEFT)
		{
			return OnLMouseLeftUp(
				event.X, 
				event.Y, 
				event.Wheel, 
				event.Shift, 
				event.Control);
		}
		else if (event.ButtonStates & irr::EMBSM_RIGHT)
		{
			return OnRMouseLeftUp(
				event.X,
				event.Y,
				event.Wheel,
				event.Shift,
				event.Control);
		}
		else if (event.ButtonStates & irr::EMBSM_MIDDLE)
		{
			return OnMMouseLeftUp(
				event.X,
				event.Y,
				event.Wheel,
				event.Shift,
				event.Control);
		}
		else
		{
			return false;
		}
	}

	void CheckKeyInput(const irr::EKEY_CODE& Char, const bool& Pressed)
	{
		if (Pressed)
			m_keyStates[Char] = KeyState::KEY_STATE_PRESSED;
		else
			m_keyStates[Char] = KeyState::KEY_STATE_RELEASED;
	}

	void ClearKeyInput()
	{
		memset(m_keyStates, 0, sizeof(m_keyStates));
	}

	void ClearKeyModInput()
	{
		memset(m_keyModStates, 0, sizeof(m_keyModStates));
	}

	void ClearMouseInput()
	{

	}

	void ClearJoystickInput()
	{

	}
};

}

#endif // BASIC_INPUT_EVENT_RECEIVER_HPP__