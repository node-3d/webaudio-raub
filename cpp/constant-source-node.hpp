#ifndef _CONSTANT_SOURCE_NODE_HPP_
#define _CONSTANT_SOURCE_NODE_HPP_


#include <addon-tools.hpp>

#include "audio-node.hpp"


class ConstantSourceNode : public AudioNode {
	
public:
	
	// Public V8 init
	static void init(v8::Local<v8::Object> target);
	
	void _destroy();
	
	
// Methods and props, available for children
protected:
	
	ConstantSourceNode();
	virtual ~ConstantSourceNode();
	
	static Nan::Persistent<v8::FunctionTemplate> _protoConstantSourceNode; // for inheritance
	static Nan::Persistent<v8::Function> _ctorConstantSourceNode;
	
	bool _isDestroyed;
	
	Nan::Persistent<v8::Object> _offset;
	
	
// JS methods and props, available through V8 APIs
private:
	
	static NAN_METHOD(newCtor);
	
	static NAN_METHOD(destroy);
	static NAN_GETTER(isDestroyedGetter);
	
	
	
	static NAN_GETTER(offsetGetter);
	
};


#endif // _CONSTANT_SOURCE_NODE_HPP_
