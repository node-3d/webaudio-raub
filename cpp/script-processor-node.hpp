#ifndef _SCRIPT_PROCESSOR_NODE_HPP_
#define _SCRIPT_PROCESSOR_NODE_HPP_


#include <addon-tools.hpp>

#include "audio-node.hpp"


class ScriptProcessorNode : public AudioNode {
	
public:
	
	~ScriptProcessorNode();
	
	// Public V8 init
	static void init(V8_VAR_OBJ target);
	
	static bool isScriptProcessorNode(V8_VAR_OBJ obj);
	
	// Make a new instance from C++ land
	static V8_VAR_OBJ getNew();
	
	// Destroy an instance from C++ land
	void _destroy();
	
	
// Methods and props, available for children
protected:
	
	ScriptProcessorNode();
	
	static V8_STORE_FT _protoScriptProcessorNode;
	static V8_STORE_FUNC _ctorScriptProcessorNode;
	
	bool _isDestroyed;
	
	V8_STORE_FUNC _onaudioprocess;
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
