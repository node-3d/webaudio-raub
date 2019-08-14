
#include "media-stream-audio-source-node.hpp"

#include "common.hpp"


// ------ Constructor and Destructor

MediaStreamAudioSourceNode::MediaStreamAudioSourceNode() :
AudioNode() {
	
	_isDestroyed = false;
	
}


MediaStreamAudioSourceNode::~MediaStreamAudioSourceNode() {
	
	_destroy();
	
}


void MediaStreamAudioSourceNode::_destroy() { DES_CHECK;
	
	_isDestroyed = true;
	
	AudioNode::_destroy();
	
}


// ------ Methods and props



JS_GETTER(MediaStreamAudioSourceNode::mediaStreamGetter) { THIS_MEDIA_STREAM_AUDIO_SOURCE_NODE; THIS_CHECK;
	
	RET_VALUE(__mediaStream.Value());
	
}


// ------ System methods and props for ObjectWrap

Napi::FunctionReference MediaStreamAudioSourceNode::_ctorMediaStreamAudioSourceNode;


void MediaStreamAudioSourceNode::init(Napi::Env env, Napi::Object exports) {
	
	
	ACCESSOR_R(obj, isDestroyed);
	
	ACCESSOR_R(obj, mediaStream);
	
	// -------- dynamic
	
	Nan::SetPrototypeMethod(proto, "destroy", destroy);
	
	
	
	// -------- static
	
	Napi::Function ctor = DefineClass(env, "MediaStreamAudioSourceNode", {
	
	});
	
	_ctorMediaStreamAudioSourceNode = Napi::Persistent(ctor);
	_ctorMediaStreamAudioSourceNode.SuppressDestruct();
	
	exports.Set("MediaStreamAudioSourceNode", ctor);
	
}


bool MediaStreamAudioSourceNode::isMediaStreamAudioSourceNode(Napi::Object obj) {
	return obj.InstanceOf(_ctorMediaStreamAudioSourceNode.Value());
}


Napi::Object MediaStreamAudioSourceNode::getNew() {
	
	V8_VAR_FUNC ctor = Nan::New(_ctorMediaStreamAudioSourceNode);
	// V8_VAR_VAL argv[] = { /* arg1, arg2, ... */ };
	return Nan::NewInstance(ctor, 0/*argc*/, nullptr/*argv*/).ToLocalChecked();
	
}


JS_METHOD(MediaStreamAudioSourceNode::newCtor) {
	
	CTOR_CHECK("MediaStreamAudioSourceNode");
	
	MediaStreamAudioSourceNode *mediaStreamAudioSourceNode = new MediaStreamAudioSourceNode();
	mediaStreamAudioSourceNode->Wrap(info.This());
	
	RET_VALUE(info.This());
	
}


JS_METHOD(MediaStreamAudioSourceNode::destroy) { THIS_MEDIA_STREAM_AUDIO_SOURCE_NODE; THIS_CHECK;
	
	mediaStreamAudioSourceNode->emit("destroy");
	
	_destroy();
	
}


JS_GETTER(MediaStreamAudioSourceNode::isDestroyedGetter) { THIS_MEDIA_STREAM_AUDIO_SOURCE_NODE;
	
	RET_BOOL(_isDestroyed);
	
}
