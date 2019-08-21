#ifndef _BIQUAD_FILTER_NODE_HPP_
#define _BIQUAD_FILTER_NODE_HPP_

#include "common.hpp"

#include "audio-node.hpp"


class BiquadFilterNode : public Napi::ObjectWrap<BiquadFilterNode>, private CommonNode {
	
public:
	
	static void init(Napi::Env env, Napi::Object exports);
	static Napi::Object create(Napi::Env env, Napi::Object context);
	
	explicit BiquadFilterNode(const Napi::CallbackInfo &info);
	~BiquadFilterNode();
	
	void _destroy();
	
private:
	
	static Napi::FunctionReference _constructor;
	
	std::string _type;
	Napi::ObjectReference _frequency;
	Napi::ObjectReference _detune;
	Napi::ObjectReference _Q;
	Napi::ObjectReference _gain;
	
	JS_METHOD(destroy);
	
	JS_METHOD(getFrequencyResponse);
	
	JS_GETTER(typeGetter);
	JS_SETTER(typeSetter);
	
	JS_GETTER(frequencyGetter);
	
	JS_GETTER(detuneGetter);
	
	JS_GETTER(QGetter);
	
	JS_GETTER(gainGetter);
	
};


#endif // _BIQUAD_FILTER_NODE_HPP_
