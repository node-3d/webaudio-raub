#ifndef _WAVE_SHAPER_NODE_HPP_
#define _WAVE_SHAPER_NODE_HPP_


#include <addon-tools.hpp>


class WaveShaperNode : public Nan::ObjectWrap {
	
// Public V8 init
public:
	
	static void init(v8::Local<v8::Object> target);
	
	
// Public C++ methods: in-engine calls
public:
	
	
// Protected C++ methods: implementing JS calls
protected:
	
	WaveShaperNode();
	virtual ~WaveShaperNode();
	
	
// JS methods and props
protected:
	
	static NAN_METHOD(newCtor);
	
	static NAN_METHOD(destroy);
	
	
	
	
	static NAN_GETTER(isDestroyedGetter);
	
	
	static NAN_GETTER(curveGetter);
	static NAN_SETTER(curveSetter);
	

	static NAN_GETTER(oversampleGetter);
	static NAN_SETTER(oversampleSetter);
	
	
// Actual destruction-handler
private:
	
	void _destroy();
	
	
// Stored JS constructor and helpers
private:
	
	static Nan::Persistent<v8::Function> _constructor;
	
	
// This-state storage
private:
	
	bool _isDestroyed;
	
	Nan::Persistent<v8::Object> _curve;
	std::string _oversample;
	
};


#endif // _WAVE_SHAPER_NODE_HPP_
