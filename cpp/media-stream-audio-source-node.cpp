#include <cstdlib>
//#include <iostream> // -> std::cout << "..." << std::endl;


#include "media-stream-audio-source-node.hpp"


using namespace v8;
using namespace node;
using namespace std;


// ------ Aux macros

#define THIS_MEDIA_STREAM_AUDIO_SOURCE_NODE                                                    \
	MediaStreamAudioSourceNode *mediaStreamAudioSourceNode = ObjectWrap::Unwrap<MediaStreamAudioSourceNode>(info.This());

#define THIS_CHECK                                                            \
	if (mediaStreamAudioSourceNode->_isDestroyed) return;

#define CACHE_CAS(CACHE, V)                                                   \
	if (mediaStreamAudioSourceNode->CACHE == V) {                                           \
		return;                                                               \
	}                                                                         \
	mediaStreamAudioSourceNode->CACHE = V;


// ------ Constructor and Destructor

MediaStreamAudioSourceNode::MediaStreamAudioSourceNode() : AudioNode() {
	
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



NAN_GETTER(MediaStreamAudioSourceNode::mediaStreamGetter) { THIS_MEDIA_STREAM_AUDIO_SOURCE_NODE; THIS_CHECK;
	
	RET_VALUE(JS_OBJ(mediaStreamAudioSourceNode->_mediaStream));
	
}


// ------ System methods and props for ObjectWrap

Nan::Persistent<v8::FunctionTemplate> MediaStreamAudioSourceNode::_protoMediaStreamAudioSourceNode;
Nan::Persistent<v8::Function> MediaStreamAudioSourceNode::_ctorMediaStreamAudioSourceNode;


void MediaStreamAudioSourceNode::init(Local<Object> target) {
	
	Local<FunctionTemplate> proto = Nan::New<FunctionTemplate>(newCtor);
	
	// class MediaStreamAudioSourceNode inherits AudioNode
	Local<FunctionTemplate> parent = Nan::New(AudioNode::_protoAudioNode);
	proto->Inherit(parent);
	
	proto->InstanceTemplate()->SetInternalFieldCount(1);
	proto->SetClassName(JS_STR("MediaStreamAudioSourceNode"));
	
	
	// Accessors
	Local<ObjectTemplate> obj = proto->PrototypeTemplate();
	ACCESSOR_R(obj, isDestroyed);
	
	ACCESSOR_R(obj, mediaStream);
	
	// -------- dynamic
	
	Nan::SetPrototypeMethod(proto, "destroy", destroy);
	
	
	
	// -------- static
	
	Local<Function> ctor = Nan::GetFunction(proto).ToLocalChecked();
	
	_protoMediaStreamAudioSourceNode.Reset(proto);
	_ctorMediaStreamAudioSourceNode.Reset(ctor);
	
	Nan::Set(target, JS_STR("MediaStreamAudioSourceNode"), ctor);
	
	
}


NAN_METHOD(MediaStreamAudioSourceNode::newCtor) {
	
	CTOR_CHECK("MediaStreamAudioSourceNode");
	
	MediaStreamAudioSourceNode *mediaStreamAudioSourceNode = new MediaStreamAudioSourceNode();
	mediaStreamAudioSourceNode->Wrap(info.This());
	
	RET_VALUE(info.This());
	
}


NAN_METHOD(MediaStreamAudioSourceNode::destroy) { THIS_MEDIA_STREAM_AUDIO_SOURCE_NODE; THIS_CHECK;
	
	mediaStreamAudioSourceNode->_destroy();
	
}


NAN_GETTER(MediaStreamAudioSourceNode::isDestroyedGetter) { THIS_MEDIA_STREAM_AUDIO_SOURCE_NODE;
	
	RET_VALUE(JS_BOOL(mediaStreamAudioSourceNode->_isDestroyed));
	
}
