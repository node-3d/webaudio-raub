#ifndef _CHANNEL_SPLITTER_NODE_HPP_
#define _CHANNEL_SPLITTER_NODE_HPP_

#include "common.hpp"

#include "audio-node.hpp"


class ChannelSplitterNode : public CommonNode<ChannelSplitterNode> {
DECLARE_ES5_CLASS(ChannelSplitterNode, ChannelSplitterNode);
	
public:
	static void init(Napi::Env env, Napi::Object exports);
	static Napi::Object create(Napi::Env env, Napi::Object context);
	
	explicit ChannelSplitterNode(const Napi::CallbackInfo &info);
	~ChannelSplitterNode();
	
	void _destroy();
	
private:
	JS_DECLARE_METHOD(ChannelSplitterNode, destroy);
	
};


#endif // _CHANNEL_SPLITTER_NODE_HPP_
