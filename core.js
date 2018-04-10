'use strict';


// const util = require('util');

// Add deps dll dirs
const { hrtf } = require('deps-labsound-raub');

const core = require('./binary/waa');


const {
	BaseAudioContext,
	// OfflineAudioContext,
	PannerNode,
	AudioScheduledSourceNode
} = core;

const addHandler = (Target, name) => {
	Object.defineProperty(Object.getPrototypeOf(Target), `on${name}`, {
		get() { return this.listeners(name); },
		set(v) { this.on(name, v); },
	});
};


PannerNode.hrtf = hrtf;

addHandler(BaseAudioContext, 'statechange');
// addHandler(OfflineAudioContext, 'complete');
addHandler(AudioScheduledSourceNode, 'ended');


module.exports = core;
