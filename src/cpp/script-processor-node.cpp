
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



JS_GETTER(ScriptProcessorNode::onaudioprocessGetter) { THIS_CHECK;
	
	RET_VALUE(JS_FUN(_onaudioprocess));
	
}

JS_SETTER(ScriptProcessorNode::onaudioprocessSetter) { THIS_CHECK; SETTER_FUN_ARG;
	
	if (Nan::New(_onaudioprocess) == v) {
		return;
	}
	_onaudioprocess.Reset(v);
	
	// TODO: may be additional actions on change?
	
	emit("onaudioprocess", 1, &value);
	
}


JS_GETTER(ScriptProcessorNode::bufferSizeGetter) { THIS_CHECK;
	
	RET_NUM(_bufferSize);
	
}


// ------ System methods and props for ObjectWrap

Napi::FunctionReference ScriptProcessorNode::_ctorScriptProcessorNode;


void ScriptProcessorNode::init(Napi::Env env, Napi::Object exports) {
	
	Napi::Function ctor = DefineClass(env, "ScriptProcessorNode", {
		ACCESSOR_RW(ScriptProcessorNode, onaudioprocess),
		ACCESSOR_M(ScriptProcessorNode, destroy),
		ACCESSOR_R(ScriptProcessorNode, bufferSize),
		ACCESSOR_R(ScriptProcessorNode, isDestroyed),
	
	});
	
	_ctorScriptProcessorNode = Napi::Persistent(ctor);
	_ctorScriptProcessorNode.SuppressDestruct();
	
	exports.Set("ScriptProcessorNode", ctor);
	
}


bool ScriptProcessorNode::isScriptProcessorNode(Napi::Object obj) {
	return obj.InstanceOf(_ctorScriptProcessorNode.Value());
}


Napi::Object ScriptProcessorNode::getNew() {
	
	Napi::Function ctor = Nan::New(_ctorScriptProcessorNode);
	// Napi::Value argv[] = { /* arg1, arg2, ... */ };
	return Nan::NewInstance(ctor, 0/*argc*/, nullptr/*argv*/).ToLocalChecked();
	
}


ScriptProcessorNode::ScriptProcessorNode(const Napi::CallbackInfo &info): Napi::ObjectWrap<ScriptProcessorNode>(info) {
	
	CTOR_CHECK("ScriptProcessorNode");
	
	ScriptProcessorNode *scriptProcessorNode = new ScriptProcessorNode();
	
}


JS_METHOD(ScriptProcessorNode::destroy) { THIS_CHECK;
	
	emit("destroy");
	
	_destroy();
	
}


JS_GETTER(ScriptProcessorNode::isDestroyedGetter) { NAPI_ENV;
	
	RET_BOOL(_isDestroyed);
	
}
