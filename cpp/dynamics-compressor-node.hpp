#ifndef _DYNAMICS_COMPRESSOR_NODE_HPP_
#define _DYNAMICS_COMPRESSOR_NODE_HPP_


#include <addon-tools.hpp>

#include "audio-node.hpp"


class DynamicsCompressorNode : public AudioNode {
	
public:
	
	// Public V8 init
	static void init(v8::Local<v8::Object> target);
	
	void _destroy();
	
	
// Methods and props
protected:
	
	DynamicsCompressorNode();
	virtual ~DynamicsCompressorNode();
	
	static Nan::Persistent<v8::FunctionTemplate> _protoDynamicsCompressorNode; // for inheritance
	static Nan::Persistent<v8::Function> _ctorDynamicsCompressorNode;
	
	
// System methods and props for ObjectWrap
private:
	
	static NAN_METHOD(newCtor);
	
	static NAN_METHOD(destroy);
	static NAN_GETTER(isDestroyedGetter);
	
	
	
	static NAN_GETTER(thresholdGetter);
	
	static NAN_GETTER(kneeGetter);
	
	static NAN_GETTER(ratioGetter);
	
	static NAN_GETTER(reductionGetter);
	
	static NAN_GETTER(attackGetter);
	
	static NAN_GETTER(releaseGetter);
	
	
private:
	
	bool _isDestroyed;
	
	Nan::Persistent<v8::Object> _threshold;
	Nan::Persistent<v8::Object> _knee;
	Nan::Persistent<v8::Object> _ratio;
	float _reduction;
	Nan::Persistent<v8::Object> _attack;
	Nan::Persistent<v8::Object> _release;
	
};


#endif // _DYNAMICS_COMPRESSOR_NODE_HPP_
