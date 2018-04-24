#include <cstdlib>
//#include <iostream> // -> cout << "..." << endl;


#include <LabSound/core/GainNode.h>

#include "gain-node.hpp"
#include "audio-context.hpp"
#include "audio-param.hpp"


using namespace v8;
using namespace node;
using namespace std;


// ------ Aux macros

#define THIS_GAIN_NODE                                                    \
	GainNode *gainNode = Nan::ObjectWrap::Unwrap<GainNode>(info.This());

#define THIS_CHECK                                                            \
	if (gainNode->_isDestroyed) return;

#define CACHE_CAS(CACHE, V)                                                   \
	if (gainNode->CACHE == V) {                                           \
		return;                                                               \
	}                                                                         \
	gainNode->CACHE = V;


// ------ Constructor and Destructor

GainNode::GainNode(V8_VAR_OBJ context) :
AudioNode(context, NodePtr(new lab::GainNode())) {
	
	lab::GainNode *node = static_cast<lab::GainNode*>(_impl.get());
	
	_gain.Reset(AudioParam::getNew(context, node->gain()));
	
	_isDestroyed = false;
	
}


GainNode::~GainNode() {
	
	_destroy();
	
}


void GainNode::_destroy() { DES_CHECK;
	
	_gain.Reset();
	
	_isDestroyed = true;
	
	AudioNode::_destroy();
	
}


// ------ Methods and props



NAN_GETTER(GainNode::gainGetter) { THIS_GAIN_NODE; THIS_CHECK;
	
	RET_VALUE(JS_OBJ(gainNode->_gain));
	
}


// ------ System methods and props for ObjectWrap

Nan::Persistent<FunctionTemplate> GainNode::_protoGainNode;
Nan::Persistent<Function> GainNode::_ctorGainNode;


void GainNode::init(V8_VAR_OBJ target) {
	
	V8_VAR_FT proto = Nan::New<FunctionTemplate>(newCtor);
	
	// class GainNode inherits AudioNode
	V8_VAR_FT parent = Nan::New(AudioNode::_protoAudioNode);
	proto->Inherit(parent);
	
	proto->InstanceTemplate()->SetInternalFieldCount(1);
	proto->SetClassName(JS_STR("GainNode"));
	
	
	// Accessors
	V8_VAR_OT obj = proto->PrototypeTemplate();
	ACCESSOR_R(obj, isDestroyed);
	
	ACCESSOR_R(obj, gain);
	
	// -------- dynamic
	
	Nan::SetPrototypeMethod(proto, "destroy", destroy);
	
	
	
	// -------- static
	
	V8_VAR_FUNC ctor = Nan::GetFunction(proto).ToLocalChecked();
	
	_protoGainNode.Reset(proto);
	_ctorGainNode.Reset(ctor);
	
	Nan::Set(target, JS_STR("GainNode"), ctor);
	
	
}


V8_VAR_OBJ GainNode::getNew(V8_VAR_OBJ context) {
	
	V8_VAR_FUNC ctor = Nan::New(_ctorGainNode);
	V8_VAR_VAL argv[] = { context };
	return Nan::NewInstance(ctor, 1, argv).ToLocalChecked();
	
}


NAN_METHOD(GainNode::newCtor) {
	
	CTOR_CHECK("GainNode");
	
	REQ_OBJ_ARG(0, context);
	
	GainNode *gainNode = new GainNode(context);
	gainNode->Wrap(info.This());
	
	RET_VALUE(info.This());
	
}


NAN_METHOD(GainNode::destroy) { THIS_GAIN_NODE; THIS_CHECK;
	
	gainNode->emit("destroy");
	
	gainNode->_destroy();
	
}


NAN_GETTER(GainNode::isDestroyedGetter) { THIS_GAIN_NODE;
	
	RET_VALUE(JS_BOOL(gainNode->_isDestroyed));
	
}
