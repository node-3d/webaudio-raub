#ifndef _DYNAMICS_COMPRESSOR_NODE_HPP_
#define _DYNAMICS_COMPRESSOR_NODE_HPP_


#include <addon-tools.hpp>


class DynamicsCompressorNode : public Nan::ObjectWrap {
	
// Public V8 init
public:
	
	static void init(v8::Local<v8::Object> target);
	
	
// Public C++ methods: in-engine calls
public:
	
	
// Protected C++ methods: implementing JS calls
protected:
	
	DynamicsCompressorNode();
	virtual ~DynamicsCompressorNode();
	
	
// JS methods and props
protected:
	
	static NAN_METHOD(newCtor);
	
	static NAN_METHOD(destroy);
	
	
	
	
	static NAN_GETTER(isDestroyedGetter);
	
	
	static NAN_GETTER(thresholdGetter);
	

	static NAN_GETTER(kneeGetter);
	

	static NAN_GETTER(ratioGetter);
	

	static NAN_GETTER(reductionGetter);
	

	static NAN_GETTER(attackGetter);
	

	static NAN_GETTER(releaseGetter);
	
	
// Actual destruction-handler
private:
	
	void _destroy();
	
	
// Stored JS constructor and helpers
private:
	
	static Nan::Persistent<v8::Function> _constructor;
	
	
// This-state storage
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
