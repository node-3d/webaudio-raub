#ifndef _STEREO_PANNER_NODE_HPP_
#define _STEREO_PANNER_NODE_HPP_


#include <addon-tools.hpp>

#include "audio-node.hpp"


class StereoPannerNode : public AudioNode {
	
public:
	
	// Public V8 init
	static void init(v8::Local<v8::Object> target);
	
	void _destroy();
	
	
// Methods and props
protected:
	
	StereoPannerNode();
	virtual ~StereoPannerNode();
	
	static Nan::Persistent<v8::FunctionTemplate> _protoStereoPannerNode; // for inheritance
	static Nan::Persistent<v8::Function> _ctorStereoPannerNode;
	
	
// System methods and props for ObjectWrap
private:
	
	static NAN_METHOD(newCtor);
	
	static NAN_METHOD(destroy);
	static NAN_GETTER(isDestroyedGetter);
	
	
	
	static NAN_GETTER(panGetter);
	
	
private:
	
	bool _isDestroyed;
	
	Nan::Persistent<v8::Object> _pan;
	
};


#endif // _STEREO_PANNER_NODE_HPP_
