#ifndef _GAIN_NODE_HPP_
#define _GAIN_NODE_HPP_


#include <addon-tools.hpp>

#include "audio-node.hpp"


class GainNode : public AudioNode {
	
public:
	
	// Public V8 init
	static void init(v8::Local<v8::Object> target);
	
	void _destroy();
	
	
// Methods and props
protected:
	
	GainNode();
	virtual ~GainNode();
	
	static Nan::Persistent<v8::FunctionTemplate> _protoGainNode; // for inheritance
	static Nan::Persistent<v8::Function> _ctorGainNode;
	
	
// System methods and props for ObjectWrap
private:
	
	static NAN_METHOD(newCtor);
	
	static NAN_METHOD(destroy);
	static NAN_GETTER(isDestroyedGetter);
	
	
	
	static NAN_GETTER(gainGetter);
	
	
private:
	
	bool _isDestroyed;
	
	Nan::Persistent<v8::Object> _gain;
	
};


#endif // _GAIN_NODE_HPP_
