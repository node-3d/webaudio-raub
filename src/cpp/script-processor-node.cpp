#include <cstdlib>


#include "script-processor-node.hpp"


using namespace v8;
using namespace node;
using namespace std;


// ------ Aux macros

#define THIS_SCRIPT_PROCESSOR_NODE                                                    \
	ScriptProcessorNode *scriptProcessorNode = Nan::ObjectWrap::Unwrap<ScriptProcessorNode>(info.This());

#define CACHE_CAS(CACHE, V)                                                   \
	if (this.CACHE == V) {                                           \
		return;                                                               \
	}                                                                         \
	this.CACHE = V;


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



NAN_GETTER(ScriptProcessorNode::onaudioprocessGetter) { THIS_SCRIPT_PROCESSOR_NODE; THIS_CHECK;
	
	RET_VALUE(JS_FUN(scriptProcessorNode->_onaudioprocess));
	
}

NAN_SETTER(ScriptProcessorNode::onaudioprocessSetter) { THIS_SCRIPT_PROCESSOR_NODE; THIS_CHECK; SETTER_FUN_ARG;
	
	if (Nan::New(scriptProcessorNode->_onaudioprocess) == v) {
		return;
	}
	scriptProcessorNode->_onaudioprocess.Reset(v);
	
	// TODO: may be additional actions on change?
	
	scriptProcessorNode->emit("onaudioprocess", 1, &value);
	
}


NAN_GETTER(ScriptProcessorNode::bufferSizeGetter) { THIS_SCRIPT_PROCESSOR_NODE; THIS_CHECK;
	
	RET_NUM(scriptProcessorNode->_bufferSize);
	
}


// ------ System methods and props for ObjectWrap

V8_STORE_FT ScriptProcessorNode::_protoScriptProcessorNode;
V8_STORE_FUNC ScriptProcessorNode::_ctorScriptProcessorNode;


void ScriptProcessorNode::init(Napi::Object target) {
	
	V8_VAR_FT proto = Nan::New<FunctionTemplate>(newCtor);

	// class ScriptProcessorNode inherits AudioNode
	V8_VAR_FT parent = Nan::New(AudioNode::_protoAudioNode);
	proto->Inherit(parent);
	
	proto->InstanceTemplate()->SetInternalFieldCount(1);
	proto->SetClassName(JS_STR("ScriptProcessorNode"));
	
	
	// Accessors
	V8_VAR_OT obj = proto->PrototypeTemplate();
	ACCESSOR_R(obj, isDestroyed);
	
	ACCESSOR_RW(obj, onaudioprocess);
	ACCESSOR_R(obj, bufferSize);
	
	// -------- dynamic
	
	Nan::SetPrototypeMethod(proto, "destroy", destroy);
	
	
	
	// -------- static
	
	V8_VAR_FUNC ctor = Nan::GetFunction(proto).ToLocalChecked();
	
	_protoScriptProcessorNode.Reset(proto);
	_ctorScriptProcessorNode.Reset(ctor);
	
	Nan::Set(target, JS_STR("ScriptProcessorNode"), ctor);
	
	
}


bool ScriptProcessorNode::isScriptProcessorNode(Napi::Object obj) {
	return Nan::New(_protoScriptProcessorNode)->HasInstance(obj);
}


Napi::Object ScriptProcessorNode::getNew() {
	
	V8_VAR_FUNC ctor = Nan::New(_ctorScriptProcessorNode);
	// V8_VAR_VAL argv[] = { /* arg1, arg2, ... */ };
	return Nan::NewInstance(ctor, 0/*argc*/, nullptr/*argv*/).ToLocalChecked();
	
}


NAN_METHOD(ScriptProcessorNode::newCtor) {
	
	CTOR_CHECK("ScriptProcessorNode");
	
	ScriptProcessorNode *scriptProcessorNode = new ScriptProcessorNode();
	scriptProcessorNode->Wrap(info.This());
	
	RET_VALUE(info.This());
	
}


NAN_METHOD(ScriptProcessorNode::destroy) { THIS_SCRIPT_PROCESSOR_NODE; THIS_CHECK;
	
	scriptProcessorNode->emit("destroy");
	
	scriptProcessorNode->_destroy();
	
}


NAN_GETTER(ScriptProcessorNode::isDestroyedGetter) { THIS_SCRIPT_PROCESSOR_NODE;
	
	RET_BOOL(scriptProcessorNode->_isDestroyed);
	
}
