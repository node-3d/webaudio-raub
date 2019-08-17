#ifndef _SCRIPT_PROCESSOR_NODE_HPP_
#define _SCRIPT_PROCESSOR_NODE_HPP_


#include "common.hpp"

#include "audio-node.hpp"


class ScriptProcessorNode : public Napi::ObjectWrap<ScriptProcessorNode>, private CommonNode {
	
public:
	
	~ScriptProcessorNode();
	explicit ScriptProcessorNode(const Napi::CallbackInfo &info);
	
	static void init(Napi::Env env, Napi::Object exports);
	
	static bool isScriptProcessorNode(Napi::Object obj);
	
	// Destroy an instance from C++ land
	void _destroy();
	
	
protected:
	
	ScriptProcessorNode();
	
	static Napi::FunctionReference _constructor;
	
	bool _isDestroyed;
	
	V8_STORE_FUNC _onaudioprocess;
	int _bufferSize;
	
	
private:
	
	JS_METHOD(destroy);
	JS_GETTER(isDestroyedGetter);
	
	
	
	JS_GETTER(onaudioprocessGetter);
	JS_SETTER(onaudioprocessSetter);
	
	JS_GETTER(bufferSizeGetter);
	
};


#endif // _SCRIPT_PROCESSOR_NODE_HPP_
