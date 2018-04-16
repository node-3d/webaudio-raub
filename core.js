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
	Object.defineProperty(Target.prototype, `on${name}`, {
		get() { return this.listeners(name); },
		set(v) { this.on(name, v); },
	});
};


PannerNode.hrtf = hrtf;

BaseAudioContext.UPDATE_INTERVAL = 20;

BaseAudioContext.startUpdater = that => {
	that._updateTimerId = setInterval(() => that.update(), BaseAudioContext.UPDATE_INTERVAL);
	that._updateTimerId.unref();
};

BaseAudioContext.stopUpdater = that => {
	clearInterval(that._updateTimerId);
	that._updateTimerId = null;
};

addHandler(BaseAudioContext, 'statechange');
// addHandler(OfflineAudioContext, 'complete');
addHandler(AudioScheduledSourceNode, 'ended');


module.exports = core;
