#ifndef _CHANNEL_SPLITTER_NODE_HPP_
#define _CHANNEL_SPLITTER_NODE_HPP_


#include "common.hpp"

#include "audio-node.hpp"


class ChannelSplitterNode : public CommonNode<ChannelSplitterNode> {
	
public:
	
	~ChannelSplitterNode();
	explicit ChannelSplitterNode(const Napi::CallbackInfo &info);
	
	static void init(Napi::Env env, Napi::Object exports);
	
	static bool isChannelSplitterNode(Napi::Object obj);
	
	// Destroy an instance from C++ land
	void _destroy();
	
	
protected:
	
	ChannelSplitterNode();
	
	static Napi::FunctionReference _constructor;
	
	bool _isDestroyed;
	
	
	
	
private:
	
	JS_DECLARE_METHOD(destroy);
	JS_DECLARE_GETTER(isDestroyed);
	
	
	
};


#endif // _CHANNEL_SPLITTER_NODE_HPP_
