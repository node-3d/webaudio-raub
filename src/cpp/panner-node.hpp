#ifndef _PANNER_NODE_HPP_
#define _PANNER_NODE_HPP_


#include "audio-node.hpp"

#include "audio-param.hpp"


class PannerNode : public AudioNode {
	
public:
	
	~PannerNode();
	
	// Public V8 init
	static void init(Napi::Object target);
	
	static bool isPannerNode(Napi::Object obj);
	
	// Make a new instance from C++ land
	static Napi::Object getNew(Napi::Object context);
	
	// Destroy an instance from C++ land
	void _destroy();
	
	
// Methods and props, available for children
protected:
	
	PannerNode(Napi::Object context, float sampleRate, const std::string &hrtf);
	
	static V8_STORE_FT _protoPannerNode;
	static V8_STORE_FUNC _ctorPannerNode;
	
	bool _isDestroyed;
	
	V8_STORE_OBJ _positionX;
	V8_STORE_OBJ _positionY;
	V8_STORE_OBJ _positionZ;
	V8_STORE_OBJ _orientationX;
	V8_STORE_OBJ _orientationY;
	V8_STORE_OBJ _orientationZ;
	
	
// JS methods and props, available through V8 APIs
private:
	
	static NAN_METHOD(newCtor);
	
	static NAN_METHOD(destroy);
	static NAN_GETTER(isDestroyedGetter);
	
	static NAN_METHOD(setPosition);
	static NAN_METHOD(setOrientation);
	static NAN_METHOD(setVelocity);
	
	static NAN_GETTER(panningModelGetter);
	static NAN_SETTER(panningModelSetter);
	
	static NAN_GETTER(positionXGetter);
	
	static NAN_GETTER(positionYGetter);
	
	static NAN_GETTER(positionZGetter);
	
	static NAN_GETTER(orientationXGetter);
	
	static NAN_GETTER(orientationYGetter);
	
	static NAN_GETTER(orientationZGetter);
	
	static NAN_GETTER(distanceModelGetter);
	static NAN_SETTER(distanceModelSetter);
	
	static NAN_GETTER(refDistanceGetter);
	static NAN_SETTER(refDistanceSetter);
	
	static NAN_GETTER(maxDistanceGetter);
	static NAN_SETTER(maxDistanceSetter);
	
	static NAN_GETTER(rolloffFactorGetter);
	static NAN_SETTER(rolloffFactorSetter);
	
	static NAN_GETTER(coneInnerAngleGetter);
	static NAN_SETTER(coneInnerAngleSetter);
	
	static NAN_GETTER(coneOuterAngleGetter);
	static NAN_SETTER(coneOuterAngleSetter);
	
	static NAN_GETTER(coneOuterGainGetter);
	static NAN_SETTER(coneOuterGainSetter);
	
};


#endif // _PANNER_NODE_HPP_
