#ifndef _WAVE_SHAPER_NODE_HPP_
#define _WAVE_SHAPER_NODE_HPP_


#include <addon-tools.hpp>

#include "audio-node.hpp"


class WaveShaperNode : public AudioNode {
	
public:
	
	// Public V8 init
	static void init(V8_VAR_OBJ target);
	
	// Make a new instance from C++ land
	static V8_VAR_OBJ getNew();
	
	// Destroy an instance from C++ land
	void _destroy();
	
	
// Methods and props, available for children
protected:
	
	WaveShaperNode();
	virtual ~WaveShaperNode();
	
	static V8_STORE_FT _protoWaveShaperNode;
	static V8_STORE_FUNC _ctorWaveShaperNode;
	
	bool _isDestroyed;
	
	V8_STORE_OBJ _curve;
	std::string _oversample;
	
	
// JS methods and props, available through V8 APIs
private:
	
	static NAN_METHOD(newCtor);
	
	static NAN_METHOD(destroy);
	static NAN_GETTER(isDestroyedGetter);
	
	
	
	static NAN_GETTER(curveGetter);
	static NAN_SETTER(curveSetter);
	
	static NAN_GETTER(oversampleGetter);
	static NAN_SETTER(oversampleSetter);
	
};


#endif // _WAVE_SHAPER_NODE_HPP_
