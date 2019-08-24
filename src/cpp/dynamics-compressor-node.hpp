#ifndef _DYNAMICS_COMPRESSOR_NODE_HPP_
#define _DYNAMICS_COMPRESSOR_NODE_HPP_


#include "common.hpp"

#include "audio-node.hpp"


class DynamicsCompressorNode : public CommonNode<DynamicsCompressorNode> {
	
public:
	
	~DynamicsCompressorNode();
	explicit DynamicsCompressorNode(const Napi::CallbackInfo &info);
	
	static void init(Napi::Env env, Napi::Object exports);
	
	static bool isDynamicsCompressorNode(Napi::Object obj);
	
	// Destroy an instance from C++ land
	void _destroy();
	
	
protected:
	
	DynamicsCompressorNode();
	
	static Napi::FunctionReference _constructor;
	
	bool _isDestroyed;
	
	Napi::ObjectReference _threshold;
	Napi::ObjectReference _knee;
	Napi::ObjectReference _ratio;
	float _reduction;
	Napi::ObjectReference _attack;
	Napi::ObjectReference _release;
	
	
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
