#ifndef _DELAY_NODE_HPP_
#define _DELAY_NODE_HPP_


#include <addon-tools.hpp>

#include "audio-node.hpp"


class DelayNode : public Napi::ObjectWrap<DelayNode> {
	
public:
	
	~DelayNode();
	DelayNode(const Napi::CallbackInfo &info);
	
	// Public V8 init
	static void init(Napi::Env env, Napi::Object exports);
	
	static bool isDelayNode(Napi::Object obj);
	
	// Make a new instance from C++ land
	explicit DelayNode(const Napi::CallbackInfo& info);
	
	// Destroy an instance from C++ land
	void _destroy();
	
	
protected:
	
	DelayNode(Napi::Object context, float sampleRate, double delay);
	
	static Napi::FunctionReference _ctorDelayNode;
	
	bool _isDestroyed;
	
	Napi::ObjectReference _delayTime;
	
	
private:
	
	JS_METHOD(destroy);
	JS_GETTER(isDestroyedGetter);
	
	JS_GETTER(delayTimeGetter);
	
};


#endif // _DELAY_NODE_HPP_
