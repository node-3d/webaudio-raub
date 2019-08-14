#ifndef _CHANNEL_MERGER_NODE_HPP_
#define _CHANNEL_MERGER_NODE_HPP_


#include <addon-tools.hpp>

#include "audio-node.hpp"


class ChannelMergerNode : public AudioNode {
	
public:
	
	~ChannelMergerNode();
	
	// Public V8 init
	static void init(Napi::Env env, Napi::Object exports);
	
	static bool isChannelMergerNode(Napi::Object obj);
	
	// Make a new instance from C++ land
	explicit ChannelMergerNode(const Napi::CallbackInfo& info);
	
	// Destroy an instance from C++ land
	void _destroy();
	
	
// Methods and props, available for children
protected:
	
	ChannelMergerNode();
	
	static Napi::FunctionReference _ctorChannelMergerNode;
	
	bool _isDestroyed;
	
	
	
	
// JS methods and props, available through V8 APIs
private:
	
	JS_METHOD(newCtor);
	
	JS_METHOD(destroy);
	JS_GETTER(isDestroyedGetter);
	
	
	
};


#endif // _CHANNEL_MERGER_NODE_HPP_
