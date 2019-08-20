#ifndef _OSCILLATOR_NODE_HPP_
#define _OSCILLATOR_NODE_HPP_


#include "common.hpp"

#include "audio-scheduled-source-node.hpp"


class OscillatorNode : public Napi::ObjectWrap<OscillatorNode>, private CommonNode {
	
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
	
	JS_METHOD(destroy);
	
	JS_METHOD(setPeriodicWave);
	
	JS_GETTER(typeGetter);
	JS_SETTER(typeSetter);
	
	JS_GETTER(frequencyGetter);
	
	JS_GETTER(detuneGetter);
	
};


#endif // _OSCILLATOR_NODE_HPP_
