#ifndef _DELAY_NODE_HPP_
#define _DELAY_NODE_HPP_


#include <addon-tools.hpp>

#include "audio-node.hpp"


class DelayNode : public AudioNode {
	
public:
	
	// Public V8 init
	static void init(v8::Local<v8::Object> target);
	
	// Make a new instance from C++ land
	static v8::Local<v8::Object> getNew();
	
	// Destroy an instance from C++ land
	void _destroy();
	
	
// Methods and props, available for children
protected:
	
	DelayNode();
	virtual ~DelayNode();
	
	static Nan::Persistent<v8::FunctionTemplate> _protoDelayNode;
	static Nan::Persistent<v8::Function> _ctorDelayNode;
	
	bool _isDestroyed;
	
	Nan::Persistent<v8::Object> _delayTime;
	
	
// JS methods and props, available through V8 APIs
private:
	
	static NAN_METHOD(newCtor);
	
	static NAN_METHOD(destroy);
	static NAN_GETTER(isDestroyedGetter);
	
	
	
	static NAN_GETTER(delayTimeGetter);
	
};


#endif // _DELAY_NODE_HPP_
