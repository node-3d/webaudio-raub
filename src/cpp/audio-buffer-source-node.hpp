#ifndef _AUDIO_BUFFER_SOURCE_NODE_HPP_
#define _AUDIO_BUFFER_SOURCE_NODE_HPP_


#include "audio-scheduled-source-node.hpp"


class AudioBufferSourceNode : public AudioScheduledSourceNode {
	
public:
	
	~AudioBufferSourceNode();
	
	// Public V8 init
	static void init(Napi::Env env, Napi::Object exports);
	
	// Make a new instance from C++ land
	explicit AudioBufferSourceNode(const Napi::CallbackInfo& info);
	
	// Destroy an instance from C++ land
	void _destroy();
	
	
// Methods and props, available for children
protected:
	
	explicit AudioBufferSourceNode(Napi::Object context);
	
	static Napi::FunctionReference _ctorAudioBufferSourceNode;
	
	bool _isDestroyed;
	
	Napi::ObjectReference _buffer;
	Napi::ObjectReference _playbackRate;
	Napi::ObjectReference _detune;
	
	
// JS methods and props, available through V8 APIs
private:
	
	JS_METHOD(newCtor);
	
	JS_METHOD(destroy);
	JS_GETTER(isDestroyedGetter);
	
	JS_METHOD(start);
	
	JS_GETTER(bufferGetter);
	JS_SETTER(bufferSetter);
	
	JS_GETTER(playbackRateGetter);
	
	JS_GETTER(detuneGetter);
	
	JS_GETTER(loopGetter);
	JS_SETTER(loopSetter);
	
	JS_GETTER(loopStartGetter);
	JS_SETTER(loopStartSetter);
	
	JS_GETTER(loopEndGetter);
	JS_SETTER(loopEndSetter);
	
};


#endif // _AUDIO_BUFFER_SOURCE_NODE_HPP_
