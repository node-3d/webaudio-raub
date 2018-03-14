#ifndef _OFFLINE_AUDIO_CONTEXT_HPP_
#define _OFFLINE_AUDIO_CONTEXT_HPP_


#include <addon-tools.hpp>


class OfflineAudioContext : public Nan::ObjectWrap {
	
// Public V8 init
public:
	
	static void init(v8::Local<v8::Object> target);
	
	
// Public C++ methods: in-engine calls
public:
	
	
// Protected C++ methods: implementing JS calls
protected:
	
	OfflineAudioContext();
	virtual ~OfflineAudioContext();
	
	
// JS methods and props
protected:
	
	static NAN_METHOD(newCtor);
	
	static NAN_METHOD(destroy);
	
	static NAN_METHOD(startRendering);
	static NAN_METHOD(suspend);
	
	
	static NAN_GETTER(isDestroyedGetter);
	
	
	static NAN_GETTER(oncompleteGetter);
	static NAN_SETTER(oncompleteSetter);
	

	static NAN_GETTER(lengthGetter);
	
	
// Actual destruction-handler
private:
	
	void _destroy();
	
	
// Stored JS constructor and helpers
private:
	
	static Nan::Persistent<v8::Function> _constructor;
	
	
// This-state storage
private:
	
	bool _isDestroyed;
	
	Nan::Persistent<v8::Function> _oncomplete;
	unsigned int _length;
	
};


#endif // _OFFLINE_AUDIO_CONTEXT_HPP_
