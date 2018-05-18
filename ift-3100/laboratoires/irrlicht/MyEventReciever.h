#ifndef MY_EVENT_RECEIVER_H__
#define MY_EVENT_RECEIVER_H__


class MyEventReceiver : public IEventReceiver
{
protected:
	SAppContext* context;

	bool	keystates[KEY_KEY_CODES_COUNT];
	int		buttonstates;

public:
	MyEventReceiver(SAppContext& context)
	{
		this->context = &context;

		clear();
	}
	
	~MyEventReceiver()
	{
		memset(keystates, 0, sizeof(keystates));
	}

	virtual bool OnEvent(const SEvent& event)
	{
		if (event.EventType == EET_MOUSE_INPUT_EVENT){
			buttonstates = event.MouseInput.ButtonStates;

			onMouseInputEvent(event.MouseInput);
		}
		else if (event.EventType == EET_KEY_INPUT_EVENT){
			keystates[event.KeyInput.Key] = event.KeyInput.PressedDown;

			onKeyInputEvent(event.KeyInput);
		}
		else if (event.EventType == EET_GUI_EVENT)
		{
			onGUIEvent(event.GUIEvent);
		}

		return false;
	}

	bool IsKeyDown(const EKEY_CODE& code) const
	{
		return keystates[code];
	}

	bool IsleftPressed() const
	{
		return (buttonstates & EMBSM_LEFT) ?  true: false;
	}

	bool IsMiddlePressed() const
	{
		return (buttonstates & EMBSM_MIDDLE) ? true : false;
	}

	bool IsRightPressed() const
	{
		return (buttonstates & EMBSM_RIGHT) ? true : false;
	}

	void clear()
	{
		clearKeyStates();

		clearButtonState();
	}

protected:

	void clearButtonState()
	{
		buttonstates &= ~buttonstates;
	}

	void clearKeyStates()
	{
		memset(keystates, 0, sizeof(keystates));
	}

	virtual void onMouseInputEvent(const SEvent::SMouseInput& event)
	{

	}

	virtual void onKeyInputEvent(const SEvent::SKeyInput& event)
	{

	}

	virtual void onGUIEvent(const SEvent::SGUIEvent& event)
	{
		switch (event.EventType)
		{
		case EGET_ELEMENT_FOCUS_LOST:
			onElementFocusLost(event.Caller, event.Element);
			break;
		case EGET_ELEMENT_FOCUSED:
			onElementFocused(event.Caller, event.Element);
			break;
		case EGET_ELEMENT_HOVERED:
			onElementHovered(event.Caller, event.Element);
			break;
		case EGET_ELEMENT_LEFT:
			onElementLeft(event.Caller, event.Element);
			break;
		case EGET_ELEMENT_CLOSED:
			onElementClosed(event.Caller, event.Element);
			break;
		case EGET_BUTTON_CLICKED:
			onButtonClicked(event.Caller, event.Element);
			break;
		case EGET_SCROLL_BAR_CHANGED:
			onScrollbarChanged(event.Caller, event.Element);
			break;
		case EGET_CHECKBOX_CHANGED:
			onCheckboxChanged(event.Caller, event.Element);
			break;
		case EGET_LISTBOX_CHANGED:
			onListboxChanged(event.Caller, event.Element);
			break;
		case EGET_LISTBOX_SELECTED_AGAIN:
			onListboxSelectedAgain(event.Caller, event.Element);
			break;
		case EGET_FILE_SELECTED:
			onFileSelected(event.Caller, event.Element);
			break;
		case EGET_DIRECTORY_SELECTED:
			onDirectorySelected(event.Caller, event.Element);
			break;
		case EGET_FILE_CHOOSE_DIALOG_CANCELLED:
			onFileChooseDialogCancelled(event.Caller, event.Element);
			break;
		case EGET_MESSAGEBOX_YES:
			onMessageboxYes(event.Caller, event.Element);
			break;
		case EGET_MESSAGEBOX_NO:
			onMessageboxNo(event.Caller, event.Element);
			break;
		case EGET_MESSAGEBOX_OK:
			onMessageboxOk(event.Caller, event.Element);
			break;
		case EGET_MESSAGEBOX_CANCEL:
			onMessageboxCancel(event.Caller, event.Element);
			break;
		case EGET_EDITBOX_ENTER:
			onEditboxEnter(event.Caller, event.Element);
			break;
		case EGET_EDITBOX_CHANGED:
			onEditboxChanged(event.Caller, event.Element);
			break;
		case EGET_EDITBOX_MARKING_CHANGED:
			onEditboxMarkingChanged(event.Caller, event.Element);
			break;
		case EGET_TAB_CHANGED:
			onTabChanged(event.Caller, event.Element);
			break;
		case EGET_MENU_ITEM_SELECTED:
			onMenuItemSelected(event.Caller, event.Element);
			break;
		case EGET_COMBO_BOX_CHANGED:
			onComboboxChanged(event.Caller, event.Element);
			break;
		case EGET_SPINBOX_CHANGED:
			onSpinboxChanged(event.Caller, event.Element);
			break;
		case EGET_TABLE_CHANGED:
			onTableChanged(event.Caller, event.Element);
			break;
		case EGET_TABLE_HEADER_CHANGED:
			onTableHeaderChanged(event.Caller, event.Element);
			break;
		case EGET_TABLE_SELECTED_AGAIN:
			onTableSelectedAgain(event.Caller, event.Element);
			break;
		case EGET_TREEVIEW_NODE_SELECT:
			onTreeViewNodeSelect(event.Caller, event.Element);
			break;
		case EGET_TREEVIEW_NODE_EXPAND:
			onTreeViewNodeExpand(event.Caller, event.Element);
			break;
		case EGET_TREEVIEW_NODE_COLLAPSE:
			onTreeViewNodeCollapse(event.Caller, event.Element);
			break;
		default:
			break;
		}

		
	}

private:

