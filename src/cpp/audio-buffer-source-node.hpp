#ifndef _AUDIO_BUFFER_SOURCE_NODE_HPP_
#define _AUDIO_BUFFER_SOURCE_NODE_HPP_

#include "common.hpp"

#include "audio-scheduled-source-node.hpp"


class AudioBufferSourceNode : public Napi::ObjectWrap<AudioBufferSourceNode>, private CommonNode {
	
public:
	
	static void init(Napi::Env env, Napi::Object exports);
	static Napi::Object create(Napi::Env env, Napi::Object context);
	
	explicit AudioBufferSourceNode(const Napi::CallbackInfo &info);
	~AudioBufferSourceNode();
	
	void _destroy();
	
private:
	
	static Napi::FunctionReference _constructor;
	
	Napi::ObjectReference _buffer;
	Napi::ObjectReference _playbackRate;
	Napi::ObjectReference _detune;
	
	JS_METHOD(destroy);
	
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
