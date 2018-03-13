#ifndef _AUDIO_NODE_HPP_
#define _AUDIO_NODE_HPP_


#include <addon-tools.hpp>


class AudioNode : public Nan::ObjectWrap {
	
// Public V8 init
public:
	
	static void init(v8::Local<v8::Object> target);
	
	
// Public C++ methods: in-engine calls
public:
	
	
// Protected C++ methods: implementing JS calls
protected:
	
	AudioNode();
	virtual ~AudioNode();
	
	
// JS methods and props
protected:
	
	static NAN_METHOD(newCtor);
	
	static NAN_METHOD(destroy);
	
	static NAN_METHOD(connect);
	static NAN_METHOD(disconnect);
	
	
	static NAN_GETTER(isDestroyedGetter);
	
	
	static NAN_GETTER(contextGetter);
	static NAN_SETTER(contextSetter);
	

	static NAN_GETTER(numberOfInputsGetter);
	static NAN_SETTER(numberOfInputsSetter);
	

	static NAN_GETTER(numberOfOutputsGetter);
	static NAN_SETTER(numberOfOutputsSetter);
	

	static NAN_GETTER(channelCountGetter);
	static NAN_SETTER(channelCountSetter);
	

	static NAN_GETTER(channelCountModeGetter);
	static NAN_SETTER(channelCountModeSetter);
	

	static NAN_GETTER(channelInterpretationGetter);
	static NAN_SETTER(channelInterpretationSetter);
	
	
// Actual destruction-handler
private:
	
	void _destroy();
	
	
// Stored JS constructor and helpers
private:
	
	static Nan::Persistent<v8::Function> _constructor;
	
	
// This-state storage
private:
	
	bool _isDestroyed;
	
	Nan::Persistent<v8::Object> _context;
	int _numberOfInputs;
	int _numberOfOutputs;
	int _channelCount;
	std::string _channelCountMode;
	std::string _channelInterpretation;
	
};


#endif // _AUDIO_NODE_HPP_
