#ifndef _CONVOLVER_NODE_HPP_
#define _CONVOLVER_NODE_HPP_


#include <addon-tools.hpp>

#include "audio-node.hpp"


class ConvolverNode : public AudioNode {
	
public:
	
	// Public V8 init
	static void init(v8::Local<v8::Object> target);
	
	void _destroy();
	
	
// Methods and props
protected:
	
	ConvolverNode();
	virtual ~ConvolverNode();
	
	static Nan::Persistent<v8::FunctionTemplate> _protoConvolverNode; // for inheritance
	static Nan::Persistent<v8::Function> _ctorConvolverNode;
	
	
// System methods and props for ObjectWrap
private:
	
	static NAN_METHOD(newCtor);
	
	static NAN_METHOD(destroy);
	static NAN_GETTER(isDestroyedGetter);
	
	
	
	static NAN_GETTER(bufferGetter);
	static NAN_SETTER(bufferSetter);
	
	static NAN_GETTER(normalizeGetter);
	static NAN_SETTER(normalizeSetter);
	
	
private:
	
	bool _isDestroyed;
	
	Nan::Persistent<v8::Object> _buffer;
	bool _normalize;
	
};


#endif // _CONVOLVER_NODE_HPP_
