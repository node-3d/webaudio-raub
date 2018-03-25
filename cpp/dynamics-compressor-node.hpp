#ifndef _DYNAMICS_COMPRESSOR_NODE_HPP_
#define _DYNAMICS_COMPRESSOR_NODE_HPP_


#include <addon-tools.hpp>

#include "audio-node.hpp"


class DynamicsCompressorNode : public AudioNode {
	
public:
	
	// Public V8 init
	static void init(v8::Local<v8::Object> target);
	
	// Make a new instance from C++ land
	static v8::Local<v8::Object> getNew();
	
	// Destroy an instance from C++ land
	void _destroy();
	
	
// Methods and props, available for children
protected:
	
	DynamicsCompressorNode();
	virtual ~DynamicsCompressorNode();
	
	static Nan::Persistent<v8::FunctionTemplate> _protoDynamicsCompressorNode;
	static Nan::Persistent<v8::Function> _ctorDynamicsCompressorNode;
	
	bool _isDestroyed;
	
	Nan::Persistent<v8::Object> _threshold;
	Nan::Persistent<v8::Object> _knee;
	Nan::Persistent<v8::Object> _ratio;
	float _reduction;
	Nan::Persistent<v8::Object> _attack;
	Nan::Persistent<v8::Object> _release;
	
	
// JS methods and props, available through V8 APIs
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
	
};


#endif // _DYNAMICS_COMPRESSOR_NODE_HPP_
