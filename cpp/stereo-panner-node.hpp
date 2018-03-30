#ifndef _STEREO_PANNER_NODE_HPP_
#define _STEREO_PANNER_NODE_HPP_


#include <addon-tools.hpp>

#include "audio-node.hpp"


class StereoPannerNode : public AudioNode {
	
public:
	
	// Public V8 init
	static void init(V8_VAR_OBJ target);
	
	static bool isStereoPannerNode(V8_VAR_OBJ obj);
	
	// Make a new instance from C++ land
	static V8_VAR_OBJ getNew();
	
	// Destroy an instance from C++ land
	void _destroy();
	
	
// Methods and props, available for children
protected:
	
	StereoPannerNode();
	virtual ~StereoPannerNode();
	
	static V8_STORE_FT _protoStereoPannerNode;
	static V8_STORE_FUNC _ctorStereoPannerNode;
	
	bool _isDestroyed;
	
	V8_STORE_OBJ _pan;
	
	
// JS methods and props, available through V8 APIs
private:
	
	static NAN_METHOD(newCtor);
	
	static NAN_METHOD(destroy);
	static NAN_GETTER(isDestroyedGetter);
	
	
	
	static NAN_GETTER(panGetter);
	
};


#endif // _STEREO_PANNER_NODE_HPP_
