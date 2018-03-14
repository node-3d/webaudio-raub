#ifndef _AUDIO_WORKLET_NODE_HPP_
#define _AUDIO_WORKLET_NODE_HPP_


#include <addon-tools.hpp>


class AudioWorkletNode : public Nan::ObjectWrap {
	
// Public V8 init
public:
	
	static void init(v8::Local<v8::Object> target);
	
	
// Public C++ methods: in-engine calls
public:
	
	
// Protected C++ methods: implementing JS calls
protected:
	
	AudioWorkletNode();
	virtual ~AudioWorkletNode();
	
	
// JS methods and props
protected:
	
	static NAN_METHOD(newCtor);
	
	static NAN_METHOD(destroy);
	
	
	
	
	static NAN_GETTER(isDestroyedGetter);
	
	
	static NAN_GETTER(parametersGetter);
	

	static NAN_GETTER(portGetter);
	

	static NAN_GETTER(onprocessorerrorGetter);
	static NAN_SETTER(onprocessorerrorSetter);
	
	
// Actual destruction-handler
private:
	
	void _destroy();
	
	
// Stored JS constructor and helpers
private:
	
	static Nan::Persistent<v8::Function> _constructor;
	
	
// This-state storage
private:
	
	bool _isDestroyed;
	
	Nan::Persistent<v8::Object> _parameters;
	Nan::Persistent<v8::Object> _port;
	Nan::Persistent<v8::Function> _onprocessorerror;
	
};


#endif // _AUDIO_WORKLET_NODE_HPP_
