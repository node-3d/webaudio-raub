#ifndef _OFFLINE_AUDIO_CONTEXT_HPP_
#define _OFFLINE_AUDIO_CONTEXT_HPP_


#include <addon-tools.hpp>

#include "base-audio-context.hpp"


class OfflineAudioContext : public BaseAudioContext {
	
public:
	
	// Public V8 init
	static void init(v8::Local<v8::Object> target);
	
	// Make a new instance from C++ land
	static v8::Local<v8::Object> getNew();
	
	// Destroy an instance from C++ land
	void _destroy();
	
	
// Methods and props, available for children
protected:
	
	OfflineAudioContext();
	virtual ~OfflineAudioContext();
	
	static Nan::Persistent<v8::FunctionTemplate> _protoOfflineAudioContext;
	static Nan::Persistent<v8::Function> _ctorOfflineAudioContext;
	
	bool _isDestroyed;
	
	Nan::Persistent<v8::Function> _oncomplete;
	unsigned int _length;
	
	
// JS methods and props, available through V8 APIs
private:
	
	static NAN_METHOD(newCtor);
	
	static NAN_METHOD(destroy);
	static NAN_GETTER(isDestroyedGetter);
	
	static NAN_METHOD(startRendering);
	static NAN_METHOD(suspend);
	
	static NAN_GETTER(oncompleteGetter);
	static NAN_SETTER(oncompleteSetter);
	
	static NAN_GETTER(lengthGetter);
	
};


#endif // _OFFLINE_AUDIO_CONTEXT_HPP_
