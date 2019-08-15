#ifndef _OSCILLATOR_NODE_HPP_
#define _OSCILLATOR_NODE_HPP_


#include <addon-tools.hpp>

#include "audio-scheduled-source-node.hpp"


class OscillatorNode : public AudioScheduledSourceNode {
	
public:
	
	~OscillatorNode();
	
	// Public V8 init
	static void init(Napi::Env env, Napi::Object exports);
	
	static bool isOscillatorNode(Napi::Object obj);
	
	// Make a new instance from C++ land
	explicit OscillatorNode(const Napi::CallbackInfo& info);
	
	// Destroy an instance from C++ land
	void _destroy();
	
	
// Methods and props, available for children
protected:
	
	OscillatorNode(Napi::Object context, float sampleRate);
	
	static Napi::FunctionReference _ctorOscillatorNode;
	
	bool _isDestroyed;
	
	std::string _type;
	Napi::ObjectReference _frequency;
	Napi::ObjectReference _detune;
	
	
// JS methods and props, available through V8 APIs
private:
	
	JS_METHOD(destroy);
	JS_GETTER(isDestroyedGetter);
	
	JS_METHOD(setPeriodicWave);
	
	JS_GETTER(typeGetter);
	JS_SETTER(typeSetter);
	
	JS_GETTER(frequencyGetter);
	
	JS_GETTER(detuneGetter);
	
};


#endif // _OSCILLATOR_NODE_HPP_
