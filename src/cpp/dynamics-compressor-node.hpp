#ifndef _DYNAMICS_COMPRESSOR_NODE_HPP_
#define _DYNAMICS_COMPRESSOR_NODE_HPP_


#include <addon-tools.hpp>

#include "audio-node.hpp"


class DynamicsCompressorNode : public AudioNode {
	
public:
	
	~DynamicsCompressorNode();
	
	// Public V8 init
	static void init(Napi::Object target);
	
	static bool isDynamicsCompressorNode(Napi::Object obj);
	
	// Make a new instance from C++ land
	static Napi::Object getNew();
	
	// Destroy an instance from C++ land
	void _destroy();
	
	
// Methods and props, available for children
protected:
	
	DynamicsCompressorNode();
	
	static V8_STORE_FT _protoDynamicsCompressorNode;
	static V8_STORE_FUNC _ctorDynamicsCompressorNode;
	
	bool _isDestroyed;
	
	V8_STORE_OBJ _threshold;
	V8_STORE_OBJ _knee;
	V8_STORE_OBJ _ratio;
	float _reduction;
	V8_STORE_OBJ _attack;
	V8_STORE_OBJ _release;
	
	
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
