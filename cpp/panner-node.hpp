#ifndef _PANNER_NODE_HPP_
#define _PANNER_NODE_HPP_


#include <addon-tools.hpp>


class PannerNode : public Nan::ObjectWrap {
	
// Public V8 init
public:
	
	static void init(v8::Local<v8::Object> target);
	
	
// Public C++ methods: in-engine calls
public:
	
	
// Protected C++ methods: implementing JS calls
protected:
	
	PannerNode();
	virtual ~PannerNode();
	
	
// JS methods and props
protected:
	
	static NAN_METHOD(newCtor);
	
	static NAN_METHOD(destroy);
	
	static NAN_METHOD(setPosition);
	static NAN_METHOD(setOrientation);
	
	
	static NAN_GETTER(isDestroyedGetter);
	
	
	static NAN_GETTER(panningModelGetter);
	static NAN_SETTER(panningModelSetter);
	

	static NAN_GETTER(positionXGetter);
	static NAN_SETTER(positionXSetter);
	

	static NAN_GETTER(positionYGetter);
	static NAN_SETTER(positionYSetter);
	

	static NAN_GETTER(positionZGetter);
	static NAN_SETTER(positionZSetter);
	

	static NAN_GETTER(orientationXGetter);
	static NAN_SETTER(orientationXSetter);
	

	static NAN_GETTER(orientationYGetter);
	static NAN_SETTER(orientationYSetter);
	

	static NAN_GETTER(orientationZGetter);
	static NAN_SETTER(orientationZSetter);
	

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
	
	
// Actual destruction-handler
private:
	
	void _destroy();
	
	
// Stored JS constructor and helpers
private:
	
	static Nan::Persistent<v8::Function> _constructor;
	
	
// This-state storage
private:
	
	bool _isDestroyed;
	
	std::string _panningModel;
	Nan::Persistent<v8::Object> _positionX;
	Nan::Persistent<v8::Object> _positionY;
	Nan::Persistent<v8::Object> _positionZ;
	Nan::Persistent<v8::Object> _orientationX;
	Nan::Persistent<v8::Object> _orientationY;
	Nan::Persistent<v8::Object> _orientationZ;
	std::string _distanceModel;
	double _refDistance;
	double _maxDistance;
	double _rolloffFactor;
	double _coneInnerAngle;
	double _coneOuterAngle;
	double _coneOuterGain;
	
};


#endif // _PANNER_NODE_HPP_
