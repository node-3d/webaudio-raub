#ifndef _DYNAMICS_COMPRESSOR_NODE_HPP_
#define _DYNAMICS_COMPRESSOR_NODE_HPP_


#include <addon-tools.hpp>

#include "audio-node.hpp"


class DynamicsCompressorNode : public AudioNode {
	
public:
	
	~DynamicsCompressorNode();
	
	// Public V8 init
	static void init(Napi::Env env, Napi::Object exports);
	
	static bool isDynamicsCompressorNode(Napi::Object obj);
	
	// Make a new instance from C++ land
	explicit DynamicsCompressorNode(const Napi::CallbackInfo& info);
	
	// Destroy an instance from C++ land
	void _destroy();
	
	
// Methods and props, available for children
protected:
	
	DynamicsCompressorNode();
	
	static Napi::FunctionReference _ctorDynamicsCompressorNode;
	
	bool _isDestroyed;
	
	Napi::ObjectReference _threshold;
	Napi::ObjectReference _knee;
	Napi::ObjectReference _ratio;
	float _reduction;
	Napi::ObjectReference _attack;
	Napi::ObjectReference _release;
	
	
// JS methods and props, available through V8 APIs
private:
	
	JS_METHOD(destroy);
	JS_GETTER(isDestroyedGetter);
	
	
	
	JS_GETTER(thresholdGetter);
	
	JS_GETTER(kneeGetter);
	
	JS_GETTER(ratioGetter);
	
	JS_GETTER(reductionGetter);
	
	JS_GETTER(attackGetter);
	
	JS_GETTER(releaseGetter);
	
};


#endif // _DYNAMICS_COMPRESSOR_NODE_HPP_
