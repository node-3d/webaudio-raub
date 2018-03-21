#ifndef _CHANNEL_MERGER_NODE_HPP_
#define _CHANNEL_MERGER_NODE_HPP_


#include <addon-tools.hpp>

#include "audio-node.hpp"


class ChannelMergerNode : public AudioNode {
	
public:
	
	// Public V8 init
	static void init(v8::Local<v8::Object> target);
	
	void _destroy();
	
	
// Methods and props, available for children
protected:
	
	ChannelMergerNode();
	virtual ~ChannelMergerNode();
	
	static Nan::Persistent<v8::FunctionTemplate> _protoChannelMergerNode; // for inheritance
	static Nan::Persistent<v8::Function> _ctorChannelMergerNode;
	
	bool _isDestroyed;
	
	
	
	
// JS methods and props, available through V8 APIs
private:
	
	static NAN_METHOD(newCtor);
	
	static NAN_METHOD(destroy);
	static NAN_GETTER(isDestroyedGetter);
	
	
	
};


#endif // _CHANNEL_MERGER_NODE_HPP_
