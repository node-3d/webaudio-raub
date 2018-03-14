#include <cstdlib>
#include <iostream>

#include "media-stream-audio-source-node.hpp"

using namespace v8;
using namespace node;
using namespace std;


#define THIS_MEDIA_STREAM_AUDIO_SOURCE_NODE                                                    \
	MediaStreamAudioSourceNode *mediaStreamAudioSourceNode = ObjectWrap::Unwrap<MediaStreamAudioSourceNode>(info.This());

#define THIS_CHECK                                                            \
	if (mediaStreamAudioSourceNode->_isDestroyed) return;

#define DES_CHECK                                                             \
	if (_isDestroyed) return;

#define CACHE_CAS(CACHE, V)                                                   \
	if (mediaStreamAudioSourceNode->CACHE == V) {                                           \
		return;                                                               \
	}                                                                         \
	mediaStreamAudioSourceNode->CACHE = V;


Nan::Persistent<v8::Function> MediaStreamAudioSourceNode::_constructor;


void MediaStreamAudioSourceNode::init(Local<Object> target) {
	
	Local<FunctionTemplate> proto = Nan::New<FunctionTemplate>(newCtor);
	
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
	
	
	
	
	_constructor.Reset(ctor);
	Nan::Set(target, JS_STR("MediaStreamAudioSourceNode"), ctor);
	
	
}


NAN_METHOD(MediaStreamAudioSourceNode::newCtor) {
	
	CTOR_CHECK("MediaStreamAudioSourceNode");
	
	MediaStreamAudioSourceNode *mediaStreamAudioSourceNode = new MediaStreamAudioSourceNode();
	mediaStreamAudioSourceNode->Wrap(info.This());
	
	RET_VALUE(info.This());
	
}


MediaStreamAudioSourceNode::MediaStreamAudioSourceNode() {
	
	_isDestroyed = false;
	
}


MediaStreamAudioSourceNode::~MediaStreamAudioSourceNode() {
	
	_destroy();
	
}


void MediaStreamAudioSourceNode::_destroy() { DES_CHECK;
	
	_isDestroyed = true;
	
	
	
}



NAN_METHOD(MediaStreamAudioSourceNode::destroy) { THIS_MEDIA_STREAM_AUDIO_SOURCE_NODE; THIS_CHECK;
	
	mediaStreamAudioSourceNode->_destroy();
	
}




NAN_GETTER(MediaStreamAudioSourceNode::isDestroyedGetter) { THIS_MEDIA_STREAM_AUDIO_SOURCE_NODE;
	
	RET_VALUE(JS_BOOL(mediaStreamAudioSourceNode->_isDestroyed));
	
}


NAN_GETTER(MediaStreamAudioSourceNode::mediaStreamGetter) { THIS_MEDIA_STREAM_AUDIO_SOURCE_NODE; THIS_CHECK;
	
	RET_VALUE(JS_OBJ(mediaStreamAudioSourceNode->_mediaStream));
	
}


