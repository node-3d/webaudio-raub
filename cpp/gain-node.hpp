#ifndef _GAIN_NODE_HPP_
#define _GAIN_NODE_HPP_


#include <addon-tools.hpp>

#include "audio-node.hpp"


class GainNode : public AudioNode {
	
public:
	
	// Public V8 init
	static void init(v8::Local<v8::Object> target);
	
	// Make a new instance from C++ land
	static v8::Local<v8::Object> getNew(v8::Local<v8::Object> context);
	
	// Destroy an instance from C++ land
	void _destroy();
	
	
// Methods and props, available for children
protected:
	
	GainNode(v8::Local<v8::Object> context);
	virtual ~GainNode();
	
	static Nan::Persistent<v8::FunctionTemplate> _protoGainNode;
	static Nan::Persistent<v8::Function> _ctorGainNode;
	
	bool _isDestroyed;
	
	Nan::Persistent<v8::Object> _gain;
	
	
// JS methods and props, available through V8 APIs
private:
	
	static NAN_METHOD(newCtor);
	
	static NAN_METHOD(destroy);
	static NAN_GETTER(isDestroyedGetter);
	
	
	
	static NAN_GETTER(gainGetter);
	
};


#endif // _GAIN_NODE_HPP_
