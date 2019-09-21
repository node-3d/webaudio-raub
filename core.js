'use strict';

require('segfault-raub');

// Add deps dll dirs
require('deps-labsound-raub');
const { bin } = require('addon-tools-raub');

const core = require(`./${bin}/webaudio`);

module.exports = core;
