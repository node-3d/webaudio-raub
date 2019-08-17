#ifndef _CHANNEL_MERGER_NODE_HPP_
#define _CHANNEL_MERGER_NODE_HPP_


#include "common.hpp"

#include "audio-node.hpp"


class ChannelMergerNode : public Napi::ObjectWrap<ChannelMergerNode>, private CommonNode {
	
public:
	
	~ChannelMergerNode();
	explicit ChannelMergerNode(const Napi::CallbackInfo &info);
	
	static void init(Napi::Env env, Napi::Object exports);
	
};


#endif // _CHANNEL_MERGER_NODE_HPP_
