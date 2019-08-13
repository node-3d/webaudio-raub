#ifndef _DELAY_NODE_HPP_
#define _DELAY_NODE_HPP_


#include <addon-tools.hpp>

#include "audio-node.hpp"


class DelayNode : public AudioNode {
	
public:
	
	~DelayNode();
	
	// Public V8 init
	static void init(Napi::Object target);
	
	static bool isDelayNode(Napi::Object obj);
	
	// Make a new instance from C++ land
	static Napi::Object getNew(Napi::Object context, double delay);
	
	// Destroy an instance from C++ land
	void _destroy();
	
	
// Methods and props, available for children
protected:
	
	DelayNode(Napi::Object context, float sampleRate, double delay);
	
	static V8_STORE_FT _protoDelayNode;
	static V8_STORE_FUNC _ctorDelayNode;
	
	bool _isDestroyed;
	
	V8_STORE_OBJ _delayTime;
	
	
// JS methods and props, available through V8 APIs
private:
	
	static NAN_METHOD(newCtor);
	
	static NAN_METHOD(destroy);
	static NAN_GETTER(isDestroyedGetter);
	
	static NAN_GETTER(delayTimeGetter);
	
};


#endif // _DELAY_NODE_HPP_
