#ifndef _AUDIO_NODE_HPP_
#define _AUDIO_NODE_HPP_


#include <event-emitter.hpp>


class AudioNode : public EventEmitter {
	
public:
	
	// Public V8 init
	static void init(v8::Local<v8::Object> target);
	
	void _destroy();
	
	
// Methods and props
protected:
	
	AudioNode();
	virtual ~AudioNode();
	
	static Nan::Persistent<v8::FunctionTemplate> _protoAudioNode; // for inheritance
	static Nan::Persistent<v8::Function> _ctorAudioNode;
	
	
// System methods and props for ObjectWrap
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
	
	
private:
	
	bool _isDestroyed;
	
	Nan::Persistent<v8::Object> _context;
	unsigned int _numberOfInputs;
	unsigned int _numberOfOutputs;
	unsigned int _channelCount;
	std::string _channelCountMode;
	std::string _channelInterpretation;
	
};


#endif // _AUDIO_NODE_HPP_
