#ifndef CONTEXT_PROVIDER_H__
#define CONTEXT_PROVIDER_H__


struct IContextProvider
{
	
	SAppContext* context;

	IContextProvider()
	{
		context = nullptr;
	}

	IContextProvider(SAppContext& context)
	{
		setContext(context);
	}

	~IContextProvider()
	{
		context = nullptr;
	}

	SAppContext* getContext()
	{
		return context;
	}

	void setContext(SAppContext& context)
	{
		this->context = &context;
	}
};


#endif // CONTEXT_PROVIDER_H__