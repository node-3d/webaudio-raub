#ifndef _STEREO_PANNER_NODE_HPP_
#define _STEREO_PANNER_NODE_HPP_


#include <addon-tools.hpp>

#include "audio-node.hpp"


class StereoPannerNode : public AudioNode {
	
public:
	
	~StereoPannerNode();
	
	// Public V8 init
	static void init(Napi::Env env, Napi::Object exports);
	
	static bool isStereoPannerNode(Napi::Object obj);
	
	// Make a new instance from C++ land
	explicit StereoPannerNode(const Napi::CallbackInfo& info);
	
	// Destroy an instance from C++ land
	void _destroy();
	
	
// Methods and props, available for children
protected:
	
	StereoPannerNode();
	
	static Napi::FunctionReference _ctorStereoPannerNode;
	
	bool _isDestroyed;
	
	Napi::ObjectReference _pan;
	
	
// JS methods and props, available through V8 APIs
private:
	
	JS_METHOD(newCtor);
	
	JS_METHOD(destroy);
	JS_GETTER(isDestroyedGetter);
	
	
	
	JS_GETTER(panGetter);
	
};


#endif // _STEREO_PANNER_NODE_HPP_
