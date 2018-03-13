#ifndef _OSCILLATOR_NODE_HPP_
#define _OSCILLATOR_NODE_HPP_


#include <addon-tools.hpp>


class OscillatorNode : public Nan::ObjectWrap {
	
// Public V8 init
public:
	
	static void init(v8::Local<v8::Object> target);
	
	
// Public C++ methods: in-engine calls
public:
	
	
// Protected C++ methods: implementing JS calls
protected:
	
	OscillatorNode();
	virtual ~OscillatorNode();
	
	
// JS methods and props
protected:
	
	static NAN_METHOD(newCtor);
	
	static NAN_METHOD(destroy);
	
	static NAN_METHOD(setPeriodicWave);
	
	
	static NAN_GETTER(isDestroyedGetter);
	
	
	static NAN_GETTER(typeGetter);
	static NAN_SETTER(typeSetter);
	

	static NAN_GETTER(frequencyGetter);
	static NAN_SETTER(frequencySetter);
	

	static NAN_GETTER(detuneGetter);
	static NAN_SETTER(detuneSetter);
	
	
// Actual destruction-handler
private:
	
	void _destroy();
	
	
// Stored JS constructor and helpers
private:
	
	static Nan::Persistent<v8::Function> _constructor;
	
	
// This-state storage
private:
	
	bool _isDestroyed;
	
	std::string _type;
	Nan::Persistent<v8::Object> _frequency;
	Nan::Persistent<v8::Object> _detune;
	
};


#endif // _OSCILLATOR_NODE_HPP_
