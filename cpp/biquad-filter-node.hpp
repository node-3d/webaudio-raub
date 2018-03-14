#ifndef _BIQUAD_FILTER_NODE_HPP_
#define _BIQUAD_FILTER_NODE_HPP_


#include <addon-tools.hpp>


class BiquadFilterNode : public Nan::ObjectWrap {
	
// Public V8 init
public:
	
	static void init(v8::Local<v8::Object> target);
	
	
// Public C++ methods: in-engine calls
public:
	
	
// Protected C++ methods: implementing JS calls
protected:
	
	BiquadFilterNode();
	virtual ~BiquadFilterNode();
	
	
// JS methods and props
protected:
	
	static NAN_METHOD(newCtor);
	
	static NAN_METHOD(destroy);
	
	static NAN_METHOD(getFrequencyResponse);
	
	
	static NAN_GETTER(isDestroyedGetter);
	
	
	static NAN_GETTER(typeGetter);
	static NAN_SETTER(typeSetter);
	

	static NAN_GETTER(frequencyGetter);
	

	static NAN_GETTER(detuneGetter);
	

	static NAN_GETTER(QGetter);
	

	static NAN_GETTER(gainGetter);
	
	
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
	Nan::Persistent<v8::Object> _Q;
	Nan::Persistent<v8::Object> _gain;
	
};


#endif // _BIQUAD_FILTER_NODE_HPP_
