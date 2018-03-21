#ifndef _CHANNEL_SPLITTER_NODE_HPP_
#define _CHANNEL_SPLITTER_NODE_HPP_


#include <addon-tools.hpp>

#include "audio-node.hpp"


class ChannelSplitterNode : public AudioNode {
	
public:
	
	// Public V8 init
	static void init(v8::Local<v8::Object> target);
	
	void _destroy();
	
	
// Methods and props
protected:
	
	ChannelSplitterNode();
	virtual ~ChannelSplitterNode();
	
	static Nan::Persistent<v8::FunctionTemplate> _protoChannelSplitterNode; // for inheritance
	static Nan::Persistent<v8::Function> _ctorChannelSplitterNode;
	
	
// System methods and props for ObjectWrap
private:
	
	static NAN_METHOD(newCtor);
	
	static NAN_METHOD(destroy);
	static NAN_GETTER(isDestroyedGetter);
	
	
	
	
private:
	
	bool _isDestroyed;
	
	
	
};


#endif // _CHANNEL_SPLITTER_NODE_HPP_
