#ifndef _STEREO_PANNER_NODE_HPP_
#define _STEREO_PANNER_NODE_HPP_


#include "common.hpp"

#include "audio-node.hpp"


class StereoPannerNode : public Napi::ObjectWrap<StereoPannerNode>, private CommonNode {
	
public:
	
	~StereoPannerNode();
	explicit StereoPannerNode(const Napi::CallbackInfo &info);
	
	static void init(Napi::Env env, Napi::Object exports);
	
	static bool isStereoPannerNode(Napi::Object obj);
	
	// Destroy an instance from C++ land
	void _destroy();
	
	
protected:
	
	StereoPannerNode();
	
	static Napi::FunctionReference _constructor;
	
	bool _isDestroyed;
	
	Napi::ObjectReference _pan;
	
	
private:
	
	JS_METHOD(destroy);
	JS_GETTER(isDestroyedGetter);
	
	
	
	JS_GETTER(panGetter);
	
};


#endif // _STEREO_PANNER_NODE_HPP_
