#ifndef _AUDIO_NODE_HPP_
#define _AUDIO_NODE_HPP_


#include <memory>

#include <event-emitter.hpp>

namespace lab { class AudioNode; };
#include <LabSound/core/AudioNode.h>


class AudioNode : public EventEmitter {
	
public:
	
	// Public V8 init
	static void init(v8::Local<v8::Object> target);
	
	// Destroy an instance from C++ land
	void _destroy();
	
	
// Methods and props, available for children
protected:
	
	AudioNode() {} // fake, TODO: remove
	AudioNode(v8::Local<v8::Object> context, lab::AudioNode *node);
	virtual ~AudioNode();
	
	static Nan::Persistent<v8::FunctionTemplate> _protoAudioNode; // for inheritance
	static Nan::Persistent<v8::Function> _ctorAudioNode;
	
	bool _isDestroyed;
	
	unsigned int _channelCount;
	std::string _channelCountMode;
	std::string _channelInterpretation;
	
	std::unique_ptr<lab::AudioNode> _impl;
	Nan::Persistent<v8::Object> _context;
	
// JS methods and props, available through V8 APIs
private:
	
	static NAN_METHOD(newCtor);
	
	static NAN_METHOD(destroy);
	static NAN_GETTER(isDestroyedGetter);
	
	static NAN_METHOD(connect);
	static NAN_METHOD(disconnect);
	
	static NAN_GETTER(contextGetter);
	
	static NAN_GETTER(numberOfInputsGetter);
	
	static NAN_GETTER(numberOfOutputsGetter);
	
	static NAN_GETTER(channelCountGetter);
	static NAN_SETTER(channelCountSetter);
	
	static NAN_GETTER(channelCountModeGetter);
	static NAN_SETTER(channelCountModeSetter);
	
	static NAN_GETTER(channelInterpretationGetter);
	static NAN_SETTER(channelInterpretationSetter);
	
};


#endif // _AUDIO_NODE_HPP_
