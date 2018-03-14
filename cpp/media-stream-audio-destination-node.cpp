#include <cstdlib>
#include <iostream>

#include "media-stream-audio-destination-node.hpp"

using namespace v8;
using namespace node;
using namespace std;


#define THIS_MEDIA_STREAM_AUDIO_DESTINATION_NODE                                                    \
	MediaStreamAudioDestinationNode *mediaStreamAudioDestinationNode = ObjectWrap::Unwrap<MediaStreamAudioDestinationNode>(info.This());

#define THIS_CHECK                                                            \
	if (mediaStreamAudioDestinationNode->_isDestroyed) return;

#define DES_CHECK                                                             \
	if (_isDestroyed) return;

#define CACHE_CAS(CACHE, V)                                                   \
	if (mediaStreamAudioDestinationNode->CACHE == V) {                                           \
		return;                                                               \
	}                                                                         \
	mediaStreamAudioDestinationNode->CACHE = V;


Nan::Persistent<v8::Function> MediaStreamAudioDestinationNode::_constructor;


void MediaStreamAudioDestinationNode::init(Local<Object> target) {
	
	Local<FunctionTemplate> proto = Nan::New<FunctionTemplate>(newCtor);
	
	proto->InstanceTemplate()->SetInternalFieldCount(1);
	proto->SetClassName(JS_STR("MediaStreamAudioDestinationNode"));
	
	
	// Accessors
	Local<ObjectTemplate> obj = proto->PrototypeTemplate();
	ACCESSOR_R(obj, isDestroyed);
	
	ACCESSOR_R(obj, stream);
	
	// -------- dynamic
	
	
	
	Nan::SetPrototypeMethod(proto, "destroy", destroy);
	
	
	
	// -------- static
	
	Local<Function> ctor = Nan::GetFunction(proto).ToLocalChecked();
	
	
	
	
	_constructor.Reset(ctor);
	Nan::Set(target, JS_STR("MediaStreamAudioDestinationNode"), ctor);
	
	
}


NAN_METHOD(MediaStreamAudioDestinationNode::newCtor) {
	
	CTOR_CHECK("MediaStreamAudioDestinationNode");
	
	MediaStreamAudioDestinationNode *mediaStreamAudioDestinationNode = new MediaStreamAudioDestinationNode();
	mediaStreamAudioDestinationNode->Wrap(info.This());
	
	RET_VALUE(info.This());
	
}


MediaStreamAudioDestinationNode::MediaStreamAudioDestinationNode() {
	
	_isDestroyed = false;
	
}


MediaStreamAudioDestinationNode::~MediaStreamAudioDestinationNode() {
	
	_destroy();
	
}


void MediaStreamAudioDestinationNode::_destroy() { DES_CHECK;
	
	_isDestroyed = true;
	
	
	
}



NAN_METHOD(MediaStreamAudioDestinationNode::destroy) { THIS_MEDIA_STREAM_AUDIO_DESTINATION_NODE; THIS_CHECK;
	
	mediaStreamAudioDestinationNode->_destroy();
	
}




NAN_GETTER(MediaStreamAudioDestinationNode::isDestroyedGetter) { THIS_MEDIA_STREAM_AUDIO_DESTINATION_NODE;
	
	RET_VALUE(JS_BOOL(mediaStreamAudioDestinationNode->_isDestroyed));
	
}


NAN_GETTER(MediaStreamAudioDestinationNode::streamGetter) { THIS_MEDIA_STREAM_AUDIO_DESTINATION_NODE; THIS_CHECK;
	
	RET_VALUE(JS_OBJ(mediaStreamAudioDestinationNode->_stream));
	
}


