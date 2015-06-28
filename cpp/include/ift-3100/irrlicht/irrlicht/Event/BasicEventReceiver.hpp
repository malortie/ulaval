#ifndef BASIC_EVENT_RECEIVER_HPP__
#define BASIC_EVENT_RECEIVER_HPP__

namespace framework
{

class BasicEventReceiver : public irr::IEventReceiver
{
public:
	BasicEventReceiver() {}

	virtual bool OnEvent(const irr::SEvent& event) { return false; }
};

}

#endif // BASIC_EVENT_RECEIVER_HPP__