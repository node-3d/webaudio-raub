#ifndef _DELAY_NODE_HPP_
#define _DELAY_NODE_HPP_


#include <addon-tools.hpp>

#include "audio-node.hpp"


class DelayNode : public AudioNode {
	
public:
	
	// Public V8 init
	static void init(v8::Local<v8::Object> target);
	
	void _destroy();
	
	
// Methods and props
protected:
	
	DelayNode();
	virtual ~DelayNode();
	
	static Nan::Persistent<v8::FunctionTemplate> _protoDelayNode; // for inheritance
	static Nan::Persistent<v8::Function> _ctorDelayNode;
	
	
// System methods and props for ObjectWrap
private:
	
	static NAN_METHOD(newCtor);
	
	static NAN_METHOD(destroy);
	static NAN_GETTER(isDestroyedGetter);
	
	
	
	static NAN_GETTER(delayTimeGetter);
	
	
private:
	
	bool _isDestroyed;
	
	Nan::Persistent<v8::Object> _delayTime;
	
};


#endif // _DELAY_NODE_HPP_
