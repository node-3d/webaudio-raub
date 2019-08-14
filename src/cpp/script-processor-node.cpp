
#include "script-processor-node.hpp"

#include "common.hpp"


// ------ Constructor and Destructor

ScriptProcessorNode::ScriptProcessorNode() :
AudioNode() {
	
	_isDestroyed = false;
	
}


ScriptProcessorNode::~ScriptProcessorNode() {
	
	_destroy();
	
}


void ScriptProcessorNode::_destroy() { DES_CHECK;
	
	_isDestroyed = true;
	
	AudioNode::_destroy();
	
}


// ------ Methods and props



JS_GETTER(ScriptProcessorNode::onaudioprocessGetter) { THIS_SCRIPT_PROCESSOR_NODE; THIS_CHECK;
	
	RET_VALUE(JS_FUN(_onaudioprocess));
	
}

JS_SETTER(ScriptProcessorNode::onaudioprocessSetter) { THIS_SCRIPT_PROCESSOR_NODE; THIS_CHECK; SETTER_FUN_ARG;
	
	if (Nan::New(_onaudioprocess) == v) {
		return;
	}
	_onaudioprocess.Reset(v);
	
	// TODO: may be additional actions on change?
	
	scriptProcessorNode->emit("onaudioprocess", 1, &value);
	
}


JS_GETTER(ScriptProcessorNode::bufferSizeGetter) { THIS_SCRIPT_PROCESSOR_NODE; THIS_CHECK;
	
	RET_NUM(_bufferSize);
	
}


// ------ System methods and props for ObjectWrap

Napi::FunctionReference ScriptProcessorNode::_ctorScriptProcessorNode;


void ScriptProcessorNode::init(Napi::Env env, Napi::Object exports) {
	
	
	ACCESSOR_R(obj, isDestroyed);
	
	ACCESSOR_RW(obj, onaudioprocess);
	ACCESSOR_R(obj, bufferSize);
	
	// -------- dynamic
	
	Nan::SetPrototypeMethod(proto, "destroy", destroy);
	
	
	
	// -------- static
	
	Napi::Function ctor = DefineClass(env, "ScriptProcessorNode", {
	
	});
	
	_ctorScriptProcessorNode = Napi::Persistent(ctor);
	_ctorScriptProcessorNode.SuppressDestruct();
	
	exports.Set("ScriptProcessorNode", ctor);
	
}


bool ScriptProcessorNode::isScriptProcessorNode(Napi::Object obj) {
	return obj.InstanceOf(_ctorScriptProcessorNode.Value());
}


Napi::Object ScriptProcessorNode::getNew() {
	
	V8_VAR_FUNC ctor = Nan::New(_ctorScriptProcessorNode);
	// V8_VAR_VAL argv[] = { /* arg1, arg2, ... */ };
	return Nan::NewInstance(ctor, 0/*argc*/, nullptr/*argv*/).ToLocalChecked();
	
}


JS_METHOD(ScriptProcessorNode::newCtor) {
	
	CTOR_CHECK("ScriptProcessorNode");
	
	ScriptProcessorNode *scriptProcessorNode = new ScriptProcessorNode();
	scriptProcessorNode->Wrap(info.This());
	
	RET_VALUE(info.This());
	
}


JS_METHOD(ScriptProcessorNode::destroy) { THIS_SCRIPT_PROCESSOR_NODE; THIS_CHECK;
	
	scriptProcessorNode->emit("destroy");
	
	_destroy();
	
}


JS_GETTER(ScriptProcessorNode::isDestroyedGetter) { THIS_SCRIPT_PROCESSOR_NODE;
	
	RET_BOOL(_isDestroyed);
	
}
