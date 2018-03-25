#ifndef _CONVOLVER_NODE_HPP_
#define _CONVOLVER_NODE_HPP_


#include <addon-tools.hpp>

#include "audio-node.hpp"


class ConvolverNode : public AudioNode {
	
public:
	
	// Public V8 init
	static void init(v8::Local<v8::Object> target);
	
	// Make a new instance from C++ land
	static v8::Local<v8::Object> getNew();
	
	// Destroy an instance from C++ land
	void _destroy();
	
	
// Methods and props, available for children
protected:
	
	ConvolverNode();
	virtual ~ConvolverNode();
	
	static Nan::Persistent<v8::FunctionTemplate> _protoConvolverNode;
	static Nan::Persistent<v8::Function> _ctorConvolverNode;
	
	bool _isDestroyed;
	
	Nan::Persistent<v8::Object> _buffer;
	bool _normalize;
	
	
// JS methods and props, available through V8 APIs
private:
	
	static NAN_METHOD(newCtor);
	
	static NAN_METHOD(destroy);
	static NAN_GETTER(isDestroyedGetter);
	
	
	
	static NAN_GETTER(bufferGetter);
	static NAN_SETTER(bufferSetter);
	
	static NAN_GETTER(normalizeGetter);
	static NAN_SETTER(normalizeSetter);
	
};


#endif // _CONVOLVER_NODE_HPP_
