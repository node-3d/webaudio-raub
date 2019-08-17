#ifndef _BIQUAD_FILTER_NODE_HPP_
#define _BIQUAD_FILTER_NODE_HPP_


#include "common.hpp"

#include "audio-node.hpp"


class BiquadFilterNode : public Napi::ObjectWrap<BiquadFilterNode>, private CommonNode {
	
public:
	
	~BiquadFilterNode();
	explicit BiquadFilterNode(const Napi::CallbackInfo &info);
	
	static void init(Napi::Env env, Napi::Object exports);
	
	static bool isBiquadFilterNode(Napi::Object obj);
	
	// Destroy an instance from C++ land
	void _destroy();
	
	
protected:
	
	explicit BiquadFilterNode(Napi::Object context);
	
	static Napi::FunctionReference _constructor;
	
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
