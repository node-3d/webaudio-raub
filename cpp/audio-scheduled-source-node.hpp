#ifndef _AUDIO_SCHEDULED_SOURCE_NODE_HPP_
#define _AUDIO_SCHEDULED_SOURCE_NODE_HPP_


#include <addon-tools.hpp>

#include "audio-node.hpp"


class AudioScheduledSourceNode : public AudioNode {
	
public:
	
	// Public V8 init
	static void init(v8::Local<v8::Object> target);
	
	void _destroy();
	
	
// Methods and props, available for children
protected:
	
	AudioScheduledSourceNode();
	virtual ~AudioScheduledSourceNode();
	
	static Nan::Persistent<v8::FunctionTemplate> _protoAudioScheduledSourceNode; // for inheritance
	static Nan::Persistent<v8::Function> _ctorAudioScheduledSourceNode;
	
	bool _isDestroyed;
	
	Nan::Persistent<v8::Function> _onended;
	
	
// JS methods and props, available through V8 APIs
private:
	
	static NAN_METHOD(newCtor);
	
	static NAN_METHOD(destroy);
	static NAN_GETTER(isDestroyedGetter);
	
	static NAN_METHOD(start);
	static NAN_METHOD(stop);
	
	static NAN_GETTER(onendedGetter);
	static NAN_SETTER(onendedSetter);
	
};


#endif // _AUDIO_SCHEDULED_SOURCE_NODE_HPP_
