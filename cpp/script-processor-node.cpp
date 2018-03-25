#include <cstdlib>
//#include <iostream> // -> cout << "..." << endl;


#include "script-processor-node.hpp"


using namespace v8;
using namespace node;
using namespace std;


// ------ Aux macros

#define THIS_SCRIPT_PROCESSOR_NODE                                                    \
	ScriptProcessorNode *scriptProcessorNode = Nan::ObjectWrap::Unwrap<ScriptProcessorNode>(info.This());

#define THIS_CHECK                                                            \
	if (scriptProcessorNode->_isDestroyed) return;

#define CACHE_CAS(CACHE, V)                                                   \
	if (scriptProcessorNode->CACHE == V) {                                           \
		return;                                                               \
	}                                                                         \
	scriptProcessorNode->CACHE = V;


// ------ Constructor and Destructor

ScriptProcessorNode::ScriptProcessorNode() : AudioNode() {
	
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
	
	RET_VALUE(JS_INT32(scriptProcessorNode->_bufferSize));
	
}


// ------ System methods and props for ObjectWrap

Nan::Persistent<FunctionTemplate> ScriptProcessorNode::_protoScriptProcessorNode;
Nan::Persistent<Function> ScriptProcessorNode::_ctorScriptProcessorNode;


void ScriptProcessorNode::init(Local<Object> target) {
	
	Local<FunctionTemplate> proto = Nan::New<FunctionTemplate>(newCtor);
	
	// class ScriptProcessorNode inherits AudioNode
	Local<FunctionTemplate> parent = Nan::New(AudioNode::_protoAudioNode);
	proto->Inherit(parent);
	
	proto->InstanceTemplate()->SetInternalFieldCount(1);
	proto->SetClassName(JS_STR("ScriptProcessorNode"));
	
	
	// Accessors
	Local<ObjectTemplate> obj = proto->PrototypeTemplate();
	ACCESSOR_R(obj, isDestroyed);
	
	ACCESSOR_RW(obj, onaudioprocess);
	ACCESSOR_R(obj, bufferSize);
	
	// -------- dynamic
	
	Nan::SetPrototypeMethod(proto, "destroy", destroy);
	
	
	
	// -------- static
	
	Local<Function> ctor = Nan::GetFunction(proto).ToLocalChecked();
	
	_protoScriptProcessorNode.Reset(proto);
	_ctorScriptProcessorNode.Reset(ctor);
	
	Nan::Set(target, JS_STR("ScriptProcessorNode"), ctor);
	
	
}


Local<Object> ScriptProcessorNode::getNew() {
	
	Local<Function> ctor = Nan::New(_ctorScriptProcessorNode);
	// Local<Value> argv[] = { /* arg1, arg2, ... */ };
	return Nan::NewInstance(ctor, 0/*argc*/, nullptr/*argv*/).ToLocalChecked();
	
}


NAN_METHOD(ScriptProcessorNode::newCtor) {
	
	CTOR_CHECK("ScriptProcessorNode");
	
	ScriptProcessorNode *scriptProcessorNode = new ScriptProcessorNode();
	scriptProcessorNode->Wrap(info.This());
	
	RET_VALUE(info.This());
	
}


NAN_METHOD(ScriptProcessorNode::destroy) { THIS_SCRIPT_PROCESSOR_NODE; THIS_CHECK;
	
	scriptProcessorNode->_destroy();
	
}


NAN_GETTER(ScriptProcessorNode::isDestroyedGetter) { THIS_SCRIPT_PROCESSOR_NODE;
	
	RET_VALUE(JS_BOOL(scriptProcessorNode->_isDestroyed));
	
}
