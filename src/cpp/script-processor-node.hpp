#ifndef _SCRIPT_PROCESSOR_NODE_HPP_
#define _SCRIPT_PROCESSOR_NODE_HPP_


#include "common.hpp"

#include "audio-node.hpp"


class ScriptProcessorNode : public CommonNode<ScriptProcessorNode> {
	
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
	
	JS_DECLARE_METHOD(destroy);
	JS_DECLARE_GETTER(isDestroyed);
	
	
	
	JS_DECLARE_GETTER(onaudioprocess);
	JS_DECLARE_SETTER(onaudioprocess);
	
	JS_DECLARE_GETTER(bufferSize);
	
};


#endif // _SCRIPT_PROCESSOR_NODE_HPP_
