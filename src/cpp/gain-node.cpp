#include <cstdlib>

#include <LabSound/core/GainNode.h>

#include "gain-node.hpp"
#include "audio-context.hpp"
#include "audio-param.hpp"


using namespace v8;
using namespace node;
using namespace std;


// ------ Aux macros

#define THIS_GAIN_NODE                                                        \
	GainNode *gainNode = Nan::ObjectWrap::Unwrap<GainNode>(info.This());

#define CACHE_CAS(CACHE, V)                                                   \
	if (this.CACHE == V) {                                               \
		return;                                                               \
	}                                                                         \
	this.CACHE = V;


// ------ Constructor and Destructor

GainNode::GainNode(Napi::Object context) :
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

V8_STORE_FT GainNode::_protoGainNode;
V8_STORE_FUNC GainNode::_ctorGainNode;


void GainNode::init(Napi::Object target) {
	
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


Napi::Object GainNode::getNew(Napi::Object context) {
	
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
	
	RET_BOOL(gainNode->_isDestroyed);
	
}
