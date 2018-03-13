#ifndef _AUDIO_SCHEDULED_SOURCE_NODE_HPP_
#define _AUDIO_SCHEDULED_SOURCE_NODE_HPP_


#include <addon-tools.hpp>


class AudioScheduledSourceNode : public Nan::ObjectWrap {
	
// Public V8 init
public:
	
	static void init(v8::Local<v8::Object> target);
	
	
// Public C++ methods: in-engine calls
public:
	
	
// Protected C++ methods: implementing JS calls
protected:
	
	AudioScheduledSourceNode();
	virtual ~AudioScheduledSourceNode();
	
	
// JS methods and props
protected:
	
	static NAN_METHOD(newCtor);
	
	static NAN_METHOD(destroy);
	
	static NAN_METHOD(start);
	static NAN_METHOD(stop);
	
	
	static NAN_GETTER(isDestroyedGetter);
	
	
	static NAN_GETTER(onendedGetter);
	static NAN_SETTER(onendedSetter);
	
	
// Actual destruction-handler
private:
	
	void _destroy();
	
	
// Stored JS constructor and helpers
private:
	
	static Nan::Persistent<v8::Function> _constructor;
	
	
// This-state storage
private:
	
	bool _isDestroyed;
	
	Nan::Persistent<v8::Function> _onended;
	
};


#endif // _AUDIO_SCHEDULED_SOURCE_NODE_HPP_
