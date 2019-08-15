#ifndef _CHANNEL_SPLITTER_NODE_HPP_
#define _CHANNEL_SPLITTER_NODE_HPP_


#include <addon-tools.hpp>

#include "audio-node.hpp"


class ChannelSplitterNode : public AudioNode {
	
public:
	
	~ChannelSplitterNode();
	
	// Public V8 init
	static void init(Napi::Env env, Napi::Object exports);
	
	static bool isChannelSplitterNode(Napi::Object obj);
	
	// Make a new instance from C++ land
	explicit ChannelSplitterNode(const Napi::CallbackInfo& info);
	
	// Destroy an instance from C++ land
	void _destroy();
	
	
// Methods and props, available for children
protected:
	
	ChannelSplitterNode();
	
	static Napi::FunctionReference _ctorChannelSplitterNode;
	
	bool _isDestroyed;
	
	
	
	
// JS methods and props, available through V8 APIs
private:
	
	JS_METHOD(destroy);
	JS_GETTER(isDestroyedGetter);
	
	
	
};


#endif // _CHANNEL_SPLITTER_NODE_HPP_
