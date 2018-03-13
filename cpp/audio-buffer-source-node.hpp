#ifndef _AUDIO_BUFFER_SOURCE_NODE_HPP_
#define _AUDIO_BUFFER_SOURCE_NODE_HPP_


#include <addon-tools.hpp>


class AudioBufferSourceNode : public Nan::ObjectWrap {
	
// Public V8 init
public:
	
	static void init(v8::Local<v8::Object> target);
	
	
// Public C++ methods: in-engine calls
public:
	
	
// Protected C++ methods: implementing JS calls
protected:
	
	AudioBufferSourceNode();
	virtual ~AudioBufferSourceNode();
	
	
// JS methods and props
protected:
	
	static NAN_METHOD(newCtor);
	
	static NAN_METHOD(destroy);
	
	static NAN_METHOD(start);
	
	
	static NAN_GETTER(isDestroyedGetter);
	
	
	static NAN_GETTER(bufferGetter);
	static NAN_SETTER(bufferSetter);
	

	static NAN_GETTER(playbackRateGetter);
	static NAN_SETTER(playbackRateSetter);
	

	static NAN_GETTER(detuneGetter);
	static NAN_SETTER(detuneSetter);
	

	static NAN_GETTER(loopGetter);
	static NAN_SETTER(loopSetter);
	

	static NAN_GETTER(loopStartGetter);
	static NAN_SETTER(loopStartSetter);
	

	static NAN_GETTER(loopEndGetter);
	static NAN_SETTER(loopEndSetter);
	
	
// Actual destruction-handler
private:
	
	void _destroy();
	
	
// Stored JS constructor and helpers
private:
	
	static Nan::Persistent<v8::Function> _constructor;
	
	
// This-state storage
private:
	
	bool _isDestroyed;
	
	Nan::Persistent<v8::Object> _buffer;
	Nan::Persistent<v8::Object> _playbackRate;
	Nan::Persistent<v8::Object> _detune;
	bool _loop;
	double _loopStart;
	double _loopEnd;
	
};


#endif // _AUDIO_BUFFER_SOURCE_NODE_HPP_
