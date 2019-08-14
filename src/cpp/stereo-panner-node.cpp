
#include "stereo-panner-node.hpp"

#include "common.hpp"


// ------ Constructor and Destructor

StereoPannerNode::StereoPannerNode() :
AudioNode() {
	
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



JS_GETTER(StereoPannerNode::panGetter) { THIS_STEREO_PANNER_NODE; THIS_CHECK;
	
	RET_VALUE(__pan.Value());
	
}


// ------ System methods and props for ObjectWrap

Napi::FunctionReference StereoPannerNode::_ctorStereoPannerNode;


void StereoPannerNode::init(Napi::Env env, Napi::Object exports) {
	
	
	ACCESSOR_R(obj, isDestroyed);
	
	ACCESSOR_R(obj, pan);
	
	// -------- dynamic
	
	Nan::SetPrototypeMethod(proto, "destroy", destroy);
	
	
	
	// -------- static
	
	Napi::Function ctor = DefineClass(env, "StereoPannerNode", {
	
	});
	
	_ctorStereoPannerNode = Napi::Persistent(ctor);
	_ctorStereoPannerNode.SuppressDestruct();
	
	exports.Set("StereoPannerNode", ctor);
	
}


bool StereoPannerNode::isStereoPannerNode(Napi::Object obj) {
	return obj.InstanceOf(_ctorStereoPannerNode.Value());
}


Napi::Object StereoPannerNode::getNew() {
	
	V8_VAR_FUNC ctor = Nan::New(_ctorStereoPannerNode);
	// V8_VAR_VAL argv[] = { /* arg1, arg2, ... */ };
	return Nan::NewInstance(ctor, 0/*argc*/, nullptr/*argv*/).ToLocalChecked();
	
}


JS_METHOD(StereoPannerNode::newCtor) {
	
	CTOR_CHECK("StereoPannerNode");
	
	StereoPannerNode *stereoPannerNode = new StereoPannerNode();
	stereoPannerNode->Wrap(info.This());
	
	RET_VALUE(info.This());
	
}


JS_METHOD(StereoPannerNode::destroy) { THIS_STEREO_PANNER_NODE; THIS_CHECK;
	
	stereoPannerNode->emit("destroy");
	
	_destroy();
	
}


JS_GETTER(StereoPannerNode::isDestroyedGetter) { THIS_STEREO_PANNER_NODE;
	
	RET_BOOL(_isDestroyed);
	
}
