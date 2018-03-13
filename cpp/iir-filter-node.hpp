#ifndef _IIR_FILTER_NODE_HPP_
#define _IIR_FILTER_NODE_HPP_


#include <addon-tools.hpp>


class IIRFilterNode : public Nan::ObjectWrap {
	
// Public V8 init
public:
	
	static void init(v8::Local<v8::Object> target);
	
	
// Public C++ methods: in-engine calls
public:
	
	
// Protected C++ methods: implementing JS calls
protected:
	
	IIRFilterNode();
	virtual ~IIRFilterNode();
	
	
// JS methods and props
protected:
	
	static NAN_METHOD(newCtor);
	
	static NAN_METHOD(destroy);
	
	static NAN_METHOD(getFrequencyResponse);
	
	
	static NAN_GETTER(isDestroyedGetter);
	
	
	
// Actual destruction-handler
private:
	
	void _destroy();
	
	
// Stored JS constructor and helpers
private:
	
	static Nan::Persistent<v8::Function> _constructor;
	
	
// This-state storage
private:
	
	bool _isDestroyed;
	
	
	
};


#endif // _IIR_FILTER_NODE_HPP_
