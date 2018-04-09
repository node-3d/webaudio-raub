'use strict';


const util = require('util');

// Add deps dll dirs
const { hrtf } = require('deps-labsound-raub');

const core = require('./binary/waa');
const { AudioContext, PannerNode, AudioScheduledSourceNode } = core;


AudioContext.prototype[util.inspect.custom] = function () {
	return 'AudioContext { }';
};


Object.defineProperty(AudioScheduledSourceNode.prototype, 'onended', {
	get() { return this.listeners('ended'); },
	set(v) { this.on('ended', v); },
});


PannerNode.hrtf = hrtf;

module.exports = core;
