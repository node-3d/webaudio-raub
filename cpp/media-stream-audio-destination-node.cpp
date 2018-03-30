#include <cstdlib>
//#include <iostream> // -> cout << "..." << endl;


#include "media-stream-audio-destination-node.hpp"


using namespace v8;
using namespace node;
using namespace std;


// ------ Aux macros

#define THIS_MEDIA_STREAM_AUDIO_DESTINATION_NODE                                                    \
	MediaStreamAudioDestinationNode *mediaStreamAudioDestinationNode = Nan::ObjectWrap::Unwrap<MediaStreamAudioDestinationNode>(info.This());

#define THIS_CHECK                                                            \
	if (mediaStreamAudioDestinationNode->_isDestroyed) return;

#define CACHE_CAS(CACHE, V)                                                   \
	if (mediaStreamAudioDestinationNode->CACHE == V) {                                           \
		return;                                                               \
	}                                                                         \
	mediaStreamAudioDestinationNode->CACHE = V;


// ------ Constructor and Destructor

MediaStreamAudioDestinationNode::MediaStreamAudioDestinationNode() : AudioNode() {
	
	_isDestroyed = false;
	
}


MediaStreamAudioDestinationNode::~MediaStreamAudioDestinationNode() {
	
	_destroy();
	
}


void MediaStreamAudioDestinationNode::_destroy() { DES_CHECK;
	
	_isDestroyed = true;
	
	AudioNode::_destroy();
	
}


// ------ Methods and props



NAN_GETTER(MediaStreamAudioDestinationNode::streamGetter) { THIS_MEDIA_STREAM_AUDIO_DESTINATION_NODE; THIS_CHECK;
	
	RET_VALUE(JS_OBJ(mediaStreamAudioDestinationNode->_stream));
	
}


// ------ System methods and props for ObjectWrap

V8_STORE_FT MediaStreamAudioDestinationNode::_protoMediaStreamAudioDestinationNode;
V8_STORE_FUNC MediaStreamAudioDestinationNode::_ctorMediaStreamAudioDestinationNode;


void MediaStreamAudioDestinationNode::init(V8_VAR_OBJ target) {
	
	V8_VAR_FT proto = Nan::New<FunctionTemplate>(newCtor);

	// class MediaStreamAudioDestinationNode inherits AudioNode
	V8_VAR_FT parent = Nan::New(AudioNode::_protoAudioNode);
	proto->Inherit(parent);
	
	proto->InstanceTemplate()->SetInternalFieldCount(1);
	proto->SetClassName(JS_STR("MediaStreamAudioDestinationNode"));
	
	
	// Accessors
	V8_VAR_OT obj = proto->PrototypeTemplate();
	ACCESSOR_R(obj, isDestroyed);
	
	ACCESSOR_R(obj, stream);
	
	// -------- dynamic
	
	Nan::SetPrototypeMethod(proto, "destroy", destroy);
	
	
	
	// -------- static
	
	V8_VAR_FUNC ctor = Nan::GetFunction(proto).ToLocalChecked();
	
	_protoMediaStreamAudioDestinationNode.Reset(proto);
	_ctorMediaStreamAudioDestinationNode.Reset(ctor);
	
	Nan::Set(target, JS_STR("MediaStreamAudioDestinationNode"), ctor);
	
	
}


bool MediaStreamAudioDestinationNode::isMediaStreamAudioDestinationNode(V8_VAR_OBJ obj) {
	return Nan::New(_protoMediaStreamAudioDestinationNode)->HasInstance(obj);
}


V8_VAR_OBJ MediaStreamAudioDestinationNode::getNew() {
	
	V8_VAR_FUNC ctor = Nan::New(_ctorMediaStreamAudioDestinationNode);
	// V8_VAR_VAL argv[] = { /* arg1, arg2, ... */ };
	return Nan::NewInstance(ctor, 0/*argc*/, nullptr/*argv*/).ToLocalChecked();
	
}


NAN_METHOD(MediaStreamAudioDestinationNode::newCtor) {
	
	CTOR_CHECK("MediaStreamAudioDestinationNode");
	
	MediaStreamAudioDestinationNode *mediaStreamAudioDestinationNode = new MediaStreamAudioDestinationNode();
	mediaStreamAudioDestinationNode->Wrap(info.This());
	
	RET_VALUE(info.This());
	
}


NAN_METHOD(MediaStreamAudioDestinationNode::destroy) { THIS_MEDIA_STREAM_AUDIO_DESTINATION_NODE; THIS_CHECK;
	
	mediaStreamAudioDestinationNode->_destroy();
	
}


NAN_GETTER(MediaStreamAudioDestinationNode::isDestroyedGetter) { THIS_MEDIA_STREAM_AUDIO_DESTINATION_NODE;
	
	RET_VALUE(JS_BOOL(mediaStreamAudioDestinationNode->_isDestroyed));
	
}