	virtual void onElementFocusLost(IGUIElement* caller, IGUIElement* element) {}
	virtual void onElementFocused(IGUIElement* caller, IGUIElement* element) {}
	virtual void onElementHovered(IGUIElement* caller, IGUIElement* element) {}
	virtual void onElementLeft(IGUIElement* caller, IGUIElement* element) {}
	virtual void onElementClosed(IGUIElement* caller, IGUIElement* element) {}
	virtual void onButtonClicked(IGUIElement* caller, IGUIElement* element) {}
	virtual void onScrollbarChanged(IGUIElement* caller, IGUIElement* element) {}
	virtual void onCheckboxChanged(IGUIElement* caller, IGUIElement* element) {}
	virtual void onListboxChanged(IGUIElement* caller, IGUIElement* element) {}
	virtual void onListboxSelectedAgain(IGUIElement* caller, IGUIElement* element) {}
	virtual void onFileSelected(IGUIElement* caller, IGUIElement* element) {}
	virtual void onDirectorySelected(IGUIElement* caller, IGUIElement* element) {}
	virtual void onFileChooseDialogCancelled(IGUIElement* caller, IGUIElement* element) {}
	virtual void onMessageboxYes(IGUIElement* caller, IGUIElement* element) {}
	virtual void onMessageboxNo(IGUIElement* caller, IGUIElement* element) {}
	virtual void onMessageboxOk(IGUIElement* caller, IGUIElement* element) {}
	virtual void onMessageboxCancel(IGUIElement* caller, IGUIElement* element) {}
	virtual void onEditboxEnter(IGUIElement* caller, IGUIElement* element) {}
	virtual void onEditboxChanged(IGUIElement* caller, IGUIElement* element) {}
	virtual void onEditboxMarkingChanged(IGUIElement* caller, IGUIElement* element) {}
	virtual void onTabChanged(IGUIElement* caller, IGUIElement* element) {}
	virtual void onMenuItemSelected(IGUIElement* caller, IGUIElement* element) {}
	virtual void onComboboxChanged(IGUIElement* caller, IGUIElement* element) {}
	virtual void onSpinboxChanged(IGUIElement* caller, IGUIElement* element) {}
	virtual void onTableChanged(IGUIElement* caller, IGUIElement* element) {}
	virtual void onTableHeaderChanged(IGUIElement* caller, IGUIElement* element) {}
	virtual void onTableSelectedAgain(IGUIElement* caller, IGUIElement* element) {}
	virtual void onTreeViewNodeDeselect(IGUIElement* caller, IGUIElement* element) {}
	virtual void onTreeViewNodeSelect(IGUIElement* caller, IGUIElement* element) {}
	virtual void onTreeViewNodeExpand(IGUIElement* caller, IGUIElement* element) {}
	virtual void onTreeViewNodeCollapse(IGUIElement* caller, IGUIElement* element) {}

};

#endif // MY_EVENT_RECEIVER_H__