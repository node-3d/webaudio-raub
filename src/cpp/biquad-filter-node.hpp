#ifndef _BIQUAD_FILTER_NODE_HPP_
#define _BIQUAD_FILTER_NODE_HPP_


#include <addon-tools.hpp>

#include "audio-node.hpp"


class BiquadFilterNode : public AudioNode {
	
public:
	
	~BiquadFilterNode();
	
	// Public V8 init
	static void init(Napi::Object target);
	
	static bool isBiquadFilterNode(Napi::Object obj);
	
	// Make a new instance from C++ land
	static Napi::Object getNew(Napi::Object context);
	
	// Destroy an instance from C++ land
	void _destroy();
	
	
// Methods and props, available for children
protected:
	
	explicit BiquadFilterNode(Napi::Object context);
	
	static V8_STORE_FT _protoBiquadFilterNode;
	static V8_STORE_FUNC _ctorBiquadFilterNode;
	
	bool _isDestroyed;
	
	std::string _type;
	V8_STORE_OBJ _frequency;
	V8_STORE_OBJ _detune;
	V8_STORE_OBJ _Q;
	V8_STORE_OBJ _gain;
	
	
// JS methods and props, available through V8 APIs
private:
	
	static NAN_METHOD(newCtor);
	
	static NAN_METHOD(destroy);
	static NAN_GETTER(isDestroyedGetter);
	
	static NAN_METHOD(getFrequencyResponse);
	
	static NAN_GETTER(typeGetter);
	static NAN_SETTER(typeSetter);
	
	static NAN_GETTER(frequencyGetter);
	
	static NAN_GETTER(detuneGetter);
	
	static NAN_GETTER(QGetter);
	
	static NAN_GETTER(gainGetter);
	
};


#endif // _BIQUAD_FILTER_NODE_HPP_
