#include <cstdlib>
//#include <iostream> // -> cout << "..." << endl;


#include <LabSound/core/AudioContext.h>
#include <LabSound/core/PannerNode.h>
#include <LabSound/extended/AudioContextLock.h>

#include "lab-audio-panner-param.hpp"
#include "audio-context.hpp"


using namespace v8;
using namespace node;
using namespace std;


double LabAudioPannerParam::_inf = std::numeric_limits<double>::infinity();


LabAudioPannerParam::LabAudioPannerParam(const string &id, lab::PannerNode *target, ParamName name) :
lab::AudioParam(id, 0., -_inf, _inf) {
	_target = target;
	_name = name;
}

float LabAudioPannerParam::value() {
	
	if (_name == positionX) {
		return _target->position().x;
	} else if (_name == positionY) {
		return _target->position().y;
	} else if (_name == positionZ) {
		return _target->position().z;
	} else if (_name == orientationX) {
		return _target->orientation().x;
	} else if (_name == orientationY) {
		return _target->orientation().y;
	} else if (_name == orientationZ) {
		return _target->orientation().z;
	} else {
		return 0.f;
	}
	
}

void LabAudioPannerParam::setValue(float v) {
	
	if (_name == positionX) {
		lab::FloatPoint3D pos = _target->position();
		_target->setPosition(v, pos.y, pos.z);
	} else if (_name == positionY) {
		lab::FloatPoint3D pos = _target->position();
		_target->setPosition(pos.x, v, pos.z);
	} else if (_name == positionZ) {
		lab::FloatPoint3D pos = _target->position();
		_target->setPosition(pos.x, pos.y, v);
	} else if (_name == orientationX) {
		lab::FloatPoint3D orient = _target->orientation();
		_target->setOrientation(v, orient.y, orient.z);
	} else if (_name == orientationY) {
		lab::FloatPoint3D orient = _target->orientation();
		_target->setOrientation(orient.x, v, orient.z);
	} else if (_name == orientationZ) {
		lab::FloatPoint3D orient = _target->orientation();
		_target->setOrientation(orient.x, orient.y, v);
	}
	
}
