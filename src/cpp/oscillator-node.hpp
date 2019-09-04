#ifndef _OSCILLATOR_NODE_HPP_
#define _OSCILLATOR_NODE_HPP_


#include "common.hpp"

#include "audio-scheduled-source-node.hpp"


class OscillatorNode : public CommonNode<OscillatorNode> {
	
public:
	
	static void init(Napi::Env env, Napi::Object exports);
	static Napi::Object create(Napi::Env env, Napi::Object context);
	
	explicit OscillatorNode(const Napi::CallbackInfo &info);
	~OscillatorNode();
	
	void _destroy();
	
private:
	
	static Napi::FunctionReference _constructor;
	
	std::string _type;
	Napi::ObjectReference _frequency;
	Napi::ObjectReference _detune;
	
	JS_DECLARE_METHOD(destroy);
	
	JS_DECLARE_METHOD(setPeriodicWave);
	
	JS_DECLARE_GETTER(type);
	JS_DECLARE_SETTER(type);
	
	JS_DECLARE_GETTER(frequency);
	
	JS_DECLARE_GETTER(detune);
	
};


#endif // _OSCILLATOR_NODE_HPP_
