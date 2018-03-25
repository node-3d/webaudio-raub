#ifndef _OSCILLATOR_NODE_HPP_
#define _OSCILLATOR_NODE_HPP_


#include <addon-tools.hpp>

#include "audio-node.hpp"


class OscillatorNode : public AudioNode {
	
public:
	
	// Public V8 init
	static void init(v8::Local<v8::Object> target);
	
	// Make a new instance from C++ land
	static v8::Local<v8::Object> getNew(v8::Local<v8::Object> context);
	
	// Destroy an instance from C++ land
	void _destroy();
	
	
// Methods and props, available for children
protected:
	
	OscillatorNode(v8::Local<v8::Object> context, float sampleRate);
	virtual ~OscillatorNode();
	
	static Nan::Persistent<v8::FunctionTemplate> _protoOscillatorNode;
	static Nan::Persistent<v8::Function> _ctorOscillatorNode;
	
	bool _isDestroyed;
	
	std::string _type;
	Nan::Persistent<v8::Object> _frequency;
	Nan::Persistent<v8::Object> _detune;
	
	
// JS methods and props, available through V8 APIs
private:
	
	static NAN_METHOD(newCtor);
	
	static NAN_METHOD(destroy);
	static NAN_GETTER(isDestroyedGetter);
	
	static NAN_METHOD(setPeriodicWave);
	
	static NAN_GETTER(typeGetter);
	static NAN_SETTER(typeSetter);
	
	static NAN_GETTER(frequencyGetter);
	
	static NAN_GETTER(detuneGetter);
	
};


#endif // _OSCILLATOR_NODE_HPP_
