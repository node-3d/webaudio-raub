#ifndef _OSCILLATOR_NODE_HPP_
#define _OSCILLATOR_NODE_HPP_


#include <addon-tools.hpp>

#include "audio-node.hpp"


class OscillatorNode : public AudioNode {
	
public:
	
	// Public V8 init
	static void init(v8::Local<v8::Object> target);
	
	void _destroy();
	
	
// Methods and props
protected:
	
	OscillatorNode();
	virtual ~OscillatorNode();
	
	static Nan::Persistent<v8::FunctionTemplate> _protoOscillatorNode; // for inheritance
	static Nan::Persistent<v8::Function> _ctorOscillatorNode;
	
	
// System methods and props for ObjectWrap
private:
	
	static NAN_METHOD(newCtor);
	
	static NAN_METHOD(destroy);
	static NAN_GETTER(isDestroyedGetter);
	
	static NAN_METHOD(setPeriodicWave);
	
	static NAN_GETTER(typeGetter);
	static NAN_SETTER(typeSetter);
	
	static NAN_GETTER(frequencyGetter);
	
	static NAN_GETTER(detuneGetter);
	
	
private:
	
	bool _isDestroyed;
	
	std::string _type;
	Nan::Persistent<v8::Object> _frequency;
	Nan::Persistent<v8::Object> _detune;
	
};


#endif // _OSCILLATOR_NODE_HPP_
