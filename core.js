'use strict';

require('segfault-raub');

// Add deps dll dirs
// require('deps-labsound-raub');
const { getBin } = require('addon-tools-raub');

const core = require(`./${getBin()}/webaudio`);

module.exports = core;
