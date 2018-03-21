#ifndef _AUDIO_BUFFER_SOURCE_NODE_HPP_
#define _AUDIO_BUFFER_SOURCE_NODE_HPP_


#include <addon-tools.hpp>

#include "audio-node.hpp"


class AudioBufferSourceNode : public AudioNode {
	
public:
	
	// Public V8 init
	static void init(v8::Local<v8::Object> target);
	
	void _destroy();
	
	
// Methods and props
protected:
	
	AudioBufferSourceNode();
	virtual ~AudioBufferSourceNode();
	
	static Nan::Persistent<v8::FunctionTemplate> _protoAudioBufferSourceNode; // for inheritance
	static Nan::Persistent<v8::Function> _ctorAudioBufferSourceNode;
	
	
// System methods and props for ObjectWrap
private:
	
	static NAN_METHOD(newCtor);
	
	static NAN_METHOD(destroy);
	static NAN_GETTER(isDestroyedGetter);
	
	static NAN_METHOD(start);
	
	static NAN_GETTER(bufferGetter);
	static NAN_SETTER(bufferSetter);
	
	static NAN_GETTER(playbackRateGetter);
	
	static NAN_GETTER(detuneGetter);
	
	static NAN_GETTER(loopGetter);
	static NAN_SETTER(loopSetter);
	
	static NAN_GETTER(loopStartGetter);
	static NAN_SETTER(loopStartSetter);
	
	static NAN_GETTER(loopEndGetter);
	static NAN_SETTER(loopEndSetter);
	
	
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
