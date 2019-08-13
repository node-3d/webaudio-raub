#ifndef _CONSTANT_SOURCE_NODE_HPP_
#define _CONSTANT_SOURCE_NODE_HPP_


#include <addon-tools.hpp>

#include "audio-scheduled-source-node.hpp"


class ConstantSourceNode : public AudioScheduledSourceNode {
	
public:
	
	~ConstantSourceNode();
	
	// Public V8 init
	static void init(Napi::Object target);
	
	static bool isConstantSourceNode(Napi::Object obj);
	
	// Make a new instance from C++ land
	static Napi::Object getNew();
	
	// Destroy an instance from C++ land
	void _destroy();
	
	
// Methods and props, available for children
protected:
	
	ConstantSourceNode();
	
	static V8_STORE_FT _protoConstantSourceNode;
	static V8_STORE_FUNC _ctorConstantSourceNode;
	
	bool _isDestroyed;
	
	V8_STORE_OBJ _offset;
	
	
// JS methods and props, available through V8 APIs
private:
	
	static NAN_METHOD(newCtor);
	
	static NAN_METHOD(destroy);
	static NAN_GETTER(isDestroyedGetter);
	
	
	
	static NAN_GETTER(offsetGetter);
	
};


#endif // _CONSTANT_SOURCE_NODE_HPP_
