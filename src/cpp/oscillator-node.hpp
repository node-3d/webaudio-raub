#ifndef _OSCILLATOR_NODE_HPP_
#define _OSCILLATOR_NODE_HPP_


#include "common.hpp"

#include "audio-scheduled-source-node.hpp"


class OscillatorNode : public CommonNode<OscillatorNode> {
DECLARE_ES5_CLASS(OscillatorNode, OscillatorNode);
	
public:
	
	static void init(Napi::Env env, Napi::Object exports);
	static Napi::Object create(Napi::Env env, Napi::Object context);
	
	explicit OscillatorNode(const Napi::CallbackInfo &info);
	~OscillatorNode();
	
	void _destroy();
	
private:
	
	std::string _type;
	Napi::ObjectReference _frequency;
	Napi::ObjectReference _detune;
	
	JS_DECLARE_METHOD(OscillatorNode, destroy);
	
	JS_DECLARE_METHOD(OscillatorNode, setPeriodicWave);
	
	JS_DECLARE_GETTER(OscillatorNode, type);
	JS_DECLARE_SETTER(OscillatorNode, type);
	
	JS_DECLARE_GETTER(OscillatorNode, frequency);
	
	JS_DECLARE_GETTER(OscillatorNode, detune);
	
};


#endif // _OSCILLATOR_NODE_HPP_
