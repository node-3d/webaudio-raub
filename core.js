'use strict';


const util = require('util');

// Add deps dll dirs
require('deps-labsound-raub');

const core = require('./binary/waa');
const { AudioContext } = core;


AudioContext.prototype[util.inspect.custom] = function () {
	return 'AudioContext { }';
};


module.exports = core;
