#ifndef _BIQUAD_FILTER_NODE_HPP_
#define _BIQUAD_FILTER_NODE_HPP_


#include <addon-tools.hpp>

#include "audio-node.hpp"


class BiquadFilterNode : public Napi::ObjectWrap<BiquadFilterNode> {
	
public:
	
	~BiquadFilterNode();
	BiquadFilterNode(const Napi::CallbackInfo &info);
	
	// Public V8 init
	static void init(Napi::Env env, Napi::Object exports);
	
	static bool isBiquadFilterNode(Napi::Object obj);
	
	// Make a new instance from C++ land
	explicit BiquadFilterNode(const Napi::CallbackInfo& info);
	
	// Destroy an instance from C++ land
	void _destroy();
	
	
protected:
	
	explicit BiquadFilterNode(Napi::Object context);
	
	static Napi::FunctionReference _ctorBiquadFilterNode;
	
	bool _isDestroyed;
	
	std::string _type;
	Napi::ObjectReference _frequency;
	Napi::ObjectReference _detune;
	Napi::ObjectReference _Q;
	Napi::ObjectReference _gain;
	
	
private:
	
	JS_METHOD(destroy);
	JS_GETTER(isDestroyedGetter);
	
	JS_METHOD(getFrequencyResponse);
	
	JS_GETTER(typeGetter);
	JS_SETTER(typeSetter);
	
	JS_GETTER(frequencyGetter);
	
	JS_GETTER(detuneGetter);
	
	JS_GETTER(QGetter);
	
	JS_GETTER(gainGetter);
	
};


#endif // _BIQUAD_FILTER_NODE_HPP_
