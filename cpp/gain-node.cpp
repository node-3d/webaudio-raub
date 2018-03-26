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

GainNode::GainNode(Local<Object> context) :
AudioNode(context, shared_ptr<lab::AudioNode>(new lab::GainNode())) {
	
	lab::GainNode *node = static_cast<lab::GainNode*>(_impl.get());
	
	_gain.Reset(AudioParam::getNew(context, node->gain()));
	
	_isDestroyed = false;
	
}


GainNode::~GainNode() {
	
	_destroy();
	
}


void GainNode::_destroy() { DES_CHECK;
	
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


void GainNode::init(Local<Object> target) {
	
	Local<FunctionTemplate> proto = Nan::New<FunctionTemplate>(newCtor);
	
	// class GainNode inherits AudioNode
	Local<FunctionTemplate> parent = Nan::New(AudioNode::_protoAudioNode);
	proto->Inherit(parent);
	
	proto->InstanceTemplate()->SetInternalFieldCount(1);
	proto->SetClassName(JS_STR("GainNode"));
	
	
	// Accessors
	Local<ObjectTemplate> obj = proto->PrototypeTemplate();
	ACCESSOR_R(obj, isDestroyed);
	
	ACCESSOR_R(obj, gain);
	
	// -------- dynamic
	
	Nan::SetPrototypeMethod(proto, "destroy", destroy);
	
	
	
	// -------- static
	
	Local<Function> ctor = Nan::GetFunction(proto).ToLocalChecked();
	
	_protoGainNode.Reset(proto);
	_ctorGainNode.Reset(ctor);
	
	Nan::Set(target, JS_STR("GainNode"), ctor);
	
	
}


Local<Object> GainNode::getNew(v8::Local<v8::Object> context) {
	
	Local<Function> ctor = Nan::New(_ctorGainNode);
	Local<Value> argv[] = { context };
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
	
	gainNode->_destroy();
	
}


NAN_GETTER(GainNode::isDestroyedGetter) { THIS_GAIN_NODE;
	
	RET_VALUE(JS_BOOL(gainNode->_isDestroyed));
	
}
