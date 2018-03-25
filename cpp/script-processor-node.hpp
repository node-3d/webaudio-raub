#ifndef _SCRIPT_PROCESSOR_NODE_HPP_
#define _SCRIPT_PROCESSOR_NODE_HPP_


#include <addon-tools.hpp>

#include "audio-node.hpp"


class ScriptProcessorNode : public AudioNode {
	
public:
	
	// Public V8 init
	static void init(v8::Local<v8::Object> target);
	
	// Make a new instance from C++ land
	static v8::Local<v8::Object> getNew();
	
	// Destroy an instance from C++ land
	void _destroy();
	
	
// Methods and props, available for children
protected:
	
	ScriptProcessorNode();
	virtual ~ScriptProcessorNode();
	
	static Nan::Persistent<v8::FunctionTemplate> _protoScriptProcessorNode;
	static Nan::Persistent<v8::Function> _ctorScriptProcessorNode;
	
	bool _isDestroyed;
	
	Nan::Persistent<v8::Function> _onaudioprocess;
	int _bufferSize;
	
	
// JS methods and props, available through V8 APIs
private:
	
	static NAN_METHOD(newCtor);
	
	static NAN_METHOD(destroy);
	static NAN_GETTER(isDestroyedGetter);
	
	
	
	static NAN_GETTER(onaudioprocessGetter);
	static NAN_SETTER(onaudioprocessSetter);
	
	static NAN_GETTER(bufferSizeGetter);
	
};


#endif // _SCRIPT_PROCESSOR_NODE_HPP_
