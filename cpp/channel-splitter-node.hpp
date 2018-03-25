#ifndef _CHANNEL_SPLITTER_NODE_HPP_
#define _CHANNEL_SPLITTER_NODE_HPP_


#include <addon-tools.hpp>

#include "audio-node.hpp"


class ChannelSplitterNode : public AudioNode {
	
public:
	
	// Public V8 init
	static void init(v8::Local<v8::Object> target);
	
	// Make a new instance from C++ land
	static v8::Local<v8::Object> getNew();
	
	// Destroy an instance from C++ land
	void _destroy();
	
	
// Methods and props, available for children
protected:
	
	ChannelSplitterNode();
	virtual ~ChannelSplitterNode();
	
	static Nan::Persistent<v8::FunctionTemplate> _protoChannelSplitterNode;
	static Nan::Persistent<v8::Function> _ctorChannelSplitterNode;
	
	bool _isDestroyed;
	
	
	
	
// JS methods and props, available through V8 APIs
private:
	
	static NAN_METHOD(newCtor);
	
	static NAN_METHOD(destroy);
	static NAN_GETTER(isDestroyedGetter);
	
	
	
};


#endif // _CHANNEL_SPLITTER_NODE_HPP_
