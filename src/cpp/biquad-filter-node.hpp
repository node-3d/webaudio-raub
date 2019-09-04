#ifndef _BIQUAD_FILTER_NODE_HPP_
#define _BIQUAD_FILTER_NODE_HPP_

#include "common.hpp"

#include "audio-node.hpp"


class BiquadFilterNode : public CommonNode<BiquadFilterNode> {
	
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
	
	JS_DECLARE_METHOD(destroy);
	
	JS_DECLARE_METHOD(getFrequencyResponse);
	
	JS_DECLARE_GETTER(type);
	JS_DECLARE_SETTER(type);
	
	JS_DECLARE_GETTER(frequency);
	
	JS_DECLARE_GETTER(detune);
	
	JS_DECLARE_GETTER(Q);
	
	JS_DECLARE_GETTER(gain);
	
};


#endif // _BIQUAD_FILTER_NODE_HPP_
