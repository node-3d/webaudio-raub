#include <cstdlib>
//#include <iostream> // -> cout << "..." << endl;


#include "stereo-panner-node.hpp"


using namespace v8;
using namespace node;
using namespace std;


// ------ Aux macros

#define THIS_STEREO_PANNER_NODE                                                    \
	StereoPannerNode *stereoPannerNode = Nan::ObjectWrap::Unwrap<StereoPannerNode>(info.This());

#define THIS_CHECK                                                            \
	if (stereoPannerNode->_isDestroyed) return;

#define CACHE_CAS(CACHE, V)                                                   \
	if (stereoPannerNode->CACHE == V) {                                           \
		return;                                                               \
	}                                                                         \
	stereoPannerNode->CACHE = V;


// ------ Constructor and Destructor

StereoPannerNode::StereoPannerNode() : AudioNode() {
	
	_isDestroyed = false;
	
}


StereoPannerNode::~StereoPannerNode() {
	
	_destroy();
	
}


void StereoPannerNode::_destroy() { DES_CHECK;
	
	_isDestroyed = true;
	
	AudioNode::_destroy();
	
}


// ------ Methods and props



NAN_GETTER(StereoPannerNode::panGetter) { THIS_STEREO_PANNER_NODE; THIS_CHECK;
	
	RET_VALUE(JS_OBJ(stereoPannerNode->_pan));
	
}


// ------ System methods and props for ObjectWrap

V8_STORE_FT StereoPannerNode::_protoStereoPannerNode;
V8_STORE_FUNC StereoPannerNode::_ctorStereoPannerNode;


void StereoPannerNode::init(V8_VAR_OBJ target) {
	
	V8_VAR_FT proto = Nan::New<FunctionTemplate>(newCtor);

	// class StereoPannerNode inherits AudioNode
	V8_VAR_FT parent = Nan::New(AudioNode::_protoAudioNode);
	proto->Inherit(parent);
	
	proto->InstanceTemplate()->SetInternalFieldCount(1);
	proto->SetClassName(JS_STR("StereoPannerNode"));
	
	
	// Accessors
	V8_VAR_OT obj = proto->PrototypeTemplate();
	ACCESSOR_R(obj, isDestroyed);
	
	ACCESSOR_R(obj, pan);
	
	// -------- dynamic
	
	Nan::SetPrototypeMethod(proto, "destroy", destroy);
	
	
	
	// -------- static
	
	V8_VAR_FUNC ctor = Nan::GetFunction(proto).ToLocalChecked();
	
	_protoStereoPannerNode.Reset(proto);
	_ctorStereoPannerNode.Reset(ctor);
	
	Nan::Set(target, JS_STR("StereoPannerNode"), ctor);
	
	
}


V8_VAR_OBJ StereoPannerNode::getNew() {
	
	V8_VAR_FUNC ctor = Nan::New(_ctorStereoPannerNode);
	// V8_VAR_VAL argv[] = { /* arg1, arg2, ... */ };
	return Nan::NewInstance(ctor, 0/*argc*/, nullptr/*argv*/).ToLocalChecked();
	
}


NAN_METHOD(StereoPannerNode::newCtor) {
	
	CTOR_CHECK("StereoPannerNode");
	
	StereoPannerNode *stereoPannerNode = new StereoPannerNode();
	stereoPannerNode->Wrap(info.This());
	
	RET_VALUE(info.This());
	
}


NAN_METHOD(StereoPannerNode::destroy) { THIS_STEREO_PANNER_NODE; THIS_CHECK;
	
	stereoPannerNode->_destroy();
	
}


NAN_GETTER(StereoPannerNode::isDestroyedGetter) { THIS_STEREO_PANNER_NODE;
	
	RET_VALUE(JS_BOOL(stereoPannerNode->_isDestroyed));
	
}
