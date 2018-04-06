#include <cstdlib>
//#include <iostream> // -> cout << "..." << endl;


#include <LabSound/core/AudioContext.h>
#include <LabSound/core/AudioListener.h>
#include <LabSound/extended/AudioContextLock.h>

#include "lab-audio-listener-param.hpp"
#include "audio-context.hpp"


using namespace v8;
using namespace node;
using namespace std;


double LabAudioListenerParam::_inf = std::numeric_limits<double>::infinity();


LabAudioListenerParam::LabAudioListenerParam(const string &id, lab::AudioListener *target, ParamName name) :
lab::AudioParam(id, 0., -_inf, _inf) {
	_target = target;
	_name = name;
}

float LabAudioListenerParam::value() {
	
	if (_name == positionX) {
		return _target->position().x;
	} else if (_name == positionY) {
		return _target->position().y;
	} else if (_name == positionZ) {
		return _target->position().z;
	} else if (_name == forwardX) {
		return _target->orientation().x;
	} else if (_name == forwardY) {
		return _target->orientation().y;
	} else if (_name == forwardZ) {
		return _target->orientation().z;
	} else if (_name == upX) {
		return _target->upVector().x;
	} else if (_name == upY) {
		return _target->upVector().y;
	} else if (_name == upZ) {
		return _target->upVector().z;
	} else {
		return 0.f;
	}
	
}

void LabAudioListenerParam::setValue(float v) {
	
	if (_name == positionX) {
		lab::FloatPoint3D pos = _target->position();
		pos.x = v;
		_target->setPosition(pos);
	} else if (_name == positionY) {
		lab::FloatPoint3D pos = _target->position();
		pos.y = v;
		_target->setPosition(pos);
	} else if (_name == positionZ) {
		lab::FloatPoint3D pos = _target->position();
		pos.z = v;
		_target->setPosition(pos);
	} else if (_name == forwardX) {
		lab::FloatPoint3D orient = _target->orientation();
		orient.x = v;
		_target->setOrientation(orient);
	} else if (_name == forwardY) {
		lab::FloatPoint3D orient = _target->orientation();
		orient.y = v;
		_target->setOrientation(orient);
	} else if (_name == forwardZ) {
		lab::FloatPoint3D orient = _target->orientation();
		orient.z = v;
		_target->setOrientation(orient);
	} else if (_name == upX) {
		lab::FloatPoint3D up = _target->upVector();
		up.x = v;
		_target->setUpVector(up);
	} else if (_name == upY) {
		lab::FloatPoint3D up = _target->upVector();
		up.y = v;
		_target->setUpVector(up);
	} else if (_name == upZ) {
		lab::FloatPoint3D up = _target->upVector();
		up.z = v;
		_target->setUpVector(up);
	}
	
}
