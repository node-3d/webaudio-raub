#include <cstdlib>
#include <iostream>

#include "stereo-panner-node.hpp"

using namespace v8;
using namespace node;
using namespace std;


#define THIS_STEREO_PANNER_NODE                                                    \
	StereoPannerNode *stereoPannerNode = ObjectWrap::Unwrap<StereoPannerNode>(info.This());

#define THIS_CHECK                                                            \
	if (stereoPannerNode->_isDestroyed) return;

#define DES_CHECK                                                             \
	if (_isDestroyed) return;

#define CACHE_CAS(CACHE, V)                                                   \
	if (stereoPannerNode->CACHE == V) {                                           \
		return;                                                               \
	}                                                                         \
	stereoPannerNode->CACHE = V;


Nan::Persistent<v8::Function> StereoPannerNode::_constructor;


void StereoPannerNode::init(Local<Object> target) {
	
	Local<FunctionTemplate> proto = Nan::New<FunctionTemplate>(newCtor);
	
	proto->InstanceTemplate()->SetInternalFieldCount(1);
	proto->SetClassName(JS_STR("StereoPannerNode"));
	
	
	// Accessors
	Local<ObjectTemplate> obj = proto->PrototypeTemplate();
	ACCESSOR_R(obj, isDestroyed);
	
	ACCESSOR_R(obj, pan);
	
	// -------- dynamic
	
	
	
	Nan::SetPrototypeMethod(proto, "destroy", destroy);
	
	
	
	// -------- static
	
	Local<Function> ctor = Nan::GetFunction(proto).ToLocalChecked();
	
	
	
	
	_constructor.Reset(ctor);
	Nan::Set(target, JS_STR("StereoPannerNode"), ctor);
	
	
}


NAN_METHOD(StereoPannerNode::newCtor) {
	
	CTOR_CHECK("StereoPannerNode");
	
	StereoPannerNode *stereoPannerNode = new StereoPannerNode();
	stereoPannerNode->Wrap(info.This());
	
	RET_VALUE(info.This());
	
}


StereoPannerNode::StereoPannerNode() {
	
	_isDestroyed = false;
	
}


StereoPannerNode::~StereoPannerNode() {
	
	_destroy();
	
}


void StereoPannerNode::_destroy() { DES_CHECK;
	
	_isDestroyed = true;
	
	
	
}



NAN_METHOD(StereoPannerNode::destroy) { THIS_STEREO_PANNER_NODE; THIS_CHECK;
	
	stereoPannerNode->_destroy();
	
}




NAN_GETTER(StereoPannerNode::isDestroyedGetter) { THIS_STEREO_PANNER_NODE;
	
	RET_VALUE(JS_BOOL(stereoPannerNode->_isDestroyed));
	
}


NAN_GETTER(StereoPannerNode::panGetter) { THIS_STEREO_PANNER_NODE; THIS_CHECK;
	
	RET_VALUE(JS_OBJ(stereoPannerNode->_pan));
	
}


