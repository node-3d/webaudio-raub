#ifndef _AUDIO_CONTEXT_HPP_
#define _AUDIO_CONTEXT_HPP_


#include <memory>

#include <addon-tools.hpp>

namespace lab { class AudioContext; };


class AudioContext : public Nan::ObjectWrap {
	
	enum AudioContextState { Running, Suspended, Closed };
	
// Public V8 init
public:
	
	static void init(v8::Local<v8::Object> target);
	
	
// Public C++ methods: in-engine calls
public:
	
	
// Protected C++ methods: implementing JS calls
protected:
	
	AudioContext(float sampleRate = 44100.f);
	virtual ~AudioContext();
	
	
// JS methods and props
protected:
	
	static NAN_METHOD(newCtor);
	
	static NAN_METHOD(destroy);
	
	static NAN_METHOD(suspend);
	static NAN_METHOD(close);
	static NAN_METHOD(getOutputTimestamp);
	static NAN_METHOD(createMediaElementSource);
	static NAN_METHOD(createMediaStreamSource);
	static NAN_METHOD(createMediaStreamDestination);
	
	
	static NAN_GETTER(isDestroyedGetter);
	
	
	static NAN_GETTER(baseLatencyGetter);
	
	
// Actual destruction-handler
private:
	
	void _destroy();
	
	
// Stored JS constructor and helpers
private:
	
	static Nan::Persistent<v8::Function> _constructor;
	
	
// This-state storage
private:
	
	bool _isDestroyed;
	AudioContextState _state;
	
	double _baseLatency;
	
	std::unique_ptr<lab::AudioContext> _impl;
	
};


#endif // _AUDIO_CONTEXT_HPP_
