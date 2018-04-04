'use strict';


const util = require('util');

// Add deps dll dirs
const { hrtf } = require('deps-labsound-raub');

const core = require('./binary/waa');
const { AudioContext, PannerNode } = core;


AudioContext.prototype[util.inspect.custom] = function () {
	return 'AudioContext { }';
};

PannerNode.hrtf = hrtf;

module.exports = core;
