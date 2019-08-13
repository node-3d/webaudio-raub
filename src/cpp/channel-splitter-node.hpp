#ifndef _CHANNEL_SPLITTER_NODE_HPP_
#define _CHANNEL_SPLITTER_NODE_HPP_


#include <addon-tools.hpp>

#include "audio-node.hpp"


class ChannelSplitterNode : public AudioNode {
	
public:
	
	~ChannelSplitterNode();
	
	// Public V8 init
	static void init(Napi::Object target);
	
	static bool isChannelSplitterNode(Napi::Object obj);
	
	// Make a new instance from C++ land
	static Napi::Object getNew();
	
	// Destroy an instance from C++ land
	void _destroy();
	
	
// Methods and props, available for children
protected:
	
	ChannelSplitterNode();
	
	static V8_STORE_FT _protoChannelSplitterNode;
	static V8_STORE_FUNC _ctorChannelSplitterNode;
	
	bool _isDestroyed;
	
	
	
	
// JS methods and props, available through V8 APIs
private:
	
	static NAN_METHOD(newCtor);
	
	static NAN_METHOD(destroy);
	static NAN_GETTER(isDestroyedGetter);
	
	
	
};


#endif // _CHANNEL_SPLITTER_NODE_HPP_
