#ifndef _IIR_FILTER_NODE_HPP_
#define _IIR_FILTER_NODE_HPP_


#include <addon-tools.hpp>

#include "audio-node.hpp"


class IIRFilterNode : public AudioNode {
	
public:
	
	// Public V8 init
	static void init(v8::Local<v8::Object> target);
	
	void _destroy();
	
	
// Methods and props
protected:
	
	IIRFilterNode();
	virtual ~IIRFilterNode();
	
	static Nan::Persistent<v8::FunctionTemplate> _protoIIRFilterNode; // for inheritance
	static Nan::Persistent<v8::Function> _ctorIIRFilterNode;
	
	
// System methods and props for ObjectWrap
private:
	
	static NAN_METHOD(newCtor);
	
	static NAN_METHOD(destroy);
	static NAN_GETTER(isDestroyedGetter);
	
	static NAN_METHOD(getFrequencyResponse);
	
	
private:
	
	bool _isDestroyed;
	
	
	
};


#endif // _IIR_FILTER_NODE_HPP_
